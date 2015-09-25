// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/src/Polygon.cpp
//! @brief     Implements class Polygon.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Polygon.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;

namespace Geometry {

class PolygonPrivate {
public:
    typedef model::d2::point_xy<double> point_t;
    typedef model::polygon<point_t> polygon_t;
    polygon_t polygon;
    void init_from(const std::vector<double> &x, const std::vector<double> &y);
};


void PolygonPrivate::init_from(const std::vector<double> &x, const std::vector<double> &y)
{
    if(x.size() != y.size()) {
        std::ostringstream message;
        message << "Polygon::Polygon(const std::vector<double> &x, const std::vector<double> &y) "
                << "Error. Sizes of arrays must conincide." << std::endl;
        throw LogicErrorException(message.str());
    }
    std::vector<point_t> points;
    for(size_t i=0; i<x.size(); ++i) {
        points.push_back(point_t(x[i], y[i]));
    }
//    // close polygon if necessary
//    if( (x.front() != x.back()) || (y.front() != y.back()) ) {
//        points.push_back(point_t(x.back(), y.back()));
//    }

    assign_points(polygon, points);
    correct(polygon);
}

//Polygon::Polygon()
//    : m_d(new PolygonPrivate)
//{

//}

Polygon::Polygon(const std::vector<double> &x, const std::vector<double> &y)
    : m_d(new PolygonPrivate)
{
    m_d->init_from(x, y);
}

Polygon::~Polygon()
{
    delete m_d;
}

Polygon *Polygon::clone() const
{
    return new Polygon(*this);
}

bool Polygon::isInside(double x, double y) const
{
//    return within(PolygonPrivate::point_t(x, y), m_d->polygon);
    return covered_by(PolygonPrivate::point_t(x, y), m_d->polygon);
}

double Polygon::getArea() const
{
    return area(m_d->polygon);
}

void Polygon::print(std::ostream &ostr) const
{
    ostr << wkt<PolygonPrivate::polygon_t>(m_d->polygon);
}

//double Polygon::getData() const
//{
//    return m_d->m_x;
//}

//void Polygon::setData(double value) const
//{
//    m_d->m_x = value;
//}

Polygon::Polygon(const Polygon &other)
{
    m_d = new PolygonPrivate(*other.m_d);
}

} // namespace Geometry
