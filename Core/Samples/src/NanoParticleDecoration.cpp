#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "LocalMonodisperseApproximationStrategy.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
: m_total_abundance(0.0)
{
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
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

    for (size_t i=0; i<m_particles.size(); ++i) {
        p_new->addNanoParticleInfo(m_particles[i]->clone());
    }

    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        p_new->addInterferenceFunction(m_interference_functions[i]->clone());
    }

    p_new->m_total_abundance = m_total_abundance;

    return p_new;
}

void NanoParticleDecoration::addNanoParticle(NanoParticle* p_particle,
        double depth, double abundance)
{
    addNanoParticle(p_particle, 0, depth, abundance);
}

void NanoParticleDecoration::addNanoParticle(const NanoParticle &p_particle,
        double depth, double abundance)
{
    addNanoParticle(p_particle.clone(), 0, depth, abundance);
}


void NanoParticleDecoration::addNanoParticle(NanoParticle* p_particle,
        Geometry::Transform3D *transform, double depth, double abundance)
{
    addNanoParticleInfo( new NanoParticleInfo(p_particle, transform, depth, abundance) );
    m_total_abundance += abundance;
}

void NanoParticleDecoration::addNanoParticle(const NanoParticle &p_particle,
        const Geometry::Transform3D &transform, double depth, double abundance)
{
    addNanoParticle(p_particle.clone(), new Geometry::Transform3D(transform), depth, abundance);
}


//const NanoParticle* NanoParticleDecoration::getNanoParticle(size_t index) const
//{
//    if (index<m_particles.size()) {
//        //return m_particles[index].mp_particle->clone();
//        return m_particles[index].mp_particle;
//    }
//    throw OutOfBoundsException("Not so many particles in this decoration.");
//}

//double NanoParticleDecoration::getDepthOfNanoParticle(size_t index) const
//{
//    if (index<m_particles.size()) {
//        return m_particles[index].m_depth;
//    }
//    throw OutOfBoundsException("Not so many particles in this decoration.");
//}


//Geometry::Transform3D * NanoParticleDecoration::getTransformationOfNanoParticle(size_t index) const
//{
//    if (index<m_particles.size()) {
//        return m_particles[index].m_transform;
//    }
//    throw OutOfBoundsException("Not so many particles in this decoration.");
//}



double NanoParticleDecoration::getAbundanceFractionOfNanoParticle(size_t index) const
{
    return getNanoParticleInfo(index)->getAbundance()/m_total_abundance;
}


void NanoParticleDecoration::addInterferenceFunction(IInterferenceFunction* p_interference_function)
{
    m_interference_functions.push_back(p_interference_function);
}


void NanoParticleDecoration::addInterferenceFunction(const IInterferenceFunction &interference_function)
{
    m_interference_functions.push_back(interference_function.clone());
}


void NanoParticleDecoration::addNanoParticleInfo(NanoParticleInfo *info)
{
    m_particles.push_back(info);
}


const IInterferenceFunction* NanoParticleDecoration::getInterferenceFunction(size_t index) const
{
    if (index<m_interference_functions.size()) {
        return m_interference_functions[index];
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}


const NanoParticleInfo* NanoParticleDecoration::getNanoParticleInfo(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index];
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}


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

