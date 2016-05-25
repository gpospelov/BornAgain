// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/Complex.h
//! @brief     Declares complex_t, and a few elementary functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BA_COMPLEX_H
#define BA_COMPLEX_H

#include <complex>

typedef std::complex<double> complex_t;

inline complex_t I_mul( complex_t z ) { return complex_t( -z.imag(), z.real() ); }

#endif // BA_COMPLEX_H
