// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialProperty.cpp
//! @brief     Implements class MaterialProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialProperty.h"
#include "MaterialItem.h"
#include "MaterialModel.h"

MaterialProperty::MaterialProperty(const QString& identifier)
    : m_identifier(identifier)
    , m_name("Undefined")
    , m_color(Qt::red)
{}

QString MaterialProperty::getName() const
{
    return m_name;
}

void MaterialProperty::setName(const QString& name)
{
    m_name = name;
}


QColor MaterialProperty::getColor() const
{
    return m_color;
}

void MaterialProperty::setColor(const QColor& color)
{
    m_color = color;
}


QPixmap MaterialProperty::getPixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(getColor());
    return pixmap;
}

bool MaterialProperty::isDefined() const
{
    return !m_identifier.isEmpty();
}
