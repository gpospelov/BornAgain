// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleLayout.cpp
//! @brief     Implements class ParticleLayout.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "SizeSpacingCorrelationApproximationStrategy.h"
#include "MessageService.h"
#include "ParticleDistribution.h"

#include <iomanip>


ParticleLayout::ParticleLayout()
{
    setName("ParticleLayout");
}

ParticleLayout::ParticleLayout(
        const IParticle& particle, double depth, double abundance)
{
    setName("ParticleLayout");
    addParticle(particle, depth, abundance);
}

ParticleLayout::~ParticleLayout()
{
}

ParticleLayout* ParticleLayout::clone() const
{
    ParticleLayout *p_new = new ParticleLayout();
    p_new->setName(getName());

    for (size_t i=0; i<m_particles.size(); ++i)
        p_new->addAndRegisterParticleInfo(m_particles[i]->clone());

    for (size_t i=0; i<m_interference_functions.size(); ++i)
        p_new->addAndRegisterInterferenceFunction(
            m_interference_functions[i]->clone());

    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());
    p_new->setApproximation(getApproximation());

    return p_new;
}

ParticleLayout* ParticleLayout::cloneInvertB() const
{
    ParticleLayout *p_new = new ParticleLayout();
    p_new->setName(getName() + "_inv");

    for (size_t i=0; i<m_particles.size(); ++i)
        p_new->addAndRegisterParticleInfo(m_particles[i]->cloneInvertB());

    for (size_t i=0; i<m_interference_functions.size(); ++i)
        p_new->addAndRegisterInterferenceFunction(
            m_interference_functions[i]->clone());

    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());
    p_new->setApproximation(getApproximation());

    return p_new;
}

//! Adds generic particle, &-version.
void ParticleLayout::addParticle(
    const IParticle& p_particle, const Geometry::Transform3D& transform,
    double depth, double abundance)
{
    if(!abundance) {
        throw LogicErrorException("ParticleLayout::addParticle() ->"
                " Error! Abundance can't be equal to 0.0");
    }
    boost::scoped_ptr<IParticle> P_particle_clone(p_particle.clone());
    P_particle_clone->setTransformation(transform);
    addAndRegisterParticleInfo(
        new ParticleInfo(*P_particle_clone, depth, abundance));
}

//! Adds particle without rotation, &-version.
void ParticleLayout::addParticle(
    const IParticle& particle,
    double depth, double abundance)
{
    addAndRegisterParticleInfo(
        new ParticleInfo(particle, depth, abundance));
}

//! Adds particle info.
void ParticleLayout::addParticleInfo(const ParticleInfo& info)
{
    addAndRegisterParticleInfo( info.clone() );
}

//! Returns particle info
const ParticleInfo* ParticleLayout::getParticleInfo(size_t index) const
{
    if (index<m_particles.size())
        return m_particles[index];
    throw OutOfBoundsException(
        "ParticleLayout::getParticleInfo() -> "
        "Error! Not so many particles in this decoration.");
}

double ParticleLayout::getAbundanceOfParticle(size_t index) const
{
    return getParticleInfo(index)->getAbundance();
}

//! Adds interference functions
void ParticleLayout::addInterferenceFunction(
    IInterferenceFunction* p_interference_function)
{
    addAndRegisterInterferenceFunction(p_interference_function);
}

void ParticleLayout::addInterferenceFunction(
    const IInterferenceFunction& interference_function)
{
    addAndRegisterInterferenceFunction(interference_function.clone());
}

const IInterferenceFunction* ParticleLayout::getInterferenceFunction(
    size_t index) const
{
    if (index<m_interference_functions.size())
        return m_interference_functions[index];
    throw OutOfBoundsException(
        "ParticleLayout::getInterferenceFunction() ->"
                "Not so many interference functions in this decoration.");
}

bool ParticleLayout::preprocess()
{
    for (size_t i=0; i<m_particles.size(); ++i) {
        if (dynamic_cast<const ParticleDistribution *>(
                    m_particles[i]->getParticle())) {
            replaceParticleDistribution(i);
            return true;
        }
    }
    return false;
}

//! Adds particle information with simultaneous registration in parent class.
void ParticleLayout::addAndRegisterParticleInfo(
    ParticleInfo *child)
{
    m_particles.push_back(child);
    registerChild(child);
}

//! Adds interference function with simultaneous registration in parent class.
void ParticleLayout::addAndRegisterInterferenceFunction(
    IInterferenceFunction *child)
{
    m_interference_functions.push_back(child);
    registerChild(child);
}

void ParticleLayout::replaceParticleDistribution(size_t index)
{
    ParticleInfo *p_particle_info = m_particles[index];
    const ParticleDistribution *p_particle_coll =
                    dynamic_cast<const ParticleDistribution *>(
                        p_particle_info->getParticle());
    std::vector<ParticleInfo *> particles =
        p_particle_coll->generateParticleInfos(
            p_particle_info->getPosition(), p_particle_info->getAbundance());
    for (size_t i=0; i<particles.size(); ++i) {
        addAndRegisterParticleInfo(particles[i]);
    }
    deregisterChild(p_particle_info);
    m_particles.deleteElement(p_particle_info);
}

void ParticleLayout::print(std::ostream& ostr) const
{
    ILayout::print(ostr);
    ostr << "-->ParticleLayout<" << this << ">{\n";
    for( size_t i=0; i<m_particles.size(); ++i )
        ostr << "      - particle " << std::left << std::setw(2) << i << " { "
             << *(m_particles[i]) << "}\n";
    ostr << "}";
}

