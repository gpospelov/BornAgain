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

GroupProperty::GroupProperty(QString group_name)
    : m_group_name(std::move(group_name)), m_groupItem(0)
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

QString GroupProperty::getCurrentLabel() const
{
    auto labels = getLabels();
    int ind = index();
    return labels.at(ind);
}

QStringList GroupProperty::getTypes() const
{
    return m_groupInfo.itemTypes();
}

QStringList GroupProperty::getLabels() const
{
    return m_groupInfo.itemLabels();
}

int GroupProperty::index() const
{
    return toIndex(m_current_type);
}

int GroupProperty::toIndex(const QString& type) const
{
    return getTypes().indexOf(type);
}

QString GroupProperty::toString(int index) const
{
    QStringList name_list = getTypes();
    if (index < 0 || index >= name_list.size())
        return QString();

    return name_list[index];
}

void GroupProperty::setGroupInfo(const GroupInfo& groupInfo)
{
    m_groupInfo = groupInfo;
    setCurrentType(m_groupInfo.itemTypes().front());
}

SessionItem* GroupProperty::createCorrespondingItem()
{
    return ItemFactory::createItem(currentType());
}
