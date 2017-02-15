// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/IShape.cpp
//! @brief     Implements default methods of interface IShape.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IShape.h"

#include <cmath>


std::vector<kvector_t> IShape::vertices() const
{
    return m_vertices;
}

std::vector<kvector_t> RectangleVertices(double length, double width, double z)
{
    std::vector<kvector_t> result(4);
    result[0] = kvector_t(length/2.0, width/2.0, z);
    result[1] = kvector_t(-length/2.0, width/2.0, z);
    result[2] = kvector_t(-length/2.0, -width/2.0, z);
    result[3] = kvector_t(length/2.0, -width/2.0, z);
    return result;
}

std::vector<kvector_t> TriangleVertices(double length, double z)
{
    static const double sqrt3 = std::sqrt(3.0);
    double L = length/sqrt3;
    std::vector<kvector_t> result(3);
    result[0] = kvector_t(L, 0.0, z);
    result[1] = kvector_t(-L/2.0, length/2.0, z);
    result[2] = kvector_t(-L/2.0, -length/2.0, z);
    return result;
}

std::vector<kvector_t> HexagonVertices(double length, double z)
{
    static const double sqrt3 = std::sqrt(3.0);
    std::vector<kvector_t> result(6);
    result[0] = kvector_t(length, 0.0, z);
    result[1] = kvector_t(length/2.0, length*sqrt3/2.0, z);
    result[2] = kvector_t(-length/2.0, length*sqrt3/2.0, z);
    result[3] = kvector_t(-length, 0.0, z);
    result[4] = kvector_t(-length/2.0, -length*sqrt3/2.0, z);
    result[5] = kvector_t(length/2.0, -length*sqrt3/2.0, z);
    return result;
}

std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)
{
    // Value of 24 ensures that real points stick out of the convex hull at most
    // 1% of the radius for the case r_x==r_y
    static constexpr size_t n_points = 24;
    static constexpr double delta_angle = M_2_PI/n_points;
    std::vector<kvector_t> result(n_points);
    for (size_t i=0; i<n_points; ++i)
    {
        double angle = i*delta_angle;
        double x = r_x*std::cos(angle);
        double y = r_y*std::sin(angle);
        result[i] = kvector_t(x, y, z);
    }
    return result;
}
