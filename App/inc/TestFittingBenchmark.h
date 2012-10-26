#ifndef TESTFITTINGBENCHMARK_H
#define TESTFITTINGBENCHMARK_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingBenchmark.h
//! @brief  Definition of TestFittingBenchmark class
//! @author Scientific Computing Group at FRM II
//! @date   October 22, 2012

#include "IFunctionalTest.h"


//- -------------------------------------------------------------------
//! @class TestFittingBenchmark
//! @brief Test of minimizers with hard-to-minimize test functions
//- -------------------------------------------------------------------
class TestFittingBenchmark : public IFunctionalTest
{
public:
    TestFittingBenchmark();
    virtual ~TestFittingBenchmark(){}
    virtual void execute();

};

#endif // TESTFITTINGBENCHMARK_H
