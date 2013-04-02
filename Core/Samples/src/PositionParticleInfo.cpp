// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/PositionParticleInfo.cpp
//! @brief     Implements class PositionParticleInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PositionParticleInfo.h"
#include <iostream>

PositionParticleInfo::PositionParticleInfo(
    Particle* p_particle, const Geometry::PTransform3D& transform,
    kvector_t position, double abundance)
    : ParticleInfo(p_particle, transform, position.z(), abundance)
    , m_pos_x(position.x())
    , m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(
    const Particle& particle, const Geometry::PTransform3D& transform,
    kvector_t position, double abundance)
    : ParticleInfo(particle.clone(), transform, position.z(), abundance)
    , m_pos_x(position.x())
    , m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(
    Particle* p_particle, kvector_t position, double abundance)
    : ParticleInfo(p_particle, position.z(), abundance)
    , m_pos_x(position.x())
    , m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(
    const Particle& particle, kvector_t position, double abundance)
    : ParticleInfo(particle.clone(), position.z(), abundance)
    , m_pos_x(position.x())
    , m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo* PositionParticleInfo::clone() const
{
    kvector_t position(m_pos_x, m_pos_y, -m_depth);
    return new PositionParticleInfo(
        mp_particle->clone(), mP_transform, position, m_abundance);
}

void PositionParticleInfo::setPosition(kvector_t position)
{
    m_pos_x = position.x();
    m_pos_y = position.y();
    m_depth = position.z();
}

void PositionParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("x_position", &m_pos_x);
    getParameterPool()->registerParameter("y_position", &m_pos_y);
    getParameterPool()->registerParameter("z_position", &m_depth);
}


