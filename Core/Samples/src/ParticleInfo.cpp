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
    IParticle *p_particle,
    double depth,
    double abundance)
    : mP_particle(p_particle)
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mP_particle.get());
    init_parameters();
}

ParticleInfo::ParticleInfo(
    const IParticle& p_particle,
    double depth,
    double abundance)
    : mP_particle(p_particle.clone())
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mP_particle.get());
    init_parameters();
}

void ParticleInfo::init_parameters()
{
    clearParameterPool();
    registerParameter("depth", &m_depth);
    registerParameter("abundance", &m_abundance);
}


void ParticleInfo::print(std::ostream& ostr) const
{
    ostr << "ParticleInfo:" << getName() << "<" << this << "> : {" <<
        " depth=" << m_depth <<
        ", abundance=" << m_abundance;
    ostr << " }";
}


