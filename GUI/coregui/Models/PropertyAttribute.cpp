// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PropertyAttribute.cpp
//! @brief     Implements class PropertyAttribute
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PropertyAttribute.h"

PropertyAttribute::PropertyAttribute(PropertyAttribute::EAppearance appearance,
                                     const AttLimits &limits, int decimals, const QString &label,
                                     const QString &tooltip)
    : m_appearance(appearance)
    , m_limits(limits)
    , m_decimals(decimals)
    , m_label(label)
    , m_tooltip(tooltip)
{

}

PropertyAttribute::PropertyAttribute(const AttLimits &limits, int decimals)
    : m_appearance(VISIBLE)
    , m_limits(limits)
    , m_decimals(decimals)
{

}

PropertyAttribute PropertyAttribute::visibleProperty()
{
    return PropertyAttribute(VISIBLE);
}

PropertyAttribute PropertyAttribute::hiddenProperty()
{
    return PropertyAttribute(HIDDEN);
}

PropertyAttribute PropertyAttribute::disabledProperty()
{
    return PropertyAttribute(DISABLED);
}

PropertyAttribute PropertyAttribute::labeled(const QString &label)
{
    return PropertyAttribute(VISIBLE, AttLimits::lowerLimited(0.0), 2, label);
}

PropertyAttribute::EAppearance PropertyAttribute::getAppearance() const
{
    return m_appearance;
}

void PropertyAttribute::setAppearance(PropertyAttribute::EAppearance appearance)
{
    m_appearance = appearance;
}

AttLimits PropertyAttribute::getLimits() const
{
    return m_limits;
}

void PropertyAttribute::setLimits(AttLimits limits)
{
    m_limits = limits;
}

int PropertyAttribute::getDecimals() const
{
    return m_decimals;
}

void PropertyAttribute::setDecimals(int decimals)
{
    m_decimals = decimals;
}

QString PropertyAttribute::getLabel() const
{
    return m_label;
}

void PropertyAttribute::setLabel(const QString &label)
{
    m_label = label;
}

QString PropertyAttribute::getToolTip() const
{
    return m_tooltip;
}

void PropertyAttribute::setToolTip(const QString &tooltip)
{
    m_tooltip = tooltip;
}

bool PropertyAttribute::isHidden() const
{
    return (m_appearance & PropertyAttribute::HIDDEN);
}

bool PropertyAttribute::isDisabled() const
{
    return (m_appearance & PropertyAttribute::DISABLED);
}

bool PropertyAttribute::isReadOnly() const
{
    return (m_appearance & PropertyAttribute::READONLY);
}



