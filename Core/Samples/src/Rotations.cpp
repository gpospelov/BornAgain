// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Rotations.cpp
//! @brief     Implements IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Rotations.h"

RotationX::RotationX(double angle)
    : m_angle(angle)
{
    setName("RotationX");
    init_parameters();
}

RotationX *RotationX::clone() const
{
    return new RotationX(m_angle);
}

RotationX *RotationX::cloneInvertB() const
{
    return clone();
}

Geometry::Transform3D *RotationX::getTransform3D() const
{
    return Geometry::Transform3D::createRotateX(m_angle).clone();
}

void RotationX::init_parameters()
{
    clearParameterPool();
    registerParameter("angle", &m_angle);
}


