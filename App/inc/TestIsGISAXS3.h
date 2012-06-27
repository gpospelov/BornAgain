#ifndef TESTISGISAXS3_H_
#define TESTISGISAXS3_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS3.h
//! @brief  Definition of TestIsGISAXS3 class for IsGISAXS validation
//! @author herk
//! @date   02.05.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "DWBAFormFactor.h"
#include "ISample.h"
#include "DWBAFormFactorConstZ.h"


class TestIsGISAXS3 : public IFunctionalTest
{
public:
    TestIsGISAXS3();
    virtual ~TestIsGISAXS3();
    virtual void execute();
    void draw();
    void write();

private:
    void initializeSample();
    ISample *mp_sample;
    OutputData<double> *mp_intensity_output;
};
#endif /* TESTISGISAXS3_H_ */
