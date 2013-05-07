// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/LatticeBasis.h
//! @brief     Defines class LatticeBasis.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICEBASIS_H_
#define LATTICEBASIS_H_

#include "Particle.h"
#include "Types.h"
#include <vector>

class LatticeBasis : public Particle
{
 public:
    LatticeBasis();
    LatticeBasis(const Particle& particle);
    LatticeBasis(const Particle& particle, std::vector<kvector_t > positions);
    virtual ~LatticeBasis();
    virtual LatticeBasis *clone() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) { p_visitor->visit(this); }

    void addParticle(const Particle& particle, std::vector<kvector_t > positions);

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

    virtual IFormFactor* createFormFactor() const;

    //! Returns number of different particles
    size_t getNbrParticles() const {return m_particles.size(); }

    //! Returns number of positions for particle with index
    size_t getNbrPositionsForParticle(size_t index) const
    { return m_positions_vector[check_index(index)].size(); }

    //! Returns position of element with given index
//    kvector_t getPosition(size_t index) const { return m_positions[check_index(index)]; }

    //! Returns particle with given index
    const Particle *getParticle(size_t index) const { return m_particles[check_index(index)]; }

    std::vector<kvector_t> getParticlePositions(size_t index) const
    { return m_positions_vector[check_index(index)]; }

    //! Creates vector of size/shape distributed particles corresponding to the particle with index i
    std::vector<DiffuseParticleInfo *> createDiffuseParticleInfos() const;

 private:
    //! Checks index
    inline size_t check_index(size_t index) const { return index < m_positions_vector.size() ? index : throw OutOfBoundsException("LatticeBasis::check_index() -> Index is out of bounds"); }

    std::vector<Particle *> m_particles;
    std::vector<std::vector<kvector_t> > m_positions_vector;
};

#endif /* LATTICEBASIS_H_ */


