#ifndef DISPERSEDPARTICLEDECORATOR_H
#define DISPERSEDPARTICLEDECORATOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DispersedParticleDecorator.h
//! @brief  Defenition of DispersedParticleDecorator
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "ISample.h"


class DispersedParticleDecorator : public ISample
{
public:
    DispersedParticleDecorator(ISample* p_sub_sample);
    virtual ~DispersedParticleDecorator() {}

    ISample* getSubSample() const { return mp_sub_sample; }

private:
    ISample* mp_sub_sample;

};

#endif // DISPERSEDPARTICLEDECORATOR_H
