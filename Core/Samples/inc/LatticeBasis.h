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

#include "NanoParticle.h"
#include "Types.h"
#include <vector>

class LatticeBasis : public NanoParticle
{
public:
    LatticeBasis();
    LatticeBasis(const NanoParticle &particle);
    LatticeBasis(const NanoParticle &particle, std::vector<kvector_t > positions);
    virtual ~LatticeBasis();
    virtual LatticeBasis *clone() const;

    void addParticle(const NanoParticle &particle, kvector_t position);

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

     virtual IFormFactor* createFormFactor() const;

private:
     std::vector<NanoParticle *> m_particles;
     std::vector<kvector_t> m_positions;
};


#endif /* LATTICEBASIS_H_ */
