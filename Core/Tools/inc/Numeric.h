// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NUMERIC_H_
#define NUMERIC_H_

#include <limits>
#include <cmath>
#include <algorithm>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric {

static const double required_precision = 1.e-4;

static const double double_epsilon = std::numeric_limits<double>::epsilon();

//! threshold on probability value during calculation of weighted form factor
static const double probthreshold = 0.0000000001;

//! compare two doubles
inline bool areAlmostEqual(double a, double b, double tolerance_factor=1.0)
    { return std::abs(a-b) < tolerance_factor*Numeric::double_epsilon; }


//! calculates safe ratio of two doubles a/b
inline double get_safe_ratio(double a, double b) {
    double result(0.0);
    if( std::abs(a) <= Numeric::double_epsilon && std::abs(b) <= Numeric::double_epsilon) {
        result = 0.0;
    } else if (std::abs(b) <= Numeric::double_epsilon) {
        result = double(a)/Numeric::double_epsilon;
    } else {
        result = double(a/b);
    }
    return result;
}

//! calculates safe relative difference (a-b)/b
inline double get_relative_difference(double a, double b)
{
    return get_safe_ratio(a-b, b);
}

} // Numeric namespace

#endif /* NUMERIC_H_ */


