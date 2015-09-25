// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/inc/IShape2D.h
//! @brief     Defines basic class for all 2D shapes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISHAPE2D_H
#define ISHAPE2D_H

#include "ICloneable.h"
#include <iostream>

namespace Geometry {

//! @class IShape2D
//! @ingroup tools
//! @brief Basic class for all shapes in 2D

class BA_CORE_API_ IShape2D : public ICloneable {
public:

    //! Returns true if given point is inside or on border of the shape
    virtual bool isInside(double x, double y) const = 0;


    friend std::ostream &operator<<(std::ostream &ostr, const IShape2D &shape)
    {
        shape.print(ostr);
        return ostr;
    }

protected:

    virtual void print(std::ostream &ostr) const
    {
        ostr << "IShape2D";
    }

};

} // namespace Geometry

#endif
