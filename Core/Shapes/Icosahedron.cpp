// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Icosahedron.cpp
//! @brief     Implements class Icosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Icosahedron.h"


Icosahedron::Icosahedron(double edge)
{
    m_vertices = {
        {  0.5773502691896258*edge,                   0*edge, 0.0},
        {  -0.288675134594813*edge,                 0.5*edge, 0.0},
        {  -0.288675134594813*edge,                -0.5*edge, 0.0},
        { -0.9341723589627158*edge,                   0*edge, -0.5773502691896259*edge},
        {   0.467086179481358*edge,  0.8090169943749475*edge, -0.5773502691896259*edge},
        {   0.467086179481358*edge, -0.8090169943749475*edge, -0.5773502691896259*edge},
        {  0.9341723589627158*edge,                   0*edge,  0.9341723589627157*edge},
        {  -0.467086179481358*edge,  0.8090169943749475*edge,  0.9341723589627157*edge},
        {  -0.467086179481358*edge, -0.8090169943749475*edge,  0.9341723589627157*edge},
        { -0.5773502691896258*edge,                   0*edge,  1.5115226281523416*edge},
        {   0.288675134594813*edge,                 0.5*edge,  1.5115226281523416*edge},
        {   0.288675134594813*edge,                -0.5*edge,  1.5115226281523416*edge} };
}

Icosahedron::~Icosahedron()
{}
