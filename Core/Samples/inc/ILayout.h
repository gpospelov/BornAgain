// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ILayout.h
//! @brief     Defines interface class ILayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYOUT_H_
#define ILAYOUT_H_

#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "ParticleInfo.h"
#include "SafePointerVector.h"

class IInterferenceFunctionStrategy;
class IInterferenceFunction;

//! @class ILayout
//! @ingroup samples_internal
//! @brief Interface to equip a sample component with various properties.

class BA_CORE_API_ ILayout : public ICompositeSample
{
public:
    enum EInterferenceApproximation { DA, SSCA, ISGISAXSMOR };

    ILayout() : m_total_particle_surface_density(1.0)
              , me_approx(DA) {}
    virtual ~ILayout() {}

    virtual ILayout *clone() const=0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const=0;

    //! Returns a clone with inverted magnetic fields
    virtual ILayout *cloneInvertB() const=0;

    //! Returns number of particles
    virtual size_t getNumberOfParticles() const=0;

    //! Returns information about particle with index
    virtual const ParticleInfo *getParticleInfo(size_t index) const=0;

    /// Get abundance fraction of particle with index
    virtual double getAbundanceOfParticle(size_t index) const=0;

    /// Get total abundance of all particles
    double getTotalAbundance() const;

    //! Returns number of interference functions
    virtual size_t getNumberOfInterferenceFunctions() const { return 0; }

    //! Returns interference functions
    virtual SafePointerVector<IInterferenceFunction>
        getInterferenceFunctions() const=0;

    //! Returns surface density of all particles
    double getTotalParticleSurfaceDensity() const
    { return m_total_particle_surface_density; }

    //! Sets surface density of all particles
    void setTotalParticleSurfaceDensity(double surface_density)
    { m_total_particle_surface_density = surface_density; }

    //! Gets the used approximation for particles and interference functions
    EInterferenceApproximation getApproximation() const {
        return me_approx;
    }

    //! Sets the used approximation for particles and interference functions
    void setApproximation(EInterferenceApproximation approximation) {
        me_approx = approximation;
    }

private:
    ///< To guarantee that fractions sum up to 1
    double m_total_particle_surface_density;
    ///< Approximation used for combining particles and interference functions
    EInterferenceApproximation me_approx;
};


inline double ILayout::getTotalAbundance() const
{
    double total_abundance = 0.0;
    for (size_t i=0; i<getNumberOfParticles(); ++i) {
        total_abundance += getAbundanceOfParticle(i);
    }
    return total_abundance;
}

#endif /* ILAYOUT_H_ */
