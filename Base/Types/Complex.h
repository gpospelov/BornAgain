//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Base/Types/Complex.h
//! @brief     Defines complex_t, and a few elementary functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_TYPES_COMPLEX_H
#define BORNAGAIN_BASE_TYPES_COMPLEX_H

#include <complex>

using complex_t = std::complex<double>;
constexpr complex_t I = complex_t(0.0, 1.0);

//! Returns product I*z, where I is the imaginary unit.
inline complex_t mul_I(complex_t z)
{
    return complex_t(-z.imag(), z.real());
}

//! Returns exp(I*z), where I is the imaginary unit.
inline complex_t exp_I(complex_t z)
{
    return std::exp(complex_t(-z.imag(), z.real()));
}

#endif // BORNAGAIN_BASE_TYPES_COMPLEX_H
