// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupProperty.cpp
//! @brief     Implements class GroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupProperty.h"
#include "ItemFactory.h"

GroupProperty::GroupProperty()
    : m_groupItem(nullptr)
{
}

SessionItem* GroupProperty::currentItem()
{
    return m_groupItem ? m_groupItem->getChildOfType(this->currentType()) : nullptr;
}

void GroupProperty::setGroupItem(SessionItem* groupItem)
{
    Q_ASSERT(groupItem);
    m_groupItem = groupItem;
    SessionItem* item = createCorrespondingItem();
    m_groupItem->insertItem(-1, item);
}

QString GroupProperty::currentType() const
{
    return m_current_type;
}

void GroupProperty::setCurrentType(const QString& type)
{
    if (type == currentType())
        return;

    SessionItem* prevItem = currentItem();
    m_current_type = type;

    if (m_groupItem) {
        if (auto item = m_groupItem->getChildOfType(m_current_type)) {
            item->setVisible(true);
            item->setEnabled(true);
        } else {
            SessionItem* new_item = createCorrespondingItem();
            m_groupItem->insertItem(-1, new_item);
        }

        if (prevItem) {
            prevItem->setVisible(false);
            prevItem->setEnabled(false);
        }

        m_groupItem->emitDataChanged();
    }
}

int GroupProperty::currentIndex() const
{
    return toIndex(m_current_type);
}

void GroupProperty::setCurrentIndex(int index)
{
    setCurrentType(toString(index));
}

QString GroupProperty::currentLabel() const
{
    return itemLabels().at(currentIndex());
}

QStringList GroupProperty::itemTypes() const
{
    return m_groupInfo.itemTypes();
}

QStringList GroupProperty::itemLabels() const
{
    return m_groupInfo.itemLabels();
}

void GroupProperty::setGroupInfo(GroupInfo groupInfo)
{
    m_groupInfo = std::move(groupInfo);
    setCurrentType(m_groupInfo.defaultType());
}

SessionItem* GroupProperty::createCorrespondingItem()
{
    return ItemFactory::createItem(currentType());
}

int GroupProperty::toIndex(const QString& type) const
{
    return itemTypes().indexOf(type);
}

QString GroupProperty::toString(int index) const
{
    return itemTypes().at(index);
}
