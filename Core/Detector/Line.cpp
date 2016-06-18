// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/Line.cpp
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
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
GCC_DIAG_ON(unused-parameter)

using namespace boost::geometry;
typedef model::d2::point_xy<double> point_t;
typedef model::box<point_t> box_t;
typedef model::linestring<point_t> line_t;


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

    return (d<Numeric::double_epsilon ? true : false);
}

// Calculates if line crosses the box made out of our bins.
// Ugly implementation, see discussion at http://stackoverflow.com/questions/21408977
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

    return intersects(line_t(box_points.begin(),box_points.end()),
                      line_t(line_points.begin(),line_points.end()));
}

Line::Line(const Line &other)
    : m_x1(other.m_x1), m_y1(other.m_y1), m_x2(other.m_x2), m_y2(other.m_y2)
{
}

// ------------------------------------------------------------------------- //

VerticalLine::VerticalLine(double x)
    : m_x(x)
{
}

VerticalLine *VerticalLine::clone() const
{
    return new VerticalLine(*this);
}

bool VerticalLine::contains(double x, double /*y*/) const
{
    return Numeric::areAlmostEqual(x, m_x);
}

bool VerticalLine::contains(const Bin1D& binx, const Bin1D& /*biny*/) const
{
    if(m_x>=binx.m_lower && m_x <= binx.m_upper) return true;
    return false;
}

double VerticalLine::getXpos() const
{
    return m_x;
}

VerticalLine::VerticalLine(const VerticalLine &other)
    : m_x(other.m_x)
{
}

// ------------------------------------------------------------------------- //

HorizontalLine::HorizontalLine(double y)
    : m_y(y)
{
}

HorizontalLine *HorizontalLine::clone() const
{
    return new HorizontalLine(*this);
}

bool HorizontalLine::contains(double /*x*/, double y) const
{
    return Numeric::areAlmostEqual(y, m_y);
}

bool HorizontalLine::contains(const Bin1D& /*binx*/, const Bin1D& biny) const
{
    if(m_y>=biny.m_lower && m_y <= biny.m_upper) return true;
    return false;
}

double HorizontalLine::getYpos() const
{
    return m_y;
}

HorizontalLine::HorizontalLine(const HorizontalLine &other)
    : m_y(other.m_y)
{
}



} // namespace Geometry
