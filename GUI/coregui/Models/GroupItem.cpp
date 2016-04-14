// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupItem.cpp
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
#include <QDebug>

const QString GroupItem::T_ITEMS = "Item tag";

GroupItem::GroupItem()
    :SessionItem(Constants::GroupItemType)
{
    registerTag(T_ITEMS);
    setDefaultTag(T_ITEMS);

    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &name)
    {
        qDebug() << "QQQQ" << item->itemLabel() << name;
        group()->setCurrentLabel(item->itemLabel());
//        qDebug() << "emmiting..." << modelType();
//        emitDataChanged();
//        qDebug() << "...emmited";
    });

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
