// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Geometry/src/Line.cpp
//! @brief     Implements class Line.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Line.h"
#include "Bin.h"
#include "Numeric.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>

using namespace boost::geometry;

namespace {
typedef model::d2::point_xy<double> point_t;
typedef model::box<point_t> box_t;
typedef model::linestring<point_t> line_t;
}


namespace Geometry {

Line::Line(double x1, double y1, double x2, double y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2)
{
}

Line *Line::clone() const
{
    return new Line(*this);
}

bool Line::contains(double x, double y) const
{
    point_t p(x, y);
    line_t line;
    line.push_back(point_t(m_x1, m_y1));
    line.push_back(point_t(m_x2, m_y2));

    double d = distance(p, line);

    std::cout << "Line: " << d << std::endl;

    return (d<Numeric::double_epsilon ? true : false);
}

// Calculates if line crosses the box made out of our bins.
// Ugly implementation, see discussion at
// http://stackoverflow.com/questions/21408977/boostgeometryintersects-doesnt-work-for-different-geometry-types
bool Line::contains(const Bin1D &binx, const Bin1D &biny) const
{
    std::vector<point_t> box_points;
    box_points.push_back(point_t(binx.m_lower, biny.m_lower));
    box_points.push_back(point_t(binx.m_lower, biny.m_upper));
    box_points.push_back(point_t(binx.m_upper, biny.m_upper));
    box_points.push_back(point_t(binx.m_upper, biny.m_lower));
    box_points.push_back(point_t(binx.m_lower, biny.m_lower));

    std::vector<point_t> line_points;
    line_points.push_back(point_t(m_x1, m_y1));
    line_points.push_back(point_t(m_x2, m_y2));

    return intersects(line_t(box_points.begin(),box_points.end()), line_t(line_points.begin(),line_points.end()));
}

Line::Line(const Line &other)
    : m_x1(other.m_x1), m_y1(other.m_y1), m_x2(other.m_x2), m_y2(other.m_y2)
{
}

} // namespace Geometry

