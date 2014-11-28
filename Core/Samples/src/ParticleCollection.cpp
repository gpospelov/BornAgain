// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleCollection.cpp
//! @brief     Implements class ParticleCollection.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCollection.h"


ParticleCollection::ParticleCollection(const IParticle &prototype,
                                       const ParameterDistribution &par_distr)
    : m_par_distribution(par_distr)
{
    mP_particle.reset(prototype.clone());
    setName("ParticleCollection");
}

ParticleCollection *ParticleCollection::clone() const
{
    ParticleCollection *p_result = new ParticleCollection(*mP_particle,
                                                          m_par_distribution);
    return p_result;
}

ParticleCollection *ParticleCollection::cloneInvertB() const
{
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "cloneInvertB: should never be called");
}

IFormFactor *ParticleCollection::createFormFactor(
        complex_t wavevector_scattering_factor) const {
    (void)wavevector_scattering_factor;
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "createFormFactor: should never be called");
}

const IFormFactor *ParticleCollection::getSimpleFormFactor() const {
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "getSimpleFormFactor: should never be called");
}

void ParticleCollection::applyTransformationToSubParticles(
        const Geometry::Transform3D& transform)
{
    mP_particle->applyTransformation(transform);
    return;
}


