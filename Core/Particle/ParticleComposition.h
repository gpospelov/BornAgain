// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleComposition.h
//! @brief     Defines class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITION_H
#define PARTICLECOMPOSITION_H

#include "IParticle.h"
#include <memory>

class HomogeneousMaterial;

//! A composition of particles at fixed positions
//! @ingroup samples

class BA_CORE_API_ ParticleComposition : public IParticle
{
public:
    ParticleComposition();
    ParticleComposition(const IParticle& particle, std::vector<kvector_t > positions);

    ~ParticleComposition();
    ParticleComposition* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void addParticle(const IParticle& particle);
    void addParticle(const IParticle& particle, kvector_t  position);
    void addParticles(const IParticle& particle, std::vector<kvector_t > positions);

    //! Create a sliced form factor for this particle
    SlicedParticle createSlicedParticle(ZLimits limits) const override;

    //! Returns number of different particles
    size_t nbrParticles() const { return m_particles.size(); }

    //! Returns particle with given index
    const IParticle* particle(size_t index) const;

    kvector_t particlePosition(size_t index) const;

    std::vector<const INode*> getChildren() const override;

    SafePointerVector<IParticle> decompose() const override;

    ParticleLimits bottomTopZ() const override;
private:
    size_t check_index(size_t index) const;

    //! Returns true if particle's type is suitable for adding
    void checkParticleType(const IParticle& p_particle);

    //! For internal use
    void addParticlePointer(IParticle* p_particle);

    std::vector<std::unique_ptr<IParticle>> m_particles;
    void initialize();
};

#endif // PARTICLECOMPOSITION_H
