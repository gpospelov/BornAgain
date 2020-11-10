// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/Bessel.h
//! @brief     Defines Bessel functions in namespace MathFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_UTILS_BESSEL_H
#define BORNAGAIN_BASE_UTILS_BESSEL_H

#include "Base/Types/Complex.h"
#include <vector>

namespace MathFunctions
{

//! Bessel function of the first kind and order 0
double Bessel_J0(double x);

//! Bessel function of the first kind and order 1
double Bessel_J1(double x);

//! Bessel function  Bessel_J1(x)/x
double Bessel_J1c(double x);

//! Modified Bessel function of the first kind and order 0
double Bessel_I0(double x);

//! Complex Bessel function of the first kind and order 0
complex_t Bessel_J0(const complex_t z);

//! Complex Bessel function of the first kind and order 1
complex_t Bessel_J1(const complex_t z);

//! Complex Bessel function  Bessel_J1(x)/x
complex_t Bessel_J1c(const complex_t z);

} // Namespace MathFunctions

#endif // BORNAGAIN_BASE_UTILS_BESSEL_H
