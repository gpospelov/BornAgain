// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FancyGroupProperty.cpp
//! @brief     Implements class FancyGroupProperty
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
    ParameterizedItem *result = ItemFactory::createItem(getValue());
    if(type() == FIXED)
        setValueLabel(result->getItemLabel());
    return result;
}

QString FancyGroupProperty::getGroupName() const
{
    return m_group_name;
}

QString FancyGroupProperty::getValue() const
{
    return m_value;
}

void FancyGroupProperty::setValue(const QString &value)
{
    if(value == getValue()) return;

    m_value = value;

    if(m_parent) {
        m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
        emit m_parent->propertyItemChanged(getGroupName());
    }
}

QString FancyGroupProperty::getValueLabel() const
{
    return m_group_map[m_value];
}

void FancyGroupProperty::setValueLabel(const QString &value_label)
{
    if(type() == FIXED) {
        m_group_map[m_value] = value_label;
        if(m_parent) emit m_parent->propertyChanged(getGroupName());
    }
}


QStringList FancyGroupProperty::getValues() const
{
    return m_group_map.keys();
}

QStringList FancyGroupProperty::getValueLabels() const
{
    return m_group_map.values();
}

int FancyGroupProperty::index() const
{
    return toIndex(m_value);
}

int FancyGroupProperty::toIndex(const QString &value) const
{
    QStringList name_list = getValues();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString FancyGroupProperty::toString(int index) const
{
    QStringList name_list = getValues();
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}


void FancyGroupProperty::setGroupMap(const QMap<QString, QString> &group_map)
{
    m_group_map = group_map;
    setValue(m_group_map.begin().key());
}

void FancyGroupProperty::setGroupType(FancyGroupProperty::EGroupType group_type)
{
    m_group_type = group_type;
}

