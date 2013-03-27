// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleInfo.cpp
//! @brief     Implements class ParticleInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ParticleInfo.h"

ParticleInfo::ParticleInfo(Particle* p_particle, Geometry::Transform3D *transform, double depth, double abundance)
    : mp_particle(p_particle)
    , mp_transform(transform)
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

ParticleInfo::ParticleInfo(const Particle& p_particle, const Geometry::Transform3D& transform, double depth, double abundance)
    : mp_particle(p_particle.clone())
    , mp_transform(new Geometry::Transform3D(transform))
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

ParticleInfo::~ParticleInfo()
{
    delete mp_particle;
    delete mp_transform;
}

//! Registers some class members for later access via parameter pool
void ParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("depth",& m_depth);
}

ParticleInfo *ParticleInfo::clone() const
{
    Geometry::Transform3D *transform(0);
    if(mp_transform) transform = new Geometry::Transform3D(*mp_transform);
    return new ParticleInfo(mp_particle->clone(), transform, m_depth, m_abundance);
}
