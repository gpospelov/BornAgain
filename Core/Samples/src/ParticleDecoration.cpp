// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleDecoration.cpp
//! @brief     Implements class ParticleDecoration.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "LocalMonodisperseApproximationStrategy.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "SizeSpacingCorrelationApproximationStrategy.h"


ParticleDecoration::ParticleDecoration()
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
}

ParticleDecoration::ParticleDecoration(Particle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
    addParticle(p_particle, 0, depth, abundance);
}

ParticleDecoration::ParticleDecoration(const Particle &p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
    addParticle(p_particle.clone(), 0, depth, abundance);
}

ParticleDecoration::~ParticleDecoration()
{
    for (size_t i=0; i<m_particles.size(); ++i) {
        delete m_particles[i];
    }
}

ParticleDecoration* ParticleDecoration::clone() const
{
    ParticleDecoration *p_new = new ParticleDecoration();
    p_new->setName(getName());

    for (size_t i=0; i<m_particles.size(); ++i) {
        p_new->addAndRegisterParticleInfo(m_particles[i]->clone());
    }

    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        p_new->addAndRegisterInterferenceFunction(m_interference_functions[i]->clone());
    }

    p_new->m_total_abundance = m_total_abundance;
    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());

    return p_new;
}

//! add particle

void ParticleDecoration::addParticle(Particle* p_particle,
        double depth, double abundance)
{
    addParticle(p_particle, 0, depth, abundance);
}

void ParticleDecoration::addParticle(const Particle &p_particle,
        double depth, double abundance)
{
    addParticle(p_particle.clone(), 0, depth, abundance);
}

void ParticleDecoration::addParticle(const Particle &p_particle,
        const Geometry::Transform3D &transform, double depth, double abundance)
{
    addParticle(p_particle.clone(), new Geometry::Transform3D(transform), depth, abundance);
}

// main function to add particle
void ParticleDecoration::addParticle(Particle* p_particle,
        Geometry::Transform3D *transform, double depth, double abundance)
{
    addAndRegisterParticleInfo( new ParticleInfo(p_particle, transform, depth, abundance) );
}

//! add particle info

void ParticleDecoration::addParticleInfo(const ParticleInfo &info)
{
    addAndRegisterParticleInfo( info.clone() );
}

//! get particle info

const ParticleInfo* ParticleDecoration::getParticleInfo(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index];
    }
    throw OutOfBoundsException("ParticleDecoration::getParticleInfo() -> Error! Not so many interference functions in this decoration.");
}

double ParticleDecoration::getAbundanceFractionOfParticle(size_t index) const
{
    return getParticleInfo(index)->getAbundance()/m_total_abundance;
}

//! add interference functions

void ParticleDecoration::addInterferenceFunction(IInterferenceFunction* p_interference_function)
{
    addAndRegisterInterferenceFunction(p_interference_function);
}

void ParticleDecoration::addInterferenceFunction(const IInterferenceFunction &interference_function)
{
    addAndRegisterInterferenceFunction(interference_function.clone());
}

const IInterferenceFunction* ParticleDecoration::getInterferenceFunction(size_t index) const
{
    if (index<m_interference_functions.size()) {
        return m_interference_functions[index];
    }
    throw OutOfBoundsException("ParticleDecoration::getInterferenceFunction() -> Not so many interference functions in this decoration.");
}
