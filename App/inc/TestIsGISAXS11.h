#ifndef TESTISGISAXS11_H_
#define TESTISGISAXS11_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS11.h
//! @brief  Definition of TestIsGISAXS11 class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 1, 2012

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestIsGISAXS11
//! @brief Comparison with IsGISAXS ex-11:
//- -------------------------------------------------------------------
class TestIsGISAXS11 : public IFunctionalTest
{
public:
    TestIsGISAXS11(){}
    virtual ~TestIsGISAXS11(){}

    virtual void execute();
    virtual void finalise();
};


#endif /* TESTISGISAXS11_H_ */
