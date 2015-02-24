// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCollectionItem.cpp
//! @brief     Implements class ParticleCollectionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCollectionItem.h"
#include "ParticleItem.h"
#include "ComboProperty.h"

const QString ParticleCollectionItem::P_DISTRIBUTED_PARAMETER =
        "Distributed parameter";
const QString ParticleCollectionItem::NO_SELECTION = "No selection";

ParticleCollectionItem::ParticleCollectionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleDistributionType, parent)
{
    setItemName(Constants::ParticleCollectionType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0);

    ComboProperty par_prop;
    registerProperty(P_DISTRIBUTED_PARAMETER, par_prop.getVariant());
    updateParameterList();
}

ParticleCollectionItem::~ParticleCollectionItem()
{
}

void ParticleCollectionItem::onPropertyChange(const QString &name)
{
    ParameterizedItem::onPropertyChange(name);
    if (name == P_DISTRIBUTED_PARAMETER
            && isRegisteredProperty(P_DISTRIBUTED_PARAMETER) ) {
        QVariant par_var = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
        ComboProperty par_prop = par_var.value<ComboProperty>();
    }
}

void ParticleCollectionItem::onChildPropertyChange()
{
    updateParameterList();
    ParameterizedItem::onChildPropertyChange();
}

void ParticleCollectionItem::updateParameterList()
{
    if (!isRegisteredProperty(P_DISTRIBUTED_PARAMETER)) return;
    QVariant par_prop = getRegisteredProperty(P_DISTRIBUTED_PARAMETER);
    QString selected_par = par_prop.value<ComboProperty>().getValue();
    ComboProperty updated_prop;
    if (childItems().size()>0) {
        QStringList par_names = childItems()[0]->getParameterTreeList();
        par_names.prepend(NO_SELECTION);
        par_names.removeAll(ParticleItem::P_ABUNDANCE);
        updated_prop = ComboProperty(par_names);
    } else {
        updated_prop << NO_SELECTION;
    }
    setRegisteredProperty(P_DISTRIBUTED_PARAMETER, updated_prop.getVariant());
}
