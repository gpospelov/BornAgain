// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/LatticeBasis.cpp
//! @brief     Implements class LatticeBasis.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LatticeBasis.h"
#include "FormFactors.h"
#include "DiffuseParticleInfo.h"
#include "Materials.h"
#include <boost/scoped_ptr.hpp>

LatticeBasis::LatticeBasis()
{
    setName("LatticeBasis");
}

LatticeBasis::LatticeBasis(const Particle& particle)
{
    setName("LatticeBasis");
    std::vector<kvector_t> positions;
    positions.push_back(kvector_t(0.0, 0.0, 0.0));
    addParticle( particle, positions );
}

LatticeBasis::LatticeBasis(const Particle& particle,
        std::vector<kvector_t> positions)
{
    setName("LatticeBasis");
    addParticle(particle, positions);
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
        p_new->addParticle(*m_particles[index], m_positions_vector[index]);
    }
    p_new->setName(getName());
    p_new->setAmbientMaterial(this->mp_ambient_material);
    if (mP_transform.get()) {
        p_new->mP_transform.reset(mP_transform->clone());
    }
    return p_new;
}

LatticeBasis* LatticeBasis::cloneInvertB() const
{
    LatticeBasis *p_new = new LatticeBasis();
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addParticlePointer(m_particles[index]->cloneInvertB(),
                m_positions_vector[index]);
    }
    p_new->setName(getName() + "_inv");

    if(mp_ambient_material)
        p_new->mp_ambient_material = Materials::createInvertedMaterial(mp_ambient_material);

    if (mP_transform.get())
        p_new->mP_transform.reset(mP_transform->clone());

    return p_new;
}

void LatticeBasis::addParticle(const Particle& particle,
        std::vector<kvector_t > positions)
{
    Particle *np = particle.clone();
    registerChild(np);
    m_particles.push_back(np);
    m_positions_vector.push_back(positions);
}

void LatticeBasis::setAmbientMaterial(const IMaterial *p_material)
{
    if(!p_material) return;
    Particle::setAmbientMaterial(p_material);
    for (size_t index=0; index<m_particles.size(); ++index) {
        m_particles[index]->setAmbientMaterial(p_material);
    }
}

IFormFactor* LatticeBasis::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    FormFactorWeighted *p_ff = new FormFactorWeighted();
    for (size_t index=0; index<m_particles.size(); ++index) {
        boost::scoped_ptr<IFormFactor> P_particle_ff(
                m_particles[index]->createFormFactor(
                                      wavevector_scattering_factor));
        FormFactorDecoratorMultiPositionFactor pos_ff(*P_particle_ff,
                m_positions_vector[index]);
        p_ff->addFormFactor(pos_ff);
    }
    p_ff->setAmbientMaterial(mp_ambient_material);
    return p_ff;
}

std::vector<DiffuseParticleInfo *>
LatticeBasis::createDiffuseParticleInfos() const
{
    std::vector<DiffuseParticleInfo *> result;
    for (size_t index=0; index<getNbrParticles(); ++index) {
        const Particle *p_particle = getParticle(index);
        if (p_particle->hasDistributedFormFactor()) {
            DiffuseParticleInfo *p_new_info = new DiffuseParticleInfo(
                    *p_particle);
            p_new_info->setNumberPerMeso(
                    (double)getNbrPositionsForParticle(index));
            result.push_back(p_new_info);
        }
    }
    return result;
}

void LatticeBasis::applyTransformationToSubParticles(
        const Geometry::Transform3D& transform)
{
    for (std::vector<Particle *>::iterator it = m_particles.begin();
            it != m_particles.end(); ++it)
    {
        (*it)->applyTransformation(transform);
    }
    for (std::vector<std::vector<kvector_t> >::iterator it_vec =
            m_positions_vector.begin(); it_vec != m_positions_vector.end();
            ++it_vec) {
        for (std::vector<kvector_t>::iterator it_vec_el = it_vec->begin();
                it_vec_el != it_vec->end(); ++it_vec_el) {
            *it_vec_el = transform.transformed(*it_vec_el);
        }
    }
}

void LatticeBasis::addParticlePointer(Particle* p_particle,
        std::vector<kvector_t> positions)
{
    registerChild(p_particle);
    m_particles.push_back(p_particle);
    m_positions_vector.push_back(positions);
}

