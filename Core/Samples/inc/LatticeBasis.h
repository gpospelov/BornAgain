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

    void addParticle(const Particle &particle, kvector_t position);

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

    virtual IFormFactor* createFormFactor() const;

    //! return number of elements
    size_t getNelements() const {return m_positions.size(); }

    //! return position of element with given index
    kvector_t getPosition(size_t indx) const { return m_positions[check_index(indx)]; }

    //! return particle with given index
    const Particle *getParticle(size_t indx) const { return m_particles[check_index(indx)]; }

private:
    //! check index
    inline size_t check_index(size_t indx) const { return indx < m_positions.size() ? indx : throw OutOfBoundsException("LatticeBasis::check_index() -> Index is out of bounds"); }

    std::vector<Particle *> m_particles;
    std::vector<kvector_t> m_positions;
};


#endif /* LATTICEBASIS_H_ */
