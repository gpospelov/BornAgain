// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/AnisoPyramid.cpp
//! @brief     Implements class AnisoPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AnisoPyramid.h"
#include "MathFunctions.h"

#include <algorithm>

AnisoPyramid::AnisoPyramid(double length, double width, double height, double alpha)
{
    m_vertices.resize(8);
    double cot_alpha = MathFunctions::cot(alpha);
    double delta = 2.0*height*cot_alpha;
    auto bottom_face = RectangleVertices(length, width, 0.0);
    auto top_face = RectangleVertices(length-delta, width-delta, height);
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(top_face.begin(), top_face.end(), m_vertices.begin()+4);
}

AnisoPyramid::~AnisoPyramid()
{}
