#include "SelectableGroupProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include <QDebug>

ParameterizedItem *SelectableGroupProperty::createCorrespondingItem(const QString &name)
{
    if( !name.isEmpty() ) m_value = name;

    if(!m_group_map.contains(getValue()))
        throw GUIHelpers::Error("SelectableGroupProperty::createCorrespondingItem() -> Error. Not existing name"+name);

    return ItemFactory::createItem(getValue());
}

void SelectableGroupProperty::setGroupMap(const QMap<QString, QString> &group_map)
{
    m_group_map = group_map;
    setValue(m_group_map.begin().key());
}

QStringList SelectableGroupProperty::getValues() const
{
    return m_group_map.keys();
}

QStringList SelectableGroupProperty::getValueLabels() const
{
    return m_group_map.values();
}

QString SelectableGroupProperty::getValueLabel() const
{
    return m_group_map[m_value];
}

void SelectableGroupProperty::setValue(const QString &value)
{
    qDebug() << "SelectableGroupProperty::setValue() -> " << value;
    if(value == getValue()) return;

    FancyGroupProperty::setValue(value);

    if(m_parent) {
        qDebug() << "   before";
        m_parent->print();
        m_parent->addPropertyItem(getGroupName(), createCorrespondingItem());
        emit m_parent->propertyItemChanged(getGroupName());
        qDebug() << "   after";
        m_parent->print();

    }
}

