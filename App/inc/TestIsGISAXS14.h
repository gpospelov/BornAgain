#ifndef TESTISGISAXS14_H
#define TESTISGISAXS14_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS14.h
//! @brief  Definition of TestIsGISAXS14 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   Jan 28, 2013

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestIsGISAXS14
//! @brief Comparison with IsGISAXS ex-14: multi layered sphere on graded interface
//- -------------------------------------------------------------------
class TestIsGISAXS14 : public IFunctionalTest
{
public:
    TestIsGISAXS14();
    virtual ~TestIsGISAXS14() {}
    virtual void execute();
    virtual void finalise();
};

#endif // TESTISGISAXS14_H
