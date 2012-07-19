#include "LatticeBasis.h"
#include "WeightedFormFactor.h"
#include "FormFactorDecoratorPositionFactor.h"

LatticeBasis::LatticeBasis()
: NanoParticle(complex_t(1.0, 0.0))
{
}

LatticeBasis::LatticeBasis(const NanoParticle& particle)
: NanoParticle(complex_t(1.0, 0.0))
{
    m_particles.push_back(particle.clone());
    m_positions.push_back(kvector_t(0.0, 0.0, 0.0));
}

LatticeBasis::LatticeBasis(const NanoParticle& particle,
        std::vector<kvector_t> positions)
: NanoParticle(complex_t(1.0, 0.0))
, m_positions(positions)
{
    for (size_t index=0; index<m_positions.size(); ++index) {
        m_particles.push_back(particle.clone());
    }
}

LatticeBasis::~LatticeBasis()
{
    for (size_t index=0; index<m_particles.size(); ++index) {
        delete m_particles[index];
    }
}

LatticeBasis* LatticeBasis::clone() const
{
    LatticeBasis *p_new = new LatticeBasis();
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addParticle(*m_particles[index], m_positions[index]);
    }
    return p_new;
}

void LatticeBasis::addParticle(const NanoParticle& particle, kvector_t position)
{
    m_particles.push_back(particle.clone());
    m_positions.push_back(position);
}

void LatticeBasis::setAmbientRefractiveIndex(complex_t refractive_index)
{
    NanoParticle::setAmbientRefractiveIndex(refractive_index);
    for (size_t index=0; index<m_particles.size(); ++index) {
        m_particles[index]->setAmbientRefractiveIndex(refractive_index);
    }
}

IFormFactor* LatticeBasis::createFormFactor() const
{
    WeightedFormFactor *p_ff = new WeightedFormFactor();
    for (size_t index=0; index<m_particles.size(); ++index) {
        IFormFactor *p_particle_ff = m_particles[index]->createFormFactor();
        FormFactorDecoratorPositionFactor pos_ff(*p_particle_ff, m_positions[index]);
        p_ff->addFormFactor(pos_ff);
        delete p_particle_ff;
    }
    p_ff->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_ff;
}
