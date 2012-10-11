#ifndef ISAMPLEBUILDER_H_
#define ISAMPLEBUILDER_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISampleBuilder.h
//! @brief  Definition of ISampleBuilder interface
//! @author Scientific Computing Group at FRM II
//! @date   Oct 11, 2012

#include "IParameterized.h"
#include "ISample.h"

class ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() { setName("SampleBuilder"); }
    virtual ~ISampleBuilder() {}

    virtual ISample *buildSample() const { throw; }
protected:
};


#endif /* ISAMPLEBUILDER_H_ */
