#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "LocalMonodisperseApproximationStrategy.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
: m_total_abundance(0.0)
, m_total_particle_surface_density(1.0)
{
    setName("NanoParticleDecoration");
}

NanoParticleDecoration::NanoParticleDecoration(Particle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
, m_total_particle_surface_density(1.0)
{
    setName("NanoParticleDecoration");
    addNanoParticle(p_particle, 0, depth, abundance);
}

NanoParticleDecoration::~NanoParticleDecoration()
{
    for (size_t i=0; i<m_particles.size(); ++i) {
        delete m_particles[i];
    }

    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        delete m_interference_functions[i];
    }
}


NanoParticleDecoration* NanoParticleDecoration::clone() const
{
    NanoParticleDecoration *p_new = new NanoParticleDecoration();
    p_new->setName(getName());

    for (size_t i=0; i<m_particles.size(); ++i) {
        p_new->addAndRegisterNanoParticleInfo(m_particles[i]->clone());
    }

    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        p_new->addAndRegisterInterferenceFunction(m_interference_functions[i]->clone());
    }

    p_new->m_total_abundance = m_total_abundance;
    p_new->setTotalParticleSurfaceDensity(m_total_particle_surface_density);

    return p_new;
}


/* ************************************************************************* */
// add nano particle
/* ************************************************************************* */
void NanoParticleDecoration::addNanoParticle(Particle* p_particle,
        double depth, double abundance)
{
    addNanoParticle(p_particle, 0, depth, abundance);
}

void NanoParticleDecoration::addNanoParticle(const Particle &p_particle,
        double depth, double abundance)
{
    addNanoParticle(p_particle.clone(), 0, depth, abundance);
}

void NanoParticleDecoration::addNanoParticle(const Particle &p_particle,
        const Geometry::Transform3D &transform, double depth, double abundance)
{
    addNanoParticle(p_particle.clone(), new Geometry::Transform3D(transform), depth, abundance);
}

// main function to add nano particle
void NanoParticleDecoration::addNanoParticle(Particle* p_particle,
        Geometry::Transform3D *transform, double depth, double abundance)
{
    addAndRegisterNanoParticleInfo( new NanoParticleInfo(p_particle, transform, depth, abundance) );
}

/* ************************************************************************* */
// add nano particle info
/* ************************************************************************* */
void NanoParticleDecoration::addNanoParticleInfo(const NanoParticleInfo &info)
{
    addAndRegisterNanoParticleInfo( info.clone() );
}

/* ************************************************************************* */
// get nano particle info
/* ************************************************************************* */
const NanoParticleInfo* NanoParticleDecoration::getNanoParticleInfo(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index];
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}

double NanoParticleDecoration::getAbundanceFractionOfNanoParticle(size_t index) const
{
    return getNanoParticleInfo(index)->getAbundance()/m_total_abundance;
}


/* ************************************************************************* */
// add interference functions
/* ************************************************************************* */
void NanoParticleDecoration::addInterferenceFunction(IInterferenceFunction* p_interference_function)
{
    addAndRegisterInterferenceFunction(p_interference_function);
}

void NanoParticleDecoration::addInterferenceFunction(const IInterferenceFunction &interference_function)
{
    addAndRegisterInterferenceFunction(interference_function.clone());
}

const IInterferenceFunction* NanoParticleDecoration::getInterferenceFunction(size_t index) const
{
    if (index<m_interference_functions.size()) {
        return m_interference_functions[index];
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}


/* ************************************************************************* */
// create strategy
/* ************************************************************************* */
IInterferenceFunctionStrategy* NanoParticleDecoration::createStrategy(
        const std::vector<IFormFactor*>& form_factors) const
{
    std::vector<double> fractions;
    for (size_t i=0; i<m_particles.size(); ++i) {
        fractions.push_back(getAbundanceFractionOfNanoParticle(i));
    }
    IInterferenceFunctionStrategy *p_strategy;
    size_t n_particles = m_particles.size();
    size_t n_ifs = m_interference_functions.size();
    if (n_ifs==1) {
        p_strategy = new DecouplingApproximationStrategy();
    }
    else if (n_ifs==n_particles) {
        p_strategy = new LocalMonodisperseApproximationStrategy();
    }
    else {
        throw ClassInitializationException("Could not create interference function strategy with given parameters.");
    }
    p_strategy->init(form_factors, fractions, m_interference_functions);
    return p_strategy;
}

