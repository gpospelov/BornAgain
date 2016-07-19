// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IShape2D.h
//! @brief     Declares basic class for all 2D shapes.
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

struct Bin1D;

namespace Geometry {

//! @class IShape2D
//! @ingroup tools
//! @brief Basic class for all shapes in 2D

class BA_CORE_API_ IShape2D : public ICloneable {
public:

    virtual IShape2D *clone() const = 0;

    //! Returns true if point with given coordinates is inside or on border of the shape
    virtual bool contains(double x, double y) const = 0;

    //! Returns true if area defined by two bins is inside or on border of the shape
    virtual bool contains(const Bin1D &binx, const Bin1D &biny) const = 0;

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

#endif // ISHAPE2D_H
