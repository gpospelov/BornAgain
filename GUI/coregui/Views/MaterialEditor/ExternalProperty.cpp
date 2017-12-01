// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/ExternalProperty.cpp
//! @brief     Implements class ExternalProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ExternalProperty.h"
#include "MaterialItem.h"
#include "MaterialModel.h"

ExternalProperty::ExternalProperty(const QString& identifier)
    : m_identifier(identifier)
    , m_name("Undefined")
    , m_color(Qt::red)
{}

QString ExternalProperty::getName() const
{
    return m_name;
}

void ExternalProperty::setName(const QString& name)
{
    m_name = name;
}


QColor ExternalProperty::getColor() const
{
    return m_color;
}

void ExternalProperty::setColor(const QColor& color)
{
    m_color = color;
}


QPixmap ExternalProperty::getPixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(getColor());
    return pixmap;
}

bool ExternalProperty::isValid() const
{
    return !m_identifier.isEmpty();
}
