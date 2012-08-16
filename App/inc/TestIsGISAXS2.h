#ifndef TESTISGISAXS2_H
#define TESTISGISAXS2_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS2.h
//! @brief  Definition of TestIsGISAXS2 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   16.08.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class TestIsGISAXS2
//! @brief Comparison with IsGISAXS ex-2: mean form factors for particles
//! with shape size distributions
//- -------------------------------------------------------------------
class TestIsGISAXS2 : public IFunctionalTest
{
public:
    TestIsGISAXS2();
    virtual ~TestIsGISAXS2(){}

    virtual void execute();
    virtual void finalise();



};

#endif // TESTISGISAXS2_H
