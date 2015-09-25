// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/inc/Polygon.h
//! @brief     Defines class Polygon.
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

#include "IShape2D.h"
#include <vector>

namespace Geometry {

class PolygonPrivate;

//! @class Polygon
//! @ingroup tools
//! @brief The polygon in 2D space

class Polygon : public IShape2D {
public:

    Polygon(const std::vector<double > &x, const std::vector<double> &y);


    ~Polygon();

    Polygon *clone() const;

    //! Returns true if given point is inside or on border of polygon
    bool contains(double x, double y) const;

    //! Returns true if area defined by two bins is inside or on border of polygon.
    //! More precisely, if mid point of two bins satisfy this condition.
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

    double getArea() const;

protected:
    virtual void print(std::ostream &ostr) const;

private:
    Polygon(const Polygon& other);
    PolygonPrivate *m_d;
};

} // namespace Geometry

#endif
