// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Icosahedron.cpp
//! @brief     Implements class Icosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Icosahedron.h"

Icosahedron::Icosahedron(double edge)
{
    // key parameters used for the calculation of vertices:
    // 1. dihedral angle = arccos(-sqrt(5)/3)
    // 2. radius of inscribed sphere = sqrt(3)/12*(3+sqrt(5))*edge

    m_vertices = {
        { -0.57735026918962573*edge,                  0.0*edge, 0.0},
        {  0.28867513459481281*edge,                  0.5*edge, 0.0},
        {  0.28867513459481281*edge,                 -0.5*edge, 0.0},
        {  0.93417235896271578*edge,                  0.0*edge, 0.57735026918962562*edge},
        { -0.46708617948135783*edge,  0.80901699437494756*edge, 0.57735026918962562*edge},
        { -0.46708617948135783*edge, -0.80901699437494756*edge, 0.57735026918962562*edge},
        { -0.93417235896271578*edge,                  0.0*edge, 0.93417235896271589*edge},
        {  0.46708617948135783*edge,  0.80901699437494756*edge, 0.93417235896271589*edge},
        {  0.46708617948135783*edge, -0.80901699437494756*edge, 0.93417235896271589*edge},
        {  0.57735026918962573*edge,                  0.0*edge, 1.5115226281523415*edge},
        { -0.28867513459481281*edge,                  0.5*edge, 1.5115226281523415*edge},
        { -0.28867513459481281*edge,                 -0.5*edge, 1.5115226281523415*edge} };
}

Icosahedron::~Icosahedron()
{}
