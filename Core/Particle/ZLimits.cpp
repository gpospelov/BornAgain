// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/ZLimits.cpp
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "ZLimits.h"
#include <algorithm>
#include <stdexcept>

ZLimits::ZLimits()
    : m_lower { true, 0 }
    , m_upper { true, 0 }
{}

ZLimits::ZLimits(double min, double max)
    : ZLimits( { false, min }, { false, max } )
{}

ZLimits::ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit)
    : m_lower(std::move(lower_limit))
    , m_upper(std::move(upper_limit))
{
    if (!lower_limit.m_limitless && !upper_limit.m_limitless
        && lower_limit.m_value > upper_limit.m_value)
        throw std::runtime_error("ZLimits constructor: "
                                 "lower limit bigger than upper limit.");
}

OneSidedLimit ZLimits::lowerLimit() const
{
    return m_lower;
}

OneSidedLimit ZLimits::upperLimit() const
{
    return m_upper;
}

ZLimits Union(const ZLimits& left, const ZLimits& right)
{
    auto lower = MinLimit(left.lowerLimit(), right.lowerLimit());
    auto upper = MaxLimit(left.upperLimit(), right.upperLimit());
    return ZLimits(lower, upper);
}

OneSidedLimit MinLimit(const OneSidedLimit& left, const OneSidedLimit& right)
{
    if (left.m_limitless || right.m_limitless)
        return { true, 0 };
    return { false, std::min(left.m_value, right.m_value) };
}

OneSidedLimit MaxLimit(const OneSidedLimit& left, const OneSidedLimit& right)
{
    if (left.m_limitless || right.m_limitless)
        return { true, 0 };
    return { false, std::max(left.m_value, right.m_value) };
}
