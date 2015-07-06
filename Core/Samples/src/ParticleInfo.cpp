// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleInfo.cpp
//! @brief     Implements class ParticleInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleInfo.h"


ParticleInfo::ParticleInfo(const IAbstractParticle& p_particle, double abundance)
    : mP_particle(p_particle.clone())
    , m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mP_particle.get());
    init_parameters();
}

ParticleInfo *ParticleInfo::clone() const
{
    return new ParticleInfo(*mP_particle, m_abundance);
}

ParticleInfo *ParticleInfo::cloneInvertB() const
{
    boost::scoped_ptr<IAbstractParticle> P_inverted_particle(
                mP_particle->cloneInvertB());
    return new ParticleInfo(*P_inverted_particle, m_abundance);
}

void ParticleInfo::init_parameters()
{
    clearParameterPool();
    registerParameter("abundance", &m_abundance);
}

void ParticleInfo::print(std::ostream& ostr) const
{
    ostr << "ParticleInfo:" << getName() << "<" << this << "> : {" <<
        "abundance=" << m_abundance;
    ostr << " }";
}


