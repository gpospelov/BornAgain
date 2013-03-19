// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/Numeric.h 
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//
// ************************************************************************** //

#ifndef NUMERIC_H_
#define NUMERIC_H_

#include <limits>
#include <cmath>

namespace Numeric {

static const double required_precision = 1.e-4;

static double double_epsilon = std::numeric_limits<double>::epsilon();
static double double_min = std::numeric_limits<double>::min();

static const double probthreshold = 0.0000000001; //!< threshold on probability value during calculation of weighted form factor

//! compare two doubles
inline bool areAlmostEqual(double a, double b, double tolerance_factor=1.0) { return std::abs(a-b) < tolerance_factor*Numeric::double_epsilon; }
}

#endif /* NUMERIC_H_ */
