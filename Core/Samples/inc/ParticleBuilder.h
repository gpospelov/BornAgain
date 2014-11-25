// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleBuilder.h
//! @brief     Defines class ParticleBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEBUILDER_H
#define PARTICLEBUILDER_H

#include "Particle.h"
#include "Distributions.h"
#include "ParticleLayout.h"

//! @class ParticleBuilder
//! @ingroup samples_internal
//! @brief To build set of particles with similar properties

class BA_CORE_API_ ParticleBuilder
{
public:
    ParticleBuilder();
    virtual ~ParticleBuilder();

    //! Sets prototype for particle production
    //! @param particle   prototype of particle
    //! @param name       parameter name in the parameter pool of given prototype
    //! @param parameter  variation type
    //! @param scale      global scale factor for probabilities
    void setPrototype(const Particle& particle, std::string name,
                      const IDistribution1D& distribution, size_t nbr_samples,
                      double sigma_factor=0.0, double scale=1.0);

    //! plant particles in given decoration
    void plantParticles(ParticleLayout& layout);

private:
    //! prototype of the particle, all particles will be cloned from it
    Particle *mp_prototype;
    std::string m_parameter_name;  //!< name of parameter to vary
    IDistribution1D *mp_distribution;  //!< distribution for the parameter
    size_t m_nbr_samples;  //!< number of particles to be created
    double m_sigma_factor;  //!< range of parameter in sigma or HWHM
    double m_scale;  //!< global scale factor for probabilities
};

#endif // PARTICLEBUILDER_H


