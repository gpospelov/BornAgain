#include "FancyGroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"


FancyGroupProperty::FancyGroupProperty(const QString &group_name)
    : m_group_name(group_name)
    , m_group_type(UndefinedGroupType)
    , m_parent(0)
{

}

FancyGroupProperty::GroupType FancyGroupProperty::type() const
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
    if(type() == FixedGroupType)
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
    m_group_map[m_value] = value_label;
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

QVariant FancyGroupProperty::getVariant() {
    QVariant result;
    result.setValue(this);
    return result;
}


void FancyGroupProperty::setGroupMap(const QMap<QString, QString> &group_map)
{
    m_group_map = group_map;
    setValue(m_group_map.begin().key());
}

