// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GroupItem.h"

const QString GroupItem::T_ITEMS = "Item tag";

GroupItem::GroupItem()
    :SessionItem(Constants::GroupItemType)
{
    registerTag(T_ITEMS);
    setDefaultTag(T_ITEMS);
}

void GroupItem::setGroup(GroupProperty_t group)
{
    group->setGroupItem(this);
    setValue(QVariant::fromValue(group));
}

GroupProperty_t GroupItem::group() const
{
    return value().value<GroupProperty_t>();
}

SessionItem *GroupItem::getCurrentItem()
{
    return group()->getCurrentItem();
}
