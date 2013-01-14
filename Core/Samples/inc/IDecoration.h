#ifndef IDECORATION_H_
#define IDECORATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IDecoration.h
//! @brief  Definition of IDecoration interface
//! @author Scientific Computing Group at FRM II
//! @date   Jun 22, 2012

#include "ICompositeSample.h"
#include "IInterferenceFunctionStrategy.h"
#include "IFormFactor.h"
#include "ParticleInfo.h"

class IDecoration : public ICompositeSample
{
public:
    IDecoration() : m_total_particle_surface_density(1.0) {}
    virtual ~IDecoration() {}

    virtual IDecoration *clone() const=0;
    virtual IInterferenceFunctionStrategy *createStrategy(
            const std::vector<IFormFactor *> &form_factors) const=0;

    /// Get number of particles
    virtual size_t getNumberOfParticles() const=0;

    /// get information about particle with index
    virtual const ParticleInfo *getParticleInfo(size_t index) const=0;

    /// Get surface density of all particles
    double getTotalParticleSurfaceDensity() const { return m_total_particle_surface_density; }

    /// Set surface density of all particles
    void setTotalParticleSurfaceDensity(double surface_density) { m_total_particle_surface_density = surface_density; }

private:
    ///< To guarantee that fractions sum up to 1
    double m_total_particle_surface_density;
};

#endif /* IDECORATION_H_ */
