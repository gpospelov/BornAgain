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
#include "MessageService.h"
#include <iomanip>


ParticleDecoration::ParticleDecoration()
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
}

ParticleDecoration::ParticleDecoration(
        Particle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
    addParticle(p_particle, depth, abundance);
}

ParticleDecoration::ParticleDecoration(
        const Particle& p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
    setName("ParticleDecoration");
    addParticle(p_particle.clone(), depth, abundance);
}

ParticleDecoration::~ParticleDecoration()
{
}

ParticleDecoration* ParticleDecoration::clone() const
{
    ParticleDecoration *p_new = new ParticleDecoration();
    p_new->setName(getName());

    for (size_t i=0; i<m_particles.size(); ++i)
        p_new->addAndRegisterParticleInfo(m_particles[i]->clone());

    for (size_t i=0; i<m_interference_functions.size(); ++i)
        p_new->addAndRegisterInterferenceFunction(
            m_interference_functions[i]->clone());

    p_new->m_total_abundance = m_total_abundance;
    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());

    return p_new;
}

ParticleDecoration* ParticleDecoration::cloneInvertB() const
{
    ParticleDecoration *p_new = new ParticleDecoration();
    p_new->setName(getName() + "_inv");

    for (size_t i=0; i<m_particles.size(); ++i)
        p_new->addAndRegisterParticleInfo(m_particles[i]->cloneInvertB());

    for (size_t i=0; i<m_interference_functions.size(); ++i)
        p_new->addAndRegisterInterferenceFunction(
            m_interference_functions[i]->clone());

    p_new->m_total_abundance = m_total_abundance;
    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());

    return p_new;
}

//! Adds generic particle, *-version.
void ParticleDecoration::addParticle(
    Particle* p_particle, const Geometry::ITransform3D& transform,
    double depth, double abundance)
{
    if(!abundance) {
        throw LogicErrorException("ParticleDecoration::addParticle() ->"
                " Error! Abundance can't be equal to 0.0");
    }
    p_particle->setTransform(transform);
    addAndRegisterParticleInfo(
        new ParticleInfo(p_particle, depth, abundance));
}

//! Adds generic particle, &-version.
void ParticleDecoration::addParticle(
    const Particle& p_particle, const Geometry::ITransform3D& transform,
    double depth, double abundance)
{
    if(!abundance) {
        throw LogicErrorException("ParticleDecoration::addParticle() ->"
                " Error! Abundance can't be equal to 0.0");
    }
    Particle *p_particle_clone = p_particle.clone();
    p_particle_clone->setTransform(transform);
    addAndRegisterParticleInfo(
        new ParticleInfo(p_particle_clone, depth, abundance));
}

//! Adds particle without rotation, *-version.
void ParticleDecoration::addParticle(
    Particle* p_particle,
    double depth, double abundance)
{
    addAndRegisterParticleInfo(
        new ParticleInfo(p_particle, depth, abundance));
}

//! Adds particle without rotation, &-version.
void ParticleDecoration::addParticle(
    const Particle& p_particle,
    double depth, double abundance)
{
    Particle *p_particle_clone = p_particle.clone();
    addAndRegisterParticleInfo(
        new ParticleInfo(p_particle_clone, depth, abundance));
}

//! Adds particle info.
void ParticleDecoration::addParticleInfo(const ParticleInfo& info)
{
    addAndRegisterParticleInfo( info.clone() );
}

//! Returns particle info
const ParticleInfo* ParticleDecoration::getParticleInfo(size_t index) const
{
    if (index<m_particles.size())
        return m_particles[index];
    throw OutOfBoundsException(
        "ParticleDecoration::getParticleInfo() -> "
        "Error! Not so many particles in this decoration.");
}

double ParticleDecoration::getAbundanceFractionOfParticle(size_t index) const
{
    return getParticleInfo(index)->getAbundance()/m_total_abundance;
}

//! Adds interference functions
void ParticleDecoration::addInterferenceFunction(
    IInterferenceFunction* p_interference_function)
{
    addAndRegisterInterferenceFunction(p_interference_function);
}

void ParticleDecoration::addInterferenceFunction(
    const IInterferenceFunction& interference_function)
{
    addAndRegisterInterferenceFunction(interference_function.clone());
}

const IInterferenceFunction* ParticleDecoration::getInterferenceFunction(
    size_t index) const
{
    if (index<m_interference_functions.size())
        return m_interference_functions[index];
    throw OutOfBoundsException(
        "ParticleDecoration::getInterferenceFunction() ->"
        "Not so many interference functions in this decoration.");
}

//! Adds particle information with simultaneous registration in parent class.
void ParticleDecoration::addAndRegisterParticleInfo(
    ParticleInfo *child)
{
    m_total_abundance += child->getAbundance();
    m_particles.push_back(child);
    registerChild(child);
}

//! Adds interference function with simultaneous registration in parent class.
void ParticleDecoration::addAndRegisterInterferenceFunction(
    IInterferenceFunction *child)
{
    m_interference_functions.push_back(child);
    registerChild(child);
}

void ParticleDecoration::print(std::ostream& ostr) const
{
    IDecoration::print(ostr);
    ostr << "-->ParticleDecoration<" << this << ">{\n";
    for( size_t i=0; i<m_particles.size(); ++i )
        ostr << "      - particle " << std::left << std::setw(2) << i << " { "
             << *(m_particles[i]) << "}\n";
    ostr << "}";
}

