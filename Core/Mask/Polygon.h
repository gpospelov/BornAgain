// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Polygon.h
//! @brief     Declares class Polygon.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POLYGON_H
#define POLYGON_H

#include "IShape2D.h" // inheriting from
#include <vector>

namespace Geometry {

class PolygonPrivate;

//! @class Polygon
//! @ingroup tools
//! @brief The polygon in 2D space

class BA_CORE_API_ Polygon : public IShape2D {
public:
    //! Polygon defined by two arrays with x and y coordinates of points.
    //! Sizes of arrays should coincide.  If polygon is unclosed (the last point
    //! doesn't repeat the first one), it will be closed automatically.
    //! @param x Vector of x-coordinates of polygon points.
    //! @param y Vector of y-coordinates of polygon points.
    Polygon(std::vector<double > x, std::vector<double> y);

    //! Polygon defined by two  dimensional array with (x,y) coordinates of polygon points.
    //! The size of second dimension should be 2. If polygon is unclosed (the last point
    //! doesn't repeat the first one), it will be closed automatically.
    //! @param points Two dimensional vector of (x,y) coordinates of polygon points.
    Polygon(std::vector<std::vector<double> > points);

    virtual ~Polygon();

    virtual Polygon* clone() const;

    //! Returns true if given point is inside or on border of polygon
    virtual bool contains(double x, double y) const;

    //! Returns true if area defined by two bins is inside or on border of polygon.
    //! More precisely, if mid point of two bins satisfy this condition.
    virtual bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getArea() const;

    void getPoints(std::vector<double> &xpos, std::vector<double> &ypos) const;

protected:
    virtual void print(std::ostream &ostr) const;

private:
    Polygon(const Polygon& other);
    const Polygon& operator=(const Polygon& );

    PolygonPrivate* m_d;
};

} // namespace Geometry

#endif // POLYGON_H
