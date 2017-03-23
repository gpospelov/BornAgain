// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/ZLimits.h
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ZLIMITS_H
#define ZLIMITS_H

//! Helper class that represents a onesided limit
//!
//! @ingroup intern

struct OneSidedLimit
{
    bool m_limitless;
    double m_value;
};

//! Class that contains upper and lower limits of the z-coordinate for the slicing of
//! form factors.
//!
//! @ingroup intern

class ZLimits
{
public:
    ZLimits();
    ZLimits(double min, double max);
    ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit);

    OneSidedLimit lowerLimit() const;
    OneSidedLimit upperLimit() const;
private:
    OneSidedLimit m_lower;
    OneSidedLimit m_upper;
};

ZLimits Union(const ZLimits& left, const ZLimits& right);
OneSidedLimit MinLimit(const OneSidedLimit& left, const OneSidedLimit& right);
OneSidedLimit MaxLimit(const OneSidedLimit& left, const OneSidedLimit& right);

#endif // ZLIMITS_H
