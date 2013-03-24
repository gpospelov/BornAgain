// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestMiscellaneous.h 
//! @brief     Defines class TestMiscellaneous.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTMISCELLANEOUS_H
#define TESTMISCELLANEOUS_H

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

    //! test of OutputData export to 2D array
    void test_OutputDataTo2DArray();

    //! testing of loggin system
    void test_LogSystem();

};

#endif // TESTMISCELLANEOUS_H
