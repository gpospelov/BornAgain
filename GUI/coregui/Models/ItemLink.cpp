// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ItemLink.cpp
//! @brief     Implements class ItemLink
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemLink.h"
#include "AngleProperty.h"
#include "ScientificDoubleProperty.h"

ItemLink::ItemLink(const QString property_name, SessionItem *item)
    : m_property_name(property_name)
    , m_item(item)
    , m_value(0)
{

}

void ItemLink::setItem(QString property_name, SessionItem *item)
{
    m_property_name = property_name;
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
    QVariant variant = m_item->getItemValue(m_property_name);
    if(variant.typeName() == QString("double")) {
        variant.setValue(m_value);
        return variant;
    }
    else if(variant.typeName() == QString("AngleProperty")) {
        AngleProperty angle_property = variant.value<AngleProperty>();
        angle_property.setValue(m_value);
        return angle_property.getVariant();
    }
    else if(variant.typeName() == QString("ScientificDoubleProperty")) {
        ScientificDoubleProperty scdouble_property = variant.value<ScientificDoubleProperty>();
        scdouble_property.setValue(m_value);
        return scdouble_property.getVariant();
    }

    return QVariant();
}

void ItemLink::updateItem()
{
    getItem()->setItemValue(getPropertyName(), getVariant());
}

