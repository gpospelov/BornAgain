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
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "DomainObjectBuilder.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include <boost/scoped_ptr.hpp>

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER =
        "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::P_CACHED_SELECTED_PARAMETER =
        "Cached selected parameter name";
const QString ParticleDistributionItem::NO_SELECTION = "None";
const QString ParticleDistributionItem::P_ABUNDANCE = "Abundance";

ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleDistributionType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    registerProperty(P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));

    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0, 1);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0, 1);

    registerProperty(P_CACHED_SELECTED_PARAMETER, QString("None"),
                     PropertyAttribute::hiddenProperty());

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
    item->setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DISABLED);
}

void ParticleDistributionItem::onPropertyChange(const QString &name)
{
    ParameterizedItem::onPropertyChange(name);
    if (name == P_DISTRIBUTED_PARAMETER
            && isRegisteredProperty(P_DISTRIBUTED_PARAMETER) ) {
        QVariant par_var = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
        ComboProperty par_prop = par_var.value<ComboProperty>();
        if (par_prop.getValue() != NO_SELECTION) {
            setRegisteredProperty(P_CACHED_SELECTED_PARAMETER,
                                  par_prop.getValue());
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
    if (!isRegisteredProperty(P_DISTRIBUTED_PARAMETER)) return;
    QVariant par_prop = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
    QString selected_par = par_prop.value<ComboProperty>().getValue();
    QString cached_par =
            getRegisteredProperty(P_CACHED_SELECTED_PARAMETER).toString();
    ComboProperty updated_prop;
    QStringList par_names = getChildParameterNames();
    par_names.removeAll(ParticleItem::P_ABUNDANCE);
    updated_prop = ComboProperty(par_names);
    if (updated_prop.getValues().contains(cached_par)) {
        updated_prop.setValue(cached_par);
    } else if (updated_prop.getValues().contains(selected_par)) {
        updated_prop.setValue(selected_par);
    } else {
        updated_prop.setValue(NO_SELECTION);
    }
    if (updated_prop.getValue() != NO_SELECTION) {
        setRegisteredProperty(P_CACHED_SELECTED_PARAMETER,
                              updated_prop.getValue());
    }
    setRegisteredProperty(P_DISTRIBUTED_PARAMETER, updated_prop.getVariant());
}

QStringList ParticleDistributionItem::getChildParameterNames() const
{
    QStringList result;
    QList<ParameterizedItem *> children = childItems();
    if (children.size()>1) {
        throw GUIHelpers::Error("ParticleDistributionItem::getChildParameterNames()"
                                " -> Error! More than one child item");
    }
    if (children.size()==0) {
        result << NO_SELECTION;
        return result;
    }
    double depth(0.0), abundance(0.0);
    ParameterizedItem *child = children[0];
    DomainObjectBuilder builder;
    if (child->modelType() == Constants::ParticleType) {
        boost::scoped_ptr<Particle> particle(builder.buildParticle(*child, depth, abundance));
        if (particle.get()) {
            boost::scoped_ptr<ParameterPool> pool(particle->createParameterTree());
            result << extractFromParameterPool(pool.get());
        }
    } else if (child->modelType() == Constants::ParticleCoreShellType) {
        boost::scoped_ptr<ParticleCoreShell> coreshell(
                    builder.buildParticleCoreShell(*child, depth, abundance));
        if (coreshell.get()) {
            boost::scoped_ptr<ParameterPool> pool(coreshell->createParameterTree());
            result << extractFromParameterPool(pool.get());
        }
    } else {
        throw GUIHelpers::Error("ParticleDistributionItem::getChildParameterNames()"
                                " -> Error! Child not of valid type");
    }

    result.prepend(NO_SELECTION);
    return result;
}

QStringList ParticleDistributionItem::extractFromParameterPool(const ParameterPool *pool) const
{
    QStringList result;
    std::vector<std::string> par_names = pool->getParameterNames();
    for (size_t i=0; i<par_names.size(); ++i) {
        result << QString(par_names[i].c_str());
    }
    return result;
}
