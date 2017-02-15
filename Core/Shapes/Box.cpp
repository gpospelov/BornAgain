// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Box.h
//! @brief     Implements class Box.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Box.h"


Box::Box(double length, double width, double height)
{
    m_vertices.resize(8);
    double l2 = length/2.0;
    double w2 = width/2.0;
    m_vertices[0] = kvector_t(l2, w2, 0.0);
    m_vertices[1] = kvector_t(l2, -w2, 0.0);
    m_vertices[2] = kvector_t(-l2, w2, 0.0);
    m_vertices[3] = kvector_t(-l2, -w2, 0.0);
    m_vertices[4] = kvector_t(l2, w2, height);
    m_vertices[5] = kvector_t(l2, -w2, height);
    m_vertices[6] = kvector_t(-l2, w2, height);
    m_vertices[7] = kvector_t(-l2, -w2, height);
}

Box::~Box()
{}
