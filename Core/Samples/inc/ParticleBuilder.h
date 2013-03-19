// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Samples/ParticleBuilder.h 
//! @brief     Defines class ParticleBuilder.
//
// ************************************************************************** //

#ifndef PARTICLEBUILDER_H
#define PARTICLEBUILDER_H

#include "Particle.h"
#include "IStochasticParameter.h"
#include "ParticleDecoration.h"

//! @class ParticleBuilder
//! @brief To build set of particles with similar properties
//!
//! currently produces particles but probably can produce directly
//! ParticleInfo, or even ISample

class ParticleBuilder
{
public:
    ParticleBuilder();
    virtual ~ParticleBuilder();

    //! set prototype for particle production
    //! @param particle   prototype of particle
    //! @param name       parameter name in the parameter pool of given prototype
    //! @param parameter  variation type
    //! @param scale      global scale factor for probabilities
    void setPrototype(const Particle &particle, std::string name, const StochasticParameter<double> &param, double scale=1.0);

    //! plant particles in given decoration
    void plantParticles(ParticleDecoration &decor);

private:
    Particle *m_prototype; //!< prototype of the particle, all particles will be cloned from it
    std::string m_parameter_name; //!< name of parameter to variate
    StochasticParameter<double > *m_parameter;
    double m_scale; //!< global scale factor for probabilities
};

#endif // PARTICLEBUILDER_H
