#ifndef LATTICEBASIS_H_
#define LATTICEBASIS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LatticeBasis.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 17, 2012

#include "Particle.h"
#include "Types.h"
#include <vector>

class LatticeBasis : public Particle
{
public:
    LatticeBasis();
    LatticeBasis(const Particle &particle);
    LatticeBasis(const Particle &particle, std::vector<kvector_t > positions);
    virtual ~LatticeBasis();
    virtual LatticeBasis *clone() const;

    void addParticle(const Particle &particle, std::vector<kvector_t > positions);

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

    virtual IFormFactor* createFormFactor() const;

    //! return number of different particles
    size_t getNbrParticles() const {return m_particles.size(); }

    //! return number of positions for particle with index
    size_t getNbrPositionsForParticle(size_t index) { return m_positions_vector[check_index(index)].size(); }

    //! return position of element with given index
//    kvector_t getPosition(size_t index) const { return m_positions[check_index(index)]; }

    //! return particle with given index
    const Particle *getParticle(size_t index) const { return m_particles[check_index(index)]; }

    std::vector<kvector_t> getParticlePositions(size_t index) const { return m_positions_vector[check_index(index)]; }

private:
    //! check index
    inline size_t check_index(size_t index) const { return index < m_positions_vector.size() ? index : throw OutOfBoundsException("LatticeBasis::check_index() -> Index is out of bounds"); }

    std::vector<Particle *> m_particles;
    std::vector<std::vector<kvector_t> > m_positions_vector;
};


#endif /* LATTICEBASIS_H_ */
