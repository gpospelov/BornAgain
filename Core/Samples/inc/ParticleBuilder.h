#ifndef PARTICLEBUILDER_H
#define PARTICLEBUILDER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ParticleBuilder.h
//! @brief  Definition of ParticleBuilder class
//! @author Scientific Computing Group at FRM II
//! @date   20.08.2012

#include "Particle.h"
#include "IStochasticParameter.h"
#include "ParticleDecoration.h"


//- -------------------------------------------------------------------
//! @class ParticleBuilder
//! @brief To build set of particles with similar properties
//!
//! currently produces particles but probably can produce directly
//! ParticleInfo, or even ISample
//- -------------------------------------------------------------------
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
