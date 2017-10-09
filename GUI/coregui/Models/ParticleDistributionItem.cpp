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
#include "DistributionItems.h"
#include "Distributions.h"
#include "GUIHelpers.h"
#include "ParticleItem.h"
#include "TransformFromDomain.h"
#include "TransformToDomain.h"
#include "ParameterTreeUtils.h"
#include "RealLimitsItems.h"
#include "ParameterUtils.h"
#include "Units.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";
}

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER = "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::NO_SELECTION = "None";
const QString ParticleDistributionItem::T_PARTICLES = "Particle Tag";

ParticleDistributionItem::ParticleDistributionItem()
    : SessionGraphicsItem(Constants::ParticleDistributionType)
{
    setToolTip(QStringLiteral("Collection of particles obtained via parametric distribution "
                              "of particle prototype"));

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3).setToolTip(abundance_tooltip);

    addGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup)->setToolTip(
        QStringLiteral("Distribution to apply to the specified parameter"));

    registerTag(T_PARTICLES, 0, 1, QStringList() << Constants::ParticleType
                                                 << Constants::ParticleCoreShellType
                                                 << Constants::ParticleCompositionType
                                                 << Constants::MesoCrystalType);
    setDefaultTag(T_PARTICLES);

    ComboProperty par_prop;
    addProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant())->setToolTip(
        QStringLiteral("Parameter to distribute"));

    updateParameterList();
    mapper()->setOnAnyChildChange([this](SessionItem* item) {
        // prevent infinit loop when item changes its own properties
        if (item && item->modelType() == Constants::PropertyType && item->parent() == this)
            return;
        updateParameterList();
    });
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
    auto& distr_item = groupItem<DistributionItem>(ParticleDistributionItem::P_DISTRIBUTION);

    auto prop
        = getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER).value<ComboProperty>();
    QString par_name = prop.getValue();

    std::string domain_par
        = ParameterTreeUtils::parameterNameToDomainName(par_name, childParticle()).toStdString();

    double scale = ParameterUtils::isAngleRelated(domain_par) ? Units::degree : 1.0;
    auto P_distribution = distr_item.createDistribution(scale);

    RealLimits limits = RealLimits::limitless();
    if(distr_item.isTag(DistributionItem::P_LIMITS)) {
        auto& limitsItem = distr_item.groupItem<RealLimitsItem>(DistributionItem::P_LIMITS);
        limits = limitsItem.createRealLimits(scale);
    }

    int nbr_samples = distr_item.getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor = distr_item.isTag(DistributionItem::P_SIGMA_FACTOR) ?
                          distr_item.getItemValue(DistributionItem::P_SIGMA_FACTOR).toDouble() :
                          0.0;
    ParameterDistribution par_distr(domain_par, *P_distribution, nbr_samples, sigma_factor, limits);
    auto result = GUIHelpers::make_unique<ParticleDistribution>(*P_particle, par_distr);
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    result->setAbundance(abundance);
    return result;
}

void ParticleDistributionItem::setDomainCacheName(const QString& name)
{
    m_domain_cache_name = name;
}

void ParticleDistributionItem::updateParameterList()
{
    if (!isTag(P_DISTRIBUTED_PARAMETER))
        return;

    ComboProperty prop = getItemValue(P_DISTRIBUTED_PARAMETER).value<ComboProperty>();
    QString currentValue = prop.getValue();

    QStringList par_names = QStringList() << NO_SELECTION << childParameterNames();
    par_names.removeAll(ParticleItem::P_ABUNDANCE);
    ComboProperty newProp = ComboProperty(par_names, NO_SELECTION);

    bool make_cache_clear(false);
    if (!m_domain_cache_name.isEmpty()) {
        QString guiName = translateParameterNameToGUI(m_domain_cache_name);
        if (!guiName.isEmpty()) { // might be empty because item was not fully constructed yet
            currentValue = guiName;
            make_cache_clear = true;
        }
    }

    if (newProp.getValues().contains(currentValue))
        newProp.setValue(currentValue);

    // we first set parameter, and then clear the cache name, to not to allow
    // initDistributionItem to override limits obtained from the domain
    if(prop != newProp)
        setItemValue(P_DISTRIBUTED_PARAMETER, newProp.getVariant());

    if(make_cache_clear)
        m_domain_cache_name.clear();
}

QStringList ParticleDistributionItem::childParameterNames() const
{
    if(auto child = childParticle())
        return ParameterTreeUtils::parameterTreeNames(child);

    return {};
}

QString ParticleDistributionItem::translateParameterNameToGUI(const QString& domainName)
{
    if(auto child = childParticle())
        return ParameterTreeUtils::domainNameToParameterName(domainName, child);

    return {};
}

const SessionItem* ParticleDistributionItem::childParticle() const
{
    if (getItems(T_PARTICLES).size() == 0)
        return nullptr;

    Q_ASSERT(getItems(T_PARTICLES).size() == 1);
    return getItems(T_PARTICLES).front();
}
