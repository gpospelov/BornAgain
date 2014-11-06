// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMiscellaneous.h
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

#include "IApplicationTest.h"

//! Collection of functional tests for miscellaneous issues.

class TestMiscellaneous : public IApplicationTest
{
public:
    TestMiscellaneous();
    virtual ~TestMiscellaneous(){}

    virtual void execute();

    //! form factor as a function of qx,qy,qz
    void test_FormFactor();

    //! Re, Im or Amp, phase of form factors as functions of qx,qy,qz
    void test_FormFactor1();

    //! opengl mesocrystal drawing
    void test_DrawMesocrystal();

    //! test of fast sin function approximation
    void test_FastSin();

    //! test kvector container
    void test_KVectorContainer();

    //! test of OutputData export to 2D array
    void test_OutputDataTo2DArray();

    //! testing of loggin system
    void test_LogSystem();

    //! testing print visitor
    void test_PrintVisitor();

    //! testing specific sample geometries (for debugging purposes)
    void test_SampleGeometry();

    //! testing hierarchical visitor
    void test_FunctionalTestRegistry();

};

#endif // TESTMISCELLANEOUS_H


