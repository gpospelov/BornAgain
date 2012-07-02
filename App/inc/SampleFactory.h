#ifndef SAMPLEFACTORY_H
#define SAMPLEFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SampleFactory.h
//! @brief  Definition of SampleFactory class
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "ISingleton.h"
#include "IFactory.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class SampleFactory
//! @brief Factory to create standard pre-defined samples
//! Samples itself are defined in StandardSamples.{h, cxx}
//- -------------------------------------------------------------------
class SampleFactory : public ISingleton<SampleFactory>, public IFactory<std::string, ISample>
{
public:
    SampleFactory();

    static ISample *createSample(const std::string &sample_name) { return instance().createItem(sample_name); }
};

#endif // SAMPLEFACTORY_H

