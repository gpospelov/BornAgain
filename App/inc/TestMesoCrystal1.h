// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMesoCrystal1.h
//! @brief     Defines class TestMesoCrystal1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMESOCRYSTAL1_H_
#define TESTMESOCRYSTAL1_H_

#include "IApplicationTest.h"

//! Simulation of 3D ordered particle assemblies.
//! Test serve for visualization of MesoCrystal1 functional test

class TestMesoCrystal1 : public IApplicationTest
{
public:
    TestMesoCrystal1(){}
    virtual ~TestMesoCrystal1(){}
    virtual void execute();

};

#endif /* TESTMESOCRYSTAL1_H_ */


