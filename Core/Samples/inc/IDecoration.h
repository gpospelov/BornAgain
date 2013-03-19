// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IDecoration.h
//! @brief     Defines class IDecoration.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IDECORATION_H_
#define IDECORATION_H_

#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "ParticleInfo.h"
#include "SafePointerVector.h"

class IInterferenceFunctionStrategy;
class IInterferenceFunction;

//! ?

class IDecoration : public ICompositeSample
{
public:
    IDecoration() : m_total_particle_surface_density(1.0) {}
    virtual ~IDecoration() {}

    virtual IDecoration *clone() const=0;

    //! Get number of particles
    virtual size_t getNumberOfParticles() const=0;

    //! get information about particle with index
    virtual const ParticleInfo *getParticleInfo(size_t index) const=0;

    /// Get abundance fraction of particle with index
    virtual double getAbundanceFractionOfParticle(size_t index) const=0;

    //! get number of interference functions
    virtual size_t getNumberOfInterferenceFunctions() const { return 0; }

    //! get interference functions
    virtual SafePointerVector<IInterferenceFunction> getInterferenceFunctions() const=0;

    //! get surface density of all particles
    double getTotalParticleSurfaceDensity() const { return m_total_particle_surface_density; }

    //! set surface density of all particles
    void setTotalParticleSurfaceDensity(double surface_density) { m_total_particle_surface_density = surface_density; }

private:
    ///< To guarantee that fractions sum up to 1
    double m_total_particle_surface_density;
};

#endif /* IDECORATION_H_ */
