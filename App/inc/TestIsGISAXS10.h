#ifndef TESTISGISAXS10_H_
#define TESTISGISAXS10_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS10.h
//! @brief  Definition of TestIsGISAXS10 class for IsGISAXS validation
//! @author herk
//! @date   19.06.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "DWBAFormFactor.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"


class TestIsGISAXS10 : public IFunctionalTest
{
public:
	TestIsGISAXS10();
    virtual ~TestIsGISAXS10();
    virtual void execute();
    void draw();
    void write();

private:
    void initializeSample();
    ISample *mp_sample;
    OutputData<double> *mp_intensity_output;
};

#endif /* TESTISGISAXS10_H_ */
