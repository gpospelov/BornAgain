#ifndef TESTMULTILAYERROUGHNESS_H
#define TESTMULTILAYERROUGHNESS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMultiLayerRoughness.h
//! @brief  Tests of specular and diffuse reflection from rough multilayer in DWBA.
//! @author Scientific Computing Group at FRM II
//! @date   01.08.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class TestMultiLayerRoughness
//! @brief Tests of specular and diffuse reflection from rough multilayer in DWBA.
//! (this is replacement for TestDiffuseReflection test)
//- -------------------------------------------------------------------
class TestMultiLayerRoughness : public IFunctionalTest
{
public:
    TestMultiLayerRoughness();
    virtual ~TestMultiLayerRoughness(){}

    virtual void execute();

};

#endif // TESTMULTILAYERROUGHNESS_H
