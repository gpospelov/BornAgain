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


ParticleInfo::ParticleInfo(const IParticle& p_particle, double depth,
                           double abundance)
    : mP_particle(p_particle.clone())
    , m_x(0.0)
    , m_y(0.0)
    , m_depth(depth)
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mP_particle.get());
    init_parameters();
}

ParticleInfo::ParticleInfo(const IParticle &p_particle, kvector_t position,
                           double abundance)
    : mP_particle(p_particle.clone())
    , m_x(position.x())
    , m_y(position.y())
    , m_depth(-position.z())
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mP_particle.get());
    init_parameters();
}

ParticleInfo *ParticleInfo::clone() const
{
    return new ParticleInfo(*mP_particle, getPosition(), m_abundance);
}

ParticleInfo *ParticleInfo::cloneInvertB() const
{
    boost::scoped_ptr<IParticle> P_inverted_particle(
                mP_particle->cloneInvertB());
    return new ParticleInfo(*P_inverted_particle, getPosition(), m_abundance);
}

void ParticleInfo::setPosition(kvector_t position)
{
    m_x = position.x();
    m_y = position.y();
    m_depth = -position.z();
}

void ParticleInfo::init_parameters()
{
    clearParameterPool();
    registerParameter("x_position", &m_x);
    registerParameter("y_position", &m_y);
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


