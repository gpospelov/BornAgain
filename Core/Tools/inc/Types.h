// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Types.h
//! @brief     Defines some complex and vector types.
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

#include <cstddef>
#include <vector>
#include "BasicVector3D.h"
using std::size_t;

typedef std::complex<double > complex_t;

typedef Geometry::BasicVector3D<double> kvector_t;
typedef Geometry::BasicVector3D<complex_t> cvector_t;

typedef std::vector<double> vdouble1d_t;
typedef std::vector<vdouble1d_t> vdouble2d_t;
typedef std::pair<complex_t, complex_t> complexpair_t;

#endif // TYPES_H


