#ifndef TESTDIFFUSEREFLECTION_H
#define TESTDIFFUSEREFLECTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestDiffuseReflection.h
//! @brief  Test of diffusse (incoherent) reflection from rough multilayer in DWBA.
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "IFunctionalTest.h"

class MultiLayer;


//- -------------------------------------------------------------------
//! @class TestDiffuseReflection
//! @brief Test diffuse (off-specular) reflection from multilayer
//- -------------------------------------------------------------------
class TestDiffuseReflection : public IFunctionalTest
{
public:
    TestDiffuseReflection();

    void execute();

    void draw();

private:
    MultiLayer *m_sample; //!< pointer to multilayer sample
};


#endif // TESTDIFFUSESCATTERING_H
