// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItem.cpp
//! @brief     Implements class GroupItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupItem.h"
#include "GUIHelpers.h"

const QString GroupItem::T_ITEMS = "Item tag";

GroupItem::GroupItem() : SessionItem(Constants::GroupItemType)
{
    registerTag(T_ITEMS);
    setDefaultTag(T_ITEMS);
}

void GroupItem::setGroup(GroupProperty_t group)
{
    if (value().isValid())
        throw GUIHelpers::Error("GroupItem::setGroup() -> Error. Attempt to set group twice.");

    group->setGroupItem(this);
    setValue(QVariant::fromValue(group));
}

GroupProperty_t GroupItem::groupProperty() const
{
    return value().value<GroupProperty_t>();
}

SessionItem* GroupItem::currentItem() const
{
    return value().isValid() ? groupProperty()->currentItem() : nullptr;
}

QString GroupItem::currentType() const
{
    return groupProperty()->currentType();
}

SessionItem* GroupItem::setCurrentType(const QString& modelType)
{
    GroupProperty_t group_property = groupProperty();
    group_property->setCurrentType(modelType);

    return currentItem();
}

QStringList GroupItem::translateList(const QStringList& list) const
{
    // we do not add here the name of itself
    return list;
}
