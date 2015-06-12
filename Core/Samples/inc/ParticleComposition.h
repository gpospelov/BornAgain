// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleComposition.h
//! @brief     Defines class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITION_H_
#define PARTICLECOMPOSITION_H_

#include "IParticle.h"
#include "Types.h"
#include <vector>

//! @class ParticleComposition
//! @ingroup samples
//! @brief A composition of particles at fixed positions

class BA_CORE_API_ ParticleComposition : public IParticle
{
public:
    ParticleComposition();
    explicit ParticleComposition(const IParticle& particle);
    ParticleComposition(const IParticle& particle, kvector_t position);
    ParticleComposition(const IParticle& particle, std::vector<kvector_t > positions);
    virtual ~ParticleComposition();
    virtual ParticleComposition *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleComposition *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    void addParticle(const IParticle& particle, kvector_t  position);
    void addParticles(const IParticle& particle, std::vector<kvector_t > positions);

    virtual void setAmbientMaterial(const IMaterial& material);
    virtual const IMaterial* getAmbientMaterial() const;

    //! Create a form factor for this particle with an extra scattering factor
    virtual IFormFactor *createTransformedFormFactor(complex_t wavevector_scattering_factor,
                                                     const IRotation* p_rotation,
                                                     kvector_t translation) const;

    //! Returns number of different particles
    size_t getNbrParticles() const {return m_particles.size(); }

    //! Returns particle with given index
    const IParticle *getParticle(size_t index) const {
        return m_particles[check_index(index)];
    }

    kvector_t getParticlePosition(size_t index) const
    { return m_particles[check_index(index)]->getPosition(); }

protected:
    virtual void applyTransformationToSubParticles(const IRotation& rotation);

private:
    //! Checks index
    inline size_t check_index(size_t index) const {
        return index < m_particles.size()
                ? index
                : throw OutOfBoundsException("ParticleComposition::check_index()"
                        "-> Index is out of bounds"); }

    //! For internal use in cloneInvertB():
    void addParticlePointer(IParticle *p_particle);

    void addParticleNoPosition(const IParticle& particle);

    std::vector<IParticle *> m_particles;
};

#endif /* PARTICLECOMPOSITION_H_ */


