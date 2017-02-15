// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Dodecahedron.cpp
//! @brief     Implements class Dodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Dodecahedron.h"


Dodecahedron::Dodecahedron(double edge)
{
    m_vertices = {
        {  0.8506508083520399*edge,                   0*edge,  0.0},
        {  0.2628655560595668*edge,  0.8090169943749473*edge,  0.0},
        { -0.6881909602355868*edge,                 0.5*edge,  0.0},
        { -0.6881909602355868*edge,                -0.5*edge,  0.0},
        {  0.2628655560595668*edge, -0.8090169943749473*edge,  0.0},
        {   1.376381920471174*edge,                   0*edge, 0.8506508083520403*edge},
        {    0.42532540417602*edge,   1.309016994374947*edge, 0.8506508083520403*edge},
        {  -1.113516364411607*edge,  0.8090169943749475*edge, 0.8506508083520403*edge},
        {  -1.113516364411607*edge, -0.8090169943749475*edge, 0.8506508083520403*edge},
        {    0.42532540417602*edge,  -1.309016994374947*edge, 0.8506508083520403*edge},
        {  -1.376381920471174*edge,                   0*edge,  1.3763819204711737*edge},
        {   -0.42532540417602*edge,  -1.309016994374947*edge,  1.3763819204711737*edge},
        {   1.113516364411607*edge, -0.8090169943749475*edge,  1.3763819204711737*edge},
        {   1.113516364411607*edge,  0.8090169943749475*edge,  1.3763819204711737*edge},
        {   -0.42532540417602*edge,   1.309016994374947*edge,  1.3763819204711737*edge},
        { -0.8506508083520399*edge,                   0*edge,   2.227032728823214*edge},
        { -0.2628655560595668*edge, -0.8090169943749473*edge,   2.227032728823214*edge},
        {  0.6881909602355868*edge,                -0.5*edge,   2.227032728823214*edge},
        {  0.6881909602355868*edge,                 0.5*edge,   2.227032728823214*edge},
        { -0.2628655560595668*edge,  0.8090169943749473*edge,   2.227032728823214*edge} };
}

Dodecahedron::~Dodecahedron()
{}
