#include "LatticeBasis.h"
#include "FormFactorWeighted.h"
#include "FormFactorDecoratorPositionFactor.h"

LatticeBasis::LatticeBasis()
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
}

LatticeBasis::LatticeBasis(const Particle& particle)
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
    addParticle( particle, kvector_t(0.0, 0.0, 0.0) );
}

LatticeBasis::LatticeBasis(const Particle& particle,
        std::vector<kvector_t> positions)
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
    for (size_t index=0; index<positions.size(); ++index) {
        addParticle( particle, positions[index] );
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
    p_new->setName(getName());
    p_new->m_ambient_refractive_index = this->m_ambient_refractive_index;
    return p_new;
}

void LatticeBasis::addParticle(const Particle& particle, kvector_t position)
{
    Particle *np = particle.clone();
    registerChild(np);
    m_particles.push_back(np);
    m_positions.push_back(position);
}

void LatticeBasis::setAmbientRefractiveIndex(complex_t refractive_index)
{
    Particle::setAmbientRefractiveIndex(refractive_index);
    for (size_t index=0; index<m_particles.size(); ++index) {
        m_particles[index]->setAmbientRefractiveIndex(refractive_index);
    }
}

IFormFactor* LatticeBasis::createFormFactor() const
{
    // TODO: for equal particles, create position superposition times the formfactor
    FormFactorWeighted *p_ff = new FormFactorWeighted();
    for (size_t index=0; index<m_particles.size(); ++index) {
        IFormFactor *p_particle_ff = m_particles[index]->createFormFactor();
        FormFactorDecoratorPositionFactor pos_ff(*p_particle_ff, m_positions[index]);
        p_ff->addFormFactor(pos_ff);
        delete p_particle_ff;
    }
    p_ff->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_ff;
}
