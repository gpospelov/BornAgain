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
    IParticle* p_particle, kvector_t position, double abundance)
    : ParticleInfo(p_particle, position.z(), abundance)
    , m_pos_x(position.x())
    , m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(
    const IParticle& particle, kvector_t position, double abundance)
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
        mP_particle->clone(), position, m_abundance);
}

void PositionParticleInfo::setPosition(kvector_t position)
{
    m_pos_x = position.x();
    m_pos_y = position.y();
    m_depth = -position.z();
}

void PositionParticleInfo::init_parameters()
{
    clearParameterPool();
    registerParameter("x_position", &m_pos_x);
    registerParameter("y_position", &m_pos_y);
    registerParameter("abundance", &m_abundance);
}


