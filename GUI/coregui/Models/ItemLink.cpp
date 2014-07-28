#include "ItemLink.h"


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
