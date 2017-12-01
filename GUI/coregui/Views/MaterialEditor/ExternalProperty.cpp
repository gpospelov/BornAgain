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

ExternalProperty::ExternalProperty()
{}

QString ExternalProperty::identifier() const {
    return m_identifier;
}

void ExternalProperty::setIdentifier(const QString& identifier)
{
    m_identifier = identifier;
}

QString ExternalProperty::text() const
{
    return m_text;
}

void ExternalProperty::setText(const QString& name)
{
    m_text = name;
}


QColor ExternalProperty::color() const
{
    return m_color;
}

void ExternalProperty::setColor(const QColor& color)
{
    m_color = color;
}


QPixmap ExternalProperty::pixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(color());
    return pixmap;
}

//! Returns true if property is in valid state (i.e. have at least one member defined).

bool ExternalProperty::isValid() const
{
    if (m_identifier.isEmpty() && m_text.isEmpty() && !m_color.isValid())
        return false;

    return true;
}

QVariant ExternalProperty::variant() const
{
    QVariant variant;
    variant.setValue(*this);
    return variant;
}

