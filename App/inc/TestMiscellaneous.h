#ifndef TESTMISCELLANEOUS_H
#define TESTMISCELLANEOUS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMiscellaneous.h
//! @brief  Collection of functional tests for miscellaneous issues
//! @author Scientific Computing Group at FRM II
//! @date   02.07.2012

#include "IFunctionalTest.h"


//- -------------------------------------------------------------------
//! @class TestMiscellaneous
//! @brief Collection of functional tests for miscellaneous issues
//- -------------------------------------------------------------------
class TestMiscellaneous : public IFunctionalTest
{
public:
    TestMiscellaneous();
    virtual ~TestMiscellaneous(){}

    virtual void execute();

    //! test double to complex interpolating function
    void test_DoubleToComplexInterpolatingFunction();

    //! form factor as a function of qx,qy,qz
    void test_FormFactor();

    //! opengl mesocrystal drawing
    void test_DrawMesocrystal();

    //! test of fast sin function approximation
    void test_FastSin();

    //! test of reading of OutputData from ASCII file
    void test_OutputDataIOFactory();

    //! test kvector container
    void test_KVectorContainer();

};

#endif // TESTMISCELLANEOUS_H
