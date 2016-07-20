// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vectors/Vectors3D.h
//! @brief     Declares basic vectors in R^3 and C^3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VECTORS3D_H
#define VECTORS3D_H

#include "BasicVector3D.h"

typedef Geometry::BasicVector3D<int> ivector_t;
typedef Geometry::BasicVector3D<double> kvector_t;
typedef Geometry::BasicVector3D<std::complex<double>> cvector_t;

#endif // VECTORS3D_H
