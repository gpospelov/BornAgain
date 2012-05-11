#ifndef TESTDIFFUSESCATTERING_H
#define TESTDIFFUSESCATTERING_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestDiffuseScattering.h
//! @brief  Test of diffusse (incoherent) scattering from rough multilayer in DWBA.
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "IFunctionalTest.h"
#include "MultiLayer.h"

class TestDiffuseScattering : public IFunctionalTest
{
public:
    TestDiffuseScattering();

    void execute();

    void test1(const MultiLayer &sample);
    double test1_a(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf);

    static bool registered;
};


#endif // TESTDIFFUSESCATTERING_H
