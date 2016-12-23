// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleDistributionItem.cpp
//! @brief     Implements class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionItem.h"
#include "ComboProperty.h"
#include "DistributionItem.h"
#include "Distributions.h"
#include "GUIHelpers.h"
#include "ModelPath.h"
#include "ParameterPool.h"
#include "ParticleItem.h"
#include "TransformFromDomain.h"
#include "TransformToDomain.h"
#include <QDebug>

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER = "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::NO_SELECTION = "None";
const QString ParticleDistributionItem::T_PARTICLES = "Particle Tag";

ParticleDistributionItem::ParticleDistributionItem()
    : SessionGraphicsItem(Constants::ParticleDistributionType)
{
    addProperty(ParticleItem::P_ABUNDANCE, 1.0);
    getItem(ParticleItem::P_ABUNDANCE)->setLimits(RealLimits::limited(0.0, 1.0));
    getItem(ParticleItem::P_ABUNDANCE)->setDecimals(3);

    addGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);

    registerTag(T_PARTICLES, 0, 1, QStringList() << Constants::ParticleType <<
                Constants::ParticleCoreShellType << Constants::ParticleCompositionType);
    setDefaultTag(T_PARTICLES);

    ComboProperty par_prop;
    addProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant());
    updateParameterList();
    mapper()->setOnAnyChildChange(
        [this] (SessionItem* item) {
            // prevent infinit loop when item changes its own properties
            if (item && item->modelType()== Constants::PropertyType && item->parent() == this)
                return;
            updateParameterList();
        } );
}

ParticleDistributionItem::~ParticleDistributionItem()
{
}

std::unique_ptr<ParticleDistribution> ParticleDistributionItem::createParticleDistribution() const
{
    auto children = childItems();
    if (children.size() == 0)
        return nullptr;
    std::unique_ptr<IParticle> P_particle = TransformToDomain::createIParticle(*getItem());
    if (!P_particle)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    auto distr_item = getGroupItem(ParticleDistributionItem::P_DISTRIBUTION);
    Q_ASSERT(distr_item);

    auto P_distribution = TransformToDomain::createDistribution(*distr_item);

    auto prop = getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();
    QString par_name = prop.getValue();
    std::string domain_par = ModelPath::translateParameterName(this, par_name);
    int nbr_samples
        = distr_item->getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor
        = distr_item->getItemValue(DistributionItem::P_SIGMA_FACTOR).toDouble();
    ParameterDistribution par_distr(domain_par, *P_distribution, nbr_samples, sigma_factor);
    auto result = GUIHelpers::make_unique<ParticleDistribution>(*P_particle, par_distr);
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    result->setAbundance(abundance);
    return result;
}

void ParticleDistributionItem::updateParameterList()
{
    if (!isTag(P_DISTRIBUTED_PARAMETER))
        return;
    QVariant par_prop = getItemValue(P_DISTRIBUTED_PARAMETER);
    auto combo_prop = par_prop.value<ComboProperty>();
    QString cached_par = combo_prop.getCachedValue();
    if (!combo_prop.cacheContainsGUIValue()) {
        auto gui_name = TransformFromDomain::translateParameterNameToGUI(this, cached_par);
        if (!gui_name.isEmpty()) {
            cached_par = gui_name;
            combo_prop.setCachedValue(cached_par);
            combo_prop.setCacheContainsGUIFlag();
        }
    }
    QString selected_par = combo_prop.getValue();
    QStringList par_names = getChildParameterNames();
    par_names.removeAll(ParticleItem::P_ABUNDANCE);
    auto updated_prop = ComboProperty(par_names);
    updated_prop.setCachedValue(cached_par);
    updated_prop.setCacheContainsGUIFlag(combo_prop.cacheContainsGUIValue());
    if (updated_prop.getValues().contains(cached_par) ) {
        updated_prop.setValue(cached_par);
    } else if (updated_prop.getValues().contains(selected_par)) {
        updated_prop.setValue(selected_par);
    } else {
        updated_prop.setValue(NO_SELECTION);
    }
    setItemValue(P_DISTRIBUTED_PARAMETER, updated_prop.getVariant());
}

QStringList ParticleDistributionItem::getChildParameterNames() const
{
    QStringList result;
    QVector<SessionItem*> children = getItems();
    if (children.size() > 1) {
        Q_ASSERT(0);
        qDebug() << "ParticleDistributionItem::getChildParameterNames(): "
                 << "More than one child item";
        return result;
    }
    if (children.size() == 0) {
        result << NO_SELECTION;
        return result;
    }
    QString prefix = children.front()->displayName() + QString("/");
    result = ModelPath::getParameterTreeList(children.front(), prefix);
    result.prepend(NO_SELECTION);
    return result;
}

QStringList ParticleDistributionItem::extractFromParameterPool(const ParameterPool *pool) const
{
    QStringList result;
    std::vector<std::string> par_names = pool->parameterNames();
    for (size_t i = 0; i < par_names.size(); ++i) {
        result << QString(par_names[i].c_str());
    }
    return result;
}
