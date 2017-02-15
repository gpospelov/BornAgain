// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/BiPyramid.cpp
//! @brief     Implements class BiPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BiPyramid.h"
#include "MathFunctions.h"

#include <algorithm>

BiPyramid::BiPyramid(double length, double height, double height_ratio, double alpha)
{
    m_vertices.resize(12);
    double cot_alpha = MathFunctions::cot(alpha);
    double delta_1 = 2.0*height*cot_alpha;
    double delta_2 = 2.0*height_ratio*height*cot_alpha;
    auto bottom_face = RectangleVertices(length, length, 0.0);
    auto mid_face = RectangleVertices(length+delta_1, length+delta_1, height);
    auto top_face = RectangleVertices(length+delta_1-delta_2, length+delta_1-delta_2,
                                      (height_ratio + 1.0)*height);
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(mid_face.begin(), mid_face.end(), m_vertices.begin()+4);
    std::move(top_face.begin(), top_face.end(), m_vertices.begin()+8);
}

BiPyramid::~BiPyramid()
{}
