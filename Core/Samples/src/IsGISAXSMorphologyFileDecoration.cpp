#include "IsGISAXSMorphologyFileDecoration.h"

IsGISAXSMorphologyFileDecoration::IsGISAXSMorphologyFileDecoration()
: m_total_abundance(0.0)
, m_total_particle_surface_density(1.0)
{
    setName("IsGISAXSMorphologyFileDecoration");
}

IsGISAXSMorphologyFileDecoration::~IsGISAXSMorphologyFileDecoration()
{
}

IsGISAXSMorphologyFileDecoration* IsGISAXSMorphologyFileDecoration::clone() const
{
    IsGISAXSMorphologyFileDecoration *p_clone = new IsGISAXSMorphologyFileDecoration();
    p_clone->setName(getName());
    //TODO: add members
    return p_clone;
}

void IsGISAXSMorphologyFileDecoration::addParticle(Particle* p_particle,
        Geometry::Transform3D *p_transform, kvector_t position, double abundance)
{
    addAndRegisterParticleInfo( new PositionParticleInfo(p_particle, p_transform, position, abundance) );
}

void IsGISAXSMorphologyFileDecoration::addParticle(const Particle& particle,
        const Geometry::Transform3D& transform, kvector_t position, double abundance)
{
    addParticle(particle.clone(), new Geometry::Transform3D(transform), position, abundance);
}

void IsGISAXSMorphologyFileDecoration::addParticle(const Particle& particle,
        kvector_t position, double abundance)
{
    addParticle(particle.clone(), 0, position, abundance);
}

void IsGISAXSMorphologyFileDecoration::addParticle(Particle* p_particle,
        kvector_t position, double abundance)
{
    addParticle(p_particle, 0, position, abundance);
}

void IsGISAXSMorphologyFileDecoration::addParticleInfo(
        const PositionParticleInfo& info)
{
    addAndRegisterParticleInfo( info.clone() );
}

const PositionParticleInfo* IsGISAXSMorphologyFileDecoration::getParticleInfo(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index];
    }
    throw OutOfBoundsException("IsGISAXSMorphologyFileDecoration::getParticleInfo() -> Error! Not so many particles in this decoration.");
}

double IsGISAXSMorphologyFileDecoration::getAbundanceFractionOfParticle(size_t index) const
{
    return getParticleInfo(index)->getAbundance()/m_total_abundance;
}

void IsGISAXSMorphologyFileDecoration::addInterferenceFunction(
        IInterferenceFunction* p_interference_function)
{
    addAndRegisterInterferenceFunction(p_interference_function);
}

void IsGISAXSMorphologyFileDecoration::addInterferenceFunction(
        const IInterferenceFunction& interference_function)
{
    addAndRegisterInterferenceFunction(interference_function.clone());
}

const IInterferenceFunction* IsGISAXSMorphologyFileDecoration::getInterferenceFunction(
        size_t index) const
{
    if (index<m_interference_functions.size()) {
        return m_interference_functions[index];
    }
    throw OutOfBoundsException("IsGISAXSMorphologyFileDecoration::getInterferenceFunction() -> Not so many interference functions in this decoration.");
}

IInterferenceFunctionStrategy* IsGISAXSMorphologyFileDecoration::createStrategy(
        const std::vector<IFormFactor*>& form_factors) const
{
}
