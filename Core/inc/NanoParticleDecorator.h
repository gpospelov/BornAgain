#ifndef NANOPARTICLEDECORATOR_H
#define NANOPARTICLEDECORATOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleDecorator.h
//! @brief  Definition of NanoParticleDecorator
//! @author Scientific Computing Group at FRM II
//! @date   23.05.2012

#include "NanoParticle.h"

//- -------------------------------------------------------------------
//! @class NanoParticleDecorator
//! @brief Definition of decorator class that adds nano particles to ISample objects
//- -------------------------------------------------------------------
class NanoParticleDecorator : public ISample
{
public:
	NanoParticleDecorator(ISample *p_sub_sample);
	virtual ~NanoParticleDecorator() {}

	/// Return decorated sample
	ISample* getSubSample() const { return mp_sub_sample; }

private:
	std::vector<NanoParticle *> m_particles;  ///< Vector of the types of nano particles
    ISample* mp_sub_sample;                   ///< Decorated ISample object

};


#endif // NANOPARTICLEDECORATOR_H
