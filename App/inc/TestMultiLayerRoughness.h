// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMultiLayerRoughness.h
//! @brief     Defines class TestMultiLayerRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMULTILAYERROUGHNESS_H
#define TESTMULTILAYERROUGHNESS_H

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"

//! Tests of specular and diffuse reflection from rough multilayer in DWBA.

//! This is replacement for TestDiffuseReflection test.
//!
class TestMultiLayerRoughness : public IApplicationTest
{
public:
    TestMultiLayerRoughness() {}
    virtual ~TestMultiLayerRoughness(){}

    virtual void execute();

};

#endif // TESTMULTILAYERROUGHNESS_H


