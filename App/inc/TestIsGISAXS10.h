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
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class TestIsGISAXS10
//! @brief Comparison with IsGISAXS ex-10: cylinder with interference on top of substrate
//- -------------------------------------------------------------------
class TestIsGISAXS10 : public IFunctionalTest
{
public:
    TestIsGISAXS10(){}
    virtual ~TestIsGISAXS10(){}

    virtual void execute();
    virtual void finalise();

    //void initializeSample2();
};

#endif /* TESTISGISAXS10_H_ */
