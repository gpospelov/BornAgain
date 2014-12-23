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
#include "ComboProperty.h"

const QString ParticleDistributionItem::P_DISTRIBUTED_PARAMETER =
        "Distributed parameter";
const QString ParticleDistributionItem::P_DISTRIBUTION = "Distribution";
const QString ParticleDistributionItem::P_SAMPLE_NUMBER = "Number of samples";
const QString ParticleDistributionItem::P_SIGMA_FACTOR = "Sigma factor";


ParticleDistributionItem::ParticleDistributionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleDistributionType);
    setItemPort(ParameterizedItem::PortInfo::Port0);

    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionGroup);
    registerProperty(P_SAMPLE_NUMBER, 5);
    registerProperty(P_SIGMA_FACTOR, 2.0);

    addToValidChildren(Constants::ParticleType, PortInfo::Port0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::Port0);

    ComboProperty par_prop;
    registerProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant());
    updateParameterList();
}

ParticleDistributionItem::~ParticleDistributionItem()
{
}

void ParticleDistributionItem::updateParameterList()
{
    QVariant par_prop = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
    QString selected_par = par_prop.value<ComboProperty>().getValue();
    removeRegisteredProperty(P_DISTRIBUTED_PARAMETER);
    ComboProperty updated_prop;
    if (childItems().size()>0) {
        QStringList par_names = childItems()[0]->getParameterTreeList();
        par_names.prepend(QString("None"));
        updated_prop = ComboProperty(par_names);
    } else {
        updated_prop << "None";
    }
    if (updated_prop.getValues().contains(selected_par)) {
        updated_prop.setValue(selected_par);
    } else {
        updated_prop.setValue(QString("None"));
    }
    registerProperty(P_DISTRIBUTED_PARAMETER, updated_prop.getVariant());
}
