// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleDistributionItem.cpp
//! @brief     Implements class ParticleDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleDistribution.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "DomainObjectBuilder.h"
#include "TransformToDomain.h"
#include "TransformFromDomain.h"
#include "DistributionItem.h"
#include "Distributions.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include <QDebug>
#include <boost/scoped_ptr.hpp>

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER = "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::NO_SELECTION = "None";

ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0).limited(0.0, 1.0).setDecimals(3);

    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0, 1);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0, 1);
    addToValidChildren(Constants::ParticleCompositionType, PortInfo::PORT_0, 1);

    ComboProperty par_prop;
    registerProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant());
    updateParameterList();
}

ParticleDistributionItem::~ParticleDistributionItem()
{
}

void ParticleDistributionItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    if (item->modelType() == Constants::ParticleType
        || item->modelType() == Constants::ParticleCoreShellType
        || item->modelType() == Constants::ParticleCompositionType) {
        int port = item->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
        if (port == PortInfo::DEFAULT) {
            item->setItemPort(PortInfo::PORT_0);
        }
    }
}

void ParticleDistributionItem::onChildPropertyChange()
{
    updateParameterList();

    ParameterizedItem::onChildPropertyChange();
}

std::unique_ptr<ParticleDistribution> ParticleDistributionItem::createParticleDistribution() const
{
    auto children = childItems();
    if (children.size() == 0) {
        return nullptr;
    }
    std::unique_ptr<IParticle> P_particle = TransformToDomain::createIParticle(*children[0]);
    if (!P_particle) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    }
    auto distr_item = getSubItems()[ParticleDistributionItem::P_DISTRIBUTION];
    Q_ASSERT(distr_item);

    auto P_distribution = TransformToDomain::createDistribution(*distr_item);

    auto prop = getRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();
    QString par_name = prop.getValue();
    std::string domain_par = translateParameterName(par_name);
    int nbr_samples
        = distr_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor
        = distr_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();
    ParameterDistribution par_distr(domain_par, *P_distribution, nbr_samples, sigma_factor);
    auto result = GUIHelpers::make_unique<ParticleDistribution>(*P_particle, par_distr);
    double abundance = getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    result->setAbundance(abundance);
    return result;
}

void ParticleDistributionItem::updateParameterList()
{
    if (!isRegisteredProperty(P_DISTRIBUTED_PARAMETER))
        return;
    QVariant par_prop = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
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
    setRegisteredProperty(P_DISTRIBUTED_PARAMETER, updated_prop.getVariant());
}

QStringList ParticleDistributionItem::getChildParameterNames() const
{
    QStringList result;
    QList<ParameterizedItem *> children = childItems();
    if (children.size() > 1) {
        qDebug() << "ParticleDistributionItem::getChildParameterNames(): "
                 << "More than one child item";
        return result;
    }
    if (children.size() == 0) {
        result << NO_SELECTION;
        return result;
    }
    QString prefix = children.front()->displayName() + QString("/");
    result = children.front()->getParameterTreeList(prefix);
    result.prepend(NO_SELECTION);
    return result;
}

QStringList ParticleDistributionItem::extractFromParameterPool(const ParameterPool *pool) const
{
    QStringList result;
    std::vector<std::string> par_names = pool->getParameterNames();
    for (size_t i = 0; i < par_names.size(); ++i) {
        result << QString(par_names[i].c_str());
    }
    return result;
}
