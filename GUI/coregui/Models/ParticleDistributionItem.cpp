// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleDistributionItem.cpp
//! @brief     Implements class ParticleDistributionItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ComboProperty.h"

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER =
        "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::P_SAMPLE_NUMBER = "Number of samples";
const QString ParticleDistributionItem::P_SIGMA_FACTOR = "Sigma factor";
const QString ParticleDistributionItem::P_CACHED_SELECTED_PARAMETER =
        "Cached selected parameter name";
const QString ParticleDistributionItem::NO_SELECTION = "None";

ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleDistributionType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);
    registerProperty(P_SAMPLE_NUMBER, 5);
    registerProperty(P_SIGMA_FACTOR, 2.0);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0);

    registerProperty(P_CACHED_SELECTED_PARAMETER, QString("None"),
                     PropertyAttribute::hiddenProperty());

    ComboProperty par_prop;
    registerProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant());
    updateParameterList();
}

ParticleDistributionItem::~ParticleDistributionItem()
{
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
    if (childItems().size()>0) {
        QStringList par_names = childItems()[0]->getParameterTreeList();
        par_names.prepend(NO_SELECTION);
        par_names.removeAll(ParticleItem::P_ABUNDANCE);
        updated_prop = ComboProperty(par_names);
    } else {
        updated_prop << NO_SELECTION;
    }
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
