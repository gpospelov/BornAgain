#include "ItemLink.h"
#include "AngleProperty.h"


ItemLink::ItemLink(const QString name, ParameterizedItem *item)
    : m_name(name)
    , m_item(item)
    , m_value(0)
{

}

void ItemLink::setItem(QString name, ParameterizedItem *item)
{
    m_name = name;
    m_item = item;
}

double ItemLink::getValue() const
{
    return m_value;
}

void ItemLink::setValue(double value)
{
    m_value = value;
}

QVariant ItemLink::getVariant()
{
    QVariant variant = m_item->getRegisteredProperty(m_name);
    if(variant.typeName() == QString("double")) {
        variant.setValue(m_value);
        return variant;
    }
    else if(variant.typeName() == QString("AngleProperty")) {
        AngleProperty angle_property = variant.value<AngleProperty>();
        angle_property.setValue(m_value);
        return angle_property.getVariant();
    }

    return QVariant();
}

void ItemLink::updateItem()
{
    getItem()->setRegisteredProperty(getPropertyName(), getVariant());
}

