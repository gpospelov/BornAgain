#ifndef NANOPARTICLE_H
#define NANOPARTICLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticle.h
//! @brief  Definition of NanoParticle
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ISample.h"
#include "IFormFactor.h"


class NanoParticle : public ISample
{
public:
    NanoParticle();
    virtual ~NanoParticle();

private:
    IFormFactor* mp_form_factor;
};

#endif // NANOPARTICLE_H
