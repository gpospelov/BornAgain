#include "FancyGroupProperty.h"
#include "GUIHelpers.h"


FancyGroupProperty::FancyGroupProperty(ParameterizedItem *parent)
    : m_parent(parent)
{

}

ParameterizedItem *FancyGroupProperty::createCorrespondingItem(const QString & /* name */)
{
    return 0;
}

QString FancyGroupProperty::getGroupName() const
{
    return m_group_name;
}

void FancyGroupProperty::setGroupName(const QString &group_name)
{
    m_group_name = group_name;
}

//QString FancyGroupProperty::getGroupLabel() const
//{
//    return m_group_label;
//}

//void FancyGroupProperty::setGroupLabel(const QString &group_label)
//{
//    m_group_label = group_label;
//}

QString FancyGroupProperty::getValue() const
{
    return m_value;
}

void FancyGroupProperty::setValue(const QString &value)
{
    m_value = value;
}

QString FancyGroupProperty::getValueLabel() const
{
    return (m_value_label.isEmpty() ? m_value : m_value_label);
}

void FancyGroupProperty::setValueLabel(const QString &value_label)
{
    m_value_label = value_label;
}

QStringList FancyGroupProperty::getValues() const
{
    throw GUIHelpers::Error("FancyGroupProperty::getValues() -> Error. Not implemented");
}

QStringList FancyGroupProperty::getValueLabels() const
{
    throw GUIHelpers::Error("FancyGroupProperty::getValueLabels() -> Error. Not implemented");
}

void FancyGroupProperty::setParent(ParameterizedItem *parent)
{
    m_parent = parent;
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

