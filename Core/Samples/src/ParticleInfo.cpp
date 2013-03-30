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

ParticleInfo::ParticleInfo(
    Particle* p_particle, const Geometry::PTransform3D& transform,
    double depth, double abundance)
    : mp_particle(p_particle)
    , mP_transform(transform)
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

ParticleInfo::ParticleInfo(
    const Particle& p_particle,
    const Geometry::PTransform3D& transform,
    double depth,
    double abundance)
    : mp_particle(p_particle.clone())
    , mP_transform(transform)
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

ParticleInfo::ParticleInfo(
    Particle *p_particle,
    double depth,
    double abundance)
    : mp_particle(p_particle)
    , mP_transform(Geometry::PTransform3D())
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

ParticleInfo::ParticleInfo(
    const Particle& p_particle,
    double depth,
    double abundance)
    : mp_particle(p_particle.clone())
    , mP_transform(Geometry::PTransform3D())
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}

void ParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("depth", &m_depth);
}


void ParticleInfo::print(std::ostream& ostr) const
{
    ostr << "ParticleInfo:" << getName() << "<" << this << "> : {" <<
        " depth=" << m_depth <<
        ", abundance=" << m_abundance <<
        ", transform=";
    if ( mP_transform )
        ostr << *mP_transform;
    else
        ostr << "NONE";
    ostr << " }";
}
