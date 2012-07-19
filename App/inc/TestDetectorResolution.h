#ifndef TESTDETECTORRESOLUTION_H_
#define TESTDETECTORRESOLUTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestDetectorResolution.h
//! @brief  Definition of TestDetectorResolution functional test class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 10, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "DWBAFormFactor.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"


class TestDetectorResolution : public IFunctionalTest
{
public:
    TestDetectorResolution();
    virtual ~TestDetectorResolution();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};

#endif /* TESTDETECTORRESOLUTION_H_ */
