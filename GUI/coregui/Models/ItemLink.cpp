#include "ItemLink.h"


ItemLink::ItemLink(const QString name, ParameterizedItem *item)
    : m_name(name)
    , m_item(item)

{

}

void ItemLink::setItem(QString name, ParameterizedItem *item)
{
    m_name = name;
    m_item = item;
}
