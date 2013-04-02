// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMultiLayerRoughness.h
//! @brief     Defines class TestMultiLayerRoughness.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMULTILAYERROUGHNESS_H
#define TESTMULTILAYERROUGHNESS_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

//! Tests of specular and diffuse reflection from rough multilayer in DWBA.

//! This is replacement for TestDiffuseReflection test.
//!
class TestMultiLayerRoughness : public IFunctionalTest
{
 public:
    TestMultiLayerRoughness() {}
    virtual ~TestMultiLayerRoughness(){}

    virtual void execute();

};

#endif // TESTMULTILAYERROUGHNESS_H


