#ifndef NANOPARTICLEBUILDER_H
#define NANOPARTICLEBUILDER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleBuilder.h
//! @brief  Definition of NanoParticleBuilder class
//! @author Scientific Computing Group at FRM II
//! @date   20.08.2012

#include "NanoParticle.h"
#include "IStochasticParameter.h"
#include "NanoParticleDecoration.h"


//- -------------------------------------------------------------------
//! @class NanoParticleBuilder
//! @brief To build set of nanoparticles with similar properties
//!
//! currently produces nano particles but probably can produce directly
//! NanoParticleInfo, or even ISample
//- -------------------------------------------------------------------
class NanoParticleBuilder
{
public:
    NanoParticleBuilder();
    virtual ~NanoParticleBuilder();

    //! set prototype for nano particle production
    //! @param particle   prototype of nano particle
    //! @param name       parameter name in the parameter pool of given prototype
    //! @param parameter  variation type
    //! @param scale      global scale factor for probabilities
    void setPrototype(const NanoParticle &particle, std::string name, const StochasticParameter<double> &param, double scale=1.0);

    //! plant nano particles in given decoration
    void plantNanoParticles(NanoParticleDecoration &decor);

private:
    NanoParticle *m_prototype; //!< prototype of the particle, all particles will be cloned from it
    std::string m_parameter_name; //!< name of parameter to variate
    StochasticParameter<double > *m_parameter;
    double m_scale; //!< global scale factor for probabilities
};


#endif // NANOPARTICLEBUILDER_H
