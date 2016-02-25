// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupProperty.cpp
//! @brief     Implements class GroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include <QDebug>


GroupProperty::GroupProperty(QString group_name)
    : m_group_name(std::move(group_name))
    , m_group_type(UNDEFINED)
    , m_parent(0)
{
}

GroupProperty::EGroupType GroupProperty::type() const
{
    return m_group_type;
}

ParameterizedItem *GroupProperty::getCurrentItem()
{
    qDebug() << "GroupProperty::getCurrentItem()" << m_parent;
    if(m_parent) return m_parent->getChildByName(this->getCurrentType());
    return 0;
//    Q_ASSERT(m_parent);
//    return m_parent->getChildByName(this->getCurrentType());
}

void GroupProperty::setParent(ParameterizedItem *parent)
{
    Q_ASSERT(parent);
    m_parent = parent;
    ParameterizedItem *item = createCorrespondingItem();
//    item->setName(getGroupName());
    m_parent->insertChildItem(-1, item);
}

ParameterizedItem *GroupProperty::createCorrespondingItem()
{
    qDebug() << "GroupProperty::createCorrespondingItem()" << getCurrentType();
    ParameterizedItem *result = ItemFactory::createItem(getCurrentType());
    if(type() == FIXED) {
        setCurrentLabel(result->itemLabel());
    }
    return result;
}

QString GroupProperty::getGroupName() const
{
    return m_group_name;
}

QString GroupProperty::getCurrentType() const
{
    return m_current_type;
}

void GroupProperty::setCurrentType(const QString &type)
{
    qDebug() << "GGG GroupProperty::setCurrentType(const QString &type)" << type;
    if(type == getCurrentType()) return;

    ParameterizedItem *prevItem = getCurrentItem();

    m_current_type = type;

    if(m_parent) {

        if (auto item = m_parent->getChildByName(m_current_type)) {
            qDebug() << "GGG GroupProperty::setCurrentType 1.1 picking existing new item" << item << item->displayName();
//            item->getAttribute().setVisible();
            item->getAttribute().setEnabled();
            item->emitValueChanged(QVector<int>() << Qt::UserRole);
        } else {
            ParameterizedItem *new_item = createCorrespondingItem();
            qDebug() << "GGG GroupProperty::setCurrentType 1.2 creating new item" << new_item << new_item->displayName();
            m_parent->insertChildItem(-1, new_item);
        }

        if(prevItem) {
            qDebug() << "GGG GroupProperty::setCurrentType 1.3 disabline previous item" << prevItem << prevItem->displayName();
//            prevItem->getAttribute().setHidden();
            prevItem->getAttribute().setDisabled();
            prevItem->emitValueChanged(QVector<int>() << Qt::UserRole);
        }

        m_parent->emitValueChanged();
    }
}

QString GroupProperty::getCurrentLabel() const
{
    return m_type_label_map.at(m_current_type);
}

void GroupProperty::setCurrentLabel(const QString &label)
{
    if(type() == FIXED) {
        m_type_label_map[m_current_type] = label;
        if(m_parent) emit m_parent->propertyChanged(getGroupName());
    }
}

QStringList GroupProperty::getTypes() const
{
    QStringList result;
    for (const auto& key_value_pair : m_type_label_map) {
        result << key_value_pair.first;
    }
    return result;
}

QStringList GroupProperty::getLabels() const
{
    QStringList result;
    for (const auto& key_value_pair : m_type_label_map) {
        result << key_value_pair.second;
    }
    return result;
}

int GroupProperty::index() const
{
    return toIndex(m_current_type);
}

int GroupProperty::toIndex(const QString &type) const
{
    QStringList name_list = getTypes();
    for (int i = 0; i < name_list.size(); ++i) {
        if (type == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString GroupProperty::toString(int index) const
{
    QStringList name_list = getTypes();
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}

void GroupProperty::setGroupMap(std::map<QString, QString> group_map)
{
    m_type_label_map = std::move(group_map);
    setCurrentType(m_type_label_map.begin()->first);
}

void GroupProperty::setGroupType(GroupProperty::EGroupType group_type)
{
    m_group_type = group_type;
}

