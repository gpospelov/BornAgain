// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FancyGroupProperty.cpp
//! @brief     Implements class FancyGroupProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FancyGroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"


FancyGroupProperty::FancyGroupProperty(const QString &group_name)
    : m_group_name(group_name)
    , m_group_type(UNDEFINED)
    , m_parent(0)
{

}

FancyGroupProperty::EGroupType FancyGroupProperty::type() const
{
    return m_group_type;
}

void FancyGroupProperty::setParent(ParameterizedItem *parent)
{
    Q_ASSERT(parent);
    m_parent = parent;
    m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
}

ParameterizedItem *FancyGroupProperty::createCorrespondingItem()
{
    ParameterizedItem *result = ItemFactory::createItem(getCurrentType());
    if(type() == FIXED)
        setCurrentLabel(result->getItemLabel());
    return result;
}

QString FancyGroupProperty::getGroupName() const
{
    return m_group_name;
}

QString FancyGroupProperty::getCurrentType() const
{
    return m_current_type;
}

void FancyGroupProperty::setCurrentType(const QString &value)
{
    if(value == getCurrentType()) return;

    m_current_type = value;

    if(m_parent) {
        m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
        //emit m_parent->subItemChanged(getGroupName());
    }
}

QString FancyGroupProperty::getCurrentLabel() const
{
    return m_type_label_map.at(m_current_type);
}

void FancyGroupProperty::setCurrentLabel(const QString &value_label)
{
    if(type() == FIXED) {
        m_type_label_map[m_current_type] = value_label;
        if(m_parent) emit m_parent->propertyChanged(getGroupName());
    }
}

QStringList FancyGroupProperty::getTypes() const
{
    QStringList result;
    for (const auto& key_value_pair : m_type_label_map) {
        result << key_value_pair.first;
    }
    return result;
}

QStringList FancyGroupProperty::getLabels() const
{
    QStringList result;
    for (const auto& key_value_pair : m_type_label_map) {
        result << key_value_pair.second;
    }
    return result;
}

int FancyGroupProperty::index() const
{
    return toIndex(m_current_type);
}

int FancyGroupProperty::toIndex(const QString &value) const
{
    QStringList name_list = getTypes();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString FancyGroupProperty::toString(int index) const
{
    QStringList name_list = getTypes();
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}


void FancyGroupProperty::setGroupMap(const QMap<Constants::ModelType, QString> &group_map)
{
    m_type_label_map.clear();
    for (QMap<Constants::ModelType, QString>::ConstIterator it = group_map.begin();
         it != group_map.end(); ++it) {
        m_type_label_map[it.key()] = it.value();
    }
    setCurrentType(m_type_label_map.begin()->first);
}

void FancyGroupProperty::setGroupType(FancyGroupProperty::EGroupType group_type)
{
    m_group_type = group_type;
}

