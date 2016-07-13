// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Geometry/Rectangle.h
//! @brief     Declares class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "IShape2D.h"

namespace Geometry {

//! @class Rectangle
//! @ingroup tools
//! @brief The rectangle shape having its axis aligned to the (non-rotated) coordinate system.

class BA_CORE_API_  Rectangle : public IShape2D {
public:
    //! Rectangle constructor with lower left and upper right coordinates
    //! @param xlow x-coordinate of lower left corner
    //! @param ylow y-coordinate of lower left corner
    //! @param xup x-coordinate of upper right corner
    //! @param yup y-coordinate of upper right corner
    Rectangle(double xlow, double ylow, double xup, double yup);

    Rectangle* clone() const;

    //! Returns true if given point is inside or on border of rectangle
    bool contains(double x, double y) const;

    //! Returns true if mid point of two bins is inside rectangle.
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getArea() const;

    double getXlow() const;
    double getYlow() const;
    double getXup() const;
    double getYup() const;

private:
    Rectangle(const Rectangle& other);
    double m_xlow, m_ylow, m_xup, m_yup;
};

} // namespace Geometry

#endif // RECTANGLE_H
