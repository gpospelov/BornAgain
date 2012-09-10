#include "ParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "LocalMonodisperseApproximationStrategy.h"

/* ************************************************************************* */
ParticleDecoration::ParticleDecoration()
: m_total_abundance(0.0)
, m_total_particle_surface_density(1.0)
{
    setName("NanoParticleDecoration");
}

ParticleDecoration::ParticleDecoration(Particle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
, m_total_particle_surface_density(1.0)
{
    setName("NanoParticleDecoration");
    addParticle(p_particle, 0, depth, abundance);
}

ParticleDecoration::~ParticleDecoration()
{
    for (size_t i=0; i<m_particles.size(); ++i) {
        delete m_particles[i];
    }

    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        delete m_interference_functions[i];
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
    p_new->setTotalParticleSurfaceDensity(m_total_particle_surface_density);

    return p_new;
}


/* ************************************************************************* */
// add nano particle
/* ************************************************************************* */
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

// main function to add nano particle
void ParticleDecoration::addParticle(Particle* p_particle,
        Geometry::Transform3D *transform, double depth, double abundance)
{
    addAndRegisterParticleInfo( new ParticleInfo(p_particle, transform, depth, abundance) );
}

/* ************************************************************************* */
// add nano particle info
/* ************************************************************************* */
void ParticleDecoration::addParticleInfo(const ParticleInfo &info)
{
    addAndRegisterParticleInfo( info.clone() );
}

/* ************************************************************************* */
// get nano particle info
/* ************************************************************************* */
const ParticleInfo* ParticleDecoration::getParticleInfo(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index];
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}

double ParticleDecoration::getAbundanceFractionOfParticle(size_t index) const
{
    return getParticleInfo(index)->getAbundance()/m_total_abundance;
}


/* ************************************************************************* */
// add interference functions
/* ************************************************************************* */
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
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}


/* ************************************************************************* */
// create strategy
/* ************************************************************************* */
IInterferenceFunctionStrategy* ParticleDecoration::createStrategy(
        const std::vector<IFormFactor*>& form_factors) const
{
    std::vector<double> fractions;
    for (size_t i=0; i<m_particles.size(); ++i) {
        fractions.push_back(getAbundanceFractionOfParticle(i));
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

