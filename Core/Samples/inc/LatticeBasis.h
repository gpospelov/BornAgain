// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/LatticeBasis.h
//! @brief     Defines class LatticeBasis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICEBASIS_H_
#define LATTICEBASIS_H_

#include "IParticle.h"
#include "Types.h"
#include <vector>

//! @class LatticeBasis
//! @ingroup samples
//! @brief Basis of the lattice represented by the composition of particles

class BA_CORE_API_ LatticeBasis : public IParticle
{
public:
    LatticeBasis();
    explicit LatticeBasis(const IParticle& particle);
    LatticeBasis(const IParticle& particle, std::vector<kvector_t > positions);
    virtual ~LatticeBasis();
    virtual LatticeBasis *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual LatticeBasis *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    void addParticle(const IParticle& particle,
                     std::vector<kvector_t > positions);

    virtual void setAmbientMaterial(const IMaterial *p_material);
    virtual const IMaterial* getAmbientMaterial() const;

    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! Returns number of different particles
    size_t getNbrParticles() const {return m_particles.size(); }

    //! Returns number of positions for particle with index
    size_t getNbrPositionsForParticle(size_t index) const
    { return m_positions_vector[check_index(index)].size(); }

    //! Returns particle with given index
    const IParticle *getParticle(size_t index) const {
        return m_particles[check_index(index)];
    }

    std::vector<kvector_t> getParticlePositions(size_t index) const
    { return m_positions_vector[check_index(index)]; }

protected:
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform);

private:
    //! Checks index
    inline size_t check_index(size_t index) const {
        return index < m_positions_vector.size()
                ? index
                : throw OutOfBoundsException("LatticeBasis::check_index()"
                        "-> Index is out of bounds"); }

    //! For internal use in cloneInvertB():
    void addParticlePointer(IParticle *p_particle,
            std::vector<kvector_t > positions);

    std::vector<IParticle *> m_particles;
    std::vector<std::vector<kvector_t> > m_positions_vector;
};

#endif /* LATTICEBASIS_H_ */


