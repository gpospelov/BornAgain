// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Pyramid6.cpp
//! @brief     Implements class Pyramid6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Pyramid6.h"
#include "MathFunctions.h"

#include <algorithm>

const double Pyramid6::sqrt3 = std::sqrt(3.0);

Pyramid6::Pyramid6(double length, double height, double alpha)
{
    m_vertices.resize(12);
    double cot_alpha = MathFunctions::cot(alpha);
    double delta = height*cot_alpha;
    auto bottom_face = HexagonVertices(length, 0.0);
    auto top_face = HexagonVertices(length-delta, height);
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(top_face.begin(), top_face.end(), m_vertices.begin()+6);
}

Pyramid6::~Pyramid6()
{}
