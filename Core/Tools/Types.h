// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/Types.h
//! @brief     Declares size_t, complex_t, and the array types vdouble1d_t, vdouble2d_t.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TYPES_H
#define TYPES_H

#include <complex>
#include <vector>

using std::size_t;

typedef std::complex<double> complex_t;

typedef std::vector<double> vdouble1d_t;
typedef std::vector<vdouble1d_t> vdouble2d_t;

#endif // TYPES_H
