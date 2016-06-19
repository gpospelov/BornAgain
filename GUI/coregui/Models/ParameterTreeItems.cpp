// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeItems.cpp
//! @brief     Implements classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTreeItems.h"
#include "ModelPath.h"
#include "SessionModel.h"

// ----------------------------------------------------------------------------

ParameterLabelItem::ParameterLabelItem()
    : SessionItem(Constants::ParameterLabelType)
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList()
                << Constants::ParameterLabelType << Constants::ParameterType);
    setDefaultTag(T_CHILDREN);
}

const QString ParameterItem::P_LINK = "Link";
const QString ParameterItem::P_BACKUP = "Backup";
const QString ParameterItem::P_DOMAIN = "Domain";
ParameterItem::ParameterItem()
    : SessionItem(Constants::ParameterType)
{
    // Link to original PropertyItem in one of components of MultiLayerItem or InstrumentItem
    addProperty(P_LINK, "");
    // The back up value of PropertyItem to be able to reset parameter tuning tree to initial state
    addProperty(P_BACKUP, 0.0);
    // The domain name of corresponding ISample's registered parameter
    addProperty(P_DOMAIN, "");
}

// ----------------------------------------------------------------------------

//! Sets current value to the original PropertyItem of MultiLayerItem/InstrumentItem.

void ParameterItem::propagateValueLink(bool backup)
{
    if (backup)
        setValue(getItemValue(P_BACKUP));
    SessionItem *item = getLinkedItem();
    if (item)
        item->setValue(value());
}

//! Returns corresponding linked item in MultiLayerItem/IsntrumentItem

SessionItem *ParameterItem::getLinkedItem()
{
    QString link = getItemValue(P_LINK).toString();
    SessionItem *cur = this;
    while (cur && cur->modelType() != Constants::JobItemType) {
        cur = cur->parent();
    }
    link = cur->itemName() + "/" + link;
    return model()->itemForIndex(ModelPath::getIndexFromPath(model(), link));
}

// ----------------------------------------------------------------------------

ParameterContainerItem::ParameterContainerItem()
    : SessionItem(Constants::ParameterContainerType)
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList() << Constants::ParameterLabelType);
    setDefaultTag(T_CHILDREN);
}
