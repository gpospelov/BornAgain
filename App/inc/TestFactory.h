#ifndef TESTFACTORY_H
#define TESTFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFactory.h
//! @brief  Definition of factory class to hold collection of functional tests
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <string>
#include <map>
#include "ISingleton.h"
#include "IFactory.h"
#include "IFunctionalTest.h"


class TestFactory : public ISingleton<TestFactory>, public IFactory<std::string, IFunctionalTest>
{
public:
    TestFactory();
    virtual ~TestFactory() {}

    //! execute specified test
    void execute(std::string name);

    //! execute all registered tests
    void execute_all();

};

#endif // TESTFACTORY_H
