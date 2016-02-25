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
#include <QDebug>

PropertyAttribute::PropertyAttribute(PropertyAttribute::Appearance appearance,
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

PropertyAttribute PropertyAttribute::labeled(const QString &label)
{
    return PropertyAttribute(VISIBLE, AttLimits::lowerLimited(0.0), 2, label);
}

PropertyAttribute::Appearance PropertyAttribute::getAppearance() const
{
    return m_appearance;
}

void PropertyAttribute::setAppearance(PropertyAttribute::Appearance appearance)
{
    m_appearance = appearance;
}

AttLimits PropertyAttribute::getLimits() const
{
    return m_limits;
}

PropertyAttribute& PropertyAttribute::setLimits(const AttLimits &limits)
{
    m_limits = limits;
    return *this;
}

PropertyAttribute &PropertyAttribute::lowerLimited(double value)
{
    m_limits = AttLimits::lowerLimited(value);
    return *this;
}

PropertyAttribute &PropertyAttribute::upperLimited(double value)
{
    m_limits = AttLimits::upperLimited(value);
    return *this;
}

PropertyAttribute &PropertyAttribute::limited(double left_bound_value, double right_bound_value)
{
    m_limits = AttLimits::limited(left_bound_value, right_bound_value);
    return *this;
}

PropertyAttribute &PropertyAttribute::limitless()
{
    m_limits = AttLimits::limitless();
    return *this;
}

int PropertyAttribute::getDecimals() const
{
    return m_decimals;
}

PropertyAttribute &PropertyAttribute::setDecimals(int decimals)
{
    m_decimals = decimals;
    return *this;
}

QString PropertyAttribute::getLabel() const
{
    return m_label;
}

PropertyAttribute &PropertyAttribute::setLabel(const QString &label)
{
    m_label = label;
    return *this;
}

QString PropertyAttribute::getToolTip() const
{
    return m_tooltip;
}

PropertyAttribute &PropertyAttribute::setToolTip(const QString &tooltip)
{
    m_tooltip = tooltip;
    return *this;
}

bool PropertyAttribute::isVisible() const
{
    return !isHidden();
}

PropertyAttribute &PropertyAttribute::setVisible()
{
    m_appearance &= ~PropertyAttribute::HIDDEN;
    return *this;
}

bool PropertyAttribute::isHidden() const
{
    return m_appearance.testFlag(PropertyAttribute::HIDDEN);
}

PropertyAttribute& PropertyAttribute::setHidden()
{
    m_appearance |= PropertyAttribute::HIDDEN;
    return *this;
}

bool PropertyAttribute::isDisabled() const
{
    return m_appearance.testFlag(PropertyAttribute::DISABLED);
}

PropertyAttribute& PropertyAttribute::setDisabled()
{
    m_appearance |= PropertyAttribute::DISABLED;
    return *this;
}

PropertyAttribute &PropertyAttribute::setEnabled()
{
    m_appearance &= ~PropertyAttribute::DISABLED;
    return *this;
}

bool PropertyAttribute::isReadOnly() const
{
    return m_appearance.testFlag(PropertyAttribute::READONLY);
}

PropertyAttribute& PropertyAttribute::setReadOnly()
{
    m_appearance |= PropertyAttribute::READONLY;
    return *this;
}



