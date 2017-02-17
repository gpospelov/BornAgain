// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Pyramid3.cpp
//! @brief     Implements class Pyramid3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Pyramid3.h"
#include "MathFunctions.h"

#include <algorithm>

const double Pyramid3::sqrt3 = std::sqrt(3.0);

Pyramid3::Pyramid3(double length, double height, double alpha)
{
    m_vertices.resize(6);
    double cot_alpha = MathFunctions::cot(alpha);
    double delta = 2.0*sqrt3*height*cot_alpha;
    auto bottom_face = TriangleVertices(length, 0.0);
    auto top_face = TriangleVertices(length-delta, height);
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(top_face.begin(), top_face.end(), m_vertices.begin()+3);
}

Pyramid3::~Pyramid3()
{}
