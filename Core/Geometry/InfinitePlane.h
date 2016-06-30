// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Geometry/InfinitePlane.h
//! @brief     Declares class InfinitePlane.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "IShape2D.h"

namespace Geometry {


//! @class InfinitePlane
//! @ingroup tools
//! @brief The infinite plane is used in masking to mask everythin once and forever.

class BA_CORE_API_  InfinitePlane : public IShape2D {
public:
    InfinitePlane(){}

    InfinitePlane *clone() const;

    //! Returns true if given point is inside or on border of rectangle
    bool contains(double x, double y) const;

    //! Returns true if mid point of two bins is inside rectangle.
    bool contains(const Bin1D &binx, const Bin1D &biny) const;
};

} // namespace Geometry

#endif
