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
    setItemName(Constants::ParticleDistributionType);

    registerProperty(ParticleItem::P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0), 3));
    registerGroupProperty(ParticleItem::P_POSITION, Constants::VectorType);

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
        item->setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
        item->setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DISABLED);
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

void ParticleDistributionItem::updateParameterList()
{
    if (!isRegisteredProperty(P_DISTRIBUTED_PARAMETER))
        return;
    QVariant par_prop = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
    QString selected_par = par_prop.value<ComboProperty>().getValue();
    QString cached_par = par_prop.value<ComboProperty>().getCachedValue();
    ComboProperty updated_prop;
    QStringList par_names = getChildParameterNames();
    par_names.removeAll(ParticleItem::P_ABUNDANCE);
    updated_prop = ComboProperty(par_names);
    updated_prop.setCachedValue(cached_par);
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
        throw GUIHelpers::Error("ParticleDistributionItem::getChildParameterNames()"
                                " -> Error! More than one child item");
    }
    if (children.size() == 0) {
        result << NO_SELECTION;
        return result;
    }
    double abundance(0.0);
    DomainObjectBuilder builder;
    boost::scoped_ptr<ParticleDistribution> P_part_distr;
    try {
        P_part_distr.reset(builder.buildParticleDistribution(*this, abundance, true));
    } catch(const std::exception &ex) {
        qDebug() << "ParticleDistributionItem::getChildParameterNames(): "
                 << "domain particle could not be build: "
                 << QString::fromStdString(ex.what());
    }
    if (P_part_distr.get()) {
        boost::scoped_ptr<ParameterPool> P_pool(P_part_distr->createDistributedParameterPool());
        result << extractFromParameterPool(P_pool.get());
    }

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
