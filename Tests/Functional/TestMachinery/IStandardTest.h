// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.h
//! @brief     Defines class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISTANDARDTEST_H
#define ISTANDARDTEST_H

#include "INamed.h"

class GISASSimulation;
class IFunctionalTest;
class SimulationInfo;
class IParameterized;

//! @class IStandardTest
//! @brief Base class for Core/PyCore/GUI tests that involve standard simulations.

//! For Foo in {Core, PyCore, GUI}, the functional test mechanism is as follows:
//!
//! FooStandardTest is the executable obtained from
//!   main(argv,argc) in FooStandardTest.cpp,
//! which runs
//!   FooStandardTest().execute(argv,argc),
//! which is inherited from here. This function,
//!   IStandardTest::execute(argv,argc)
//! uses argv[1] to retrieve a set of parameters from StandardSimulationsRegistry.
//! Then it bifurcates into
//!   IStandardTest::execute_onetest(argv,argc) or
//!   IStandardTest::execute_subtests(argv,argc)
//! which will call
//!   IFunctionalTest::getTest(),
//! which is the only nontrivial member of FooStandardTest, implemented in FooStandardTest.cpp.
//! The return value
//!   test = new FooTest( <parameters> )
//! is provided by FooTest.cpp.
//! The arguments in this constructor are callback functions provided by IStandardTest;
//! they contain information gathered from StandardSimulationsRegistry, and possibly from
//! a subtest registry.
//! Finally, IStandardTest::execute_... will call
//!   test->runTest()        // implemented in FooTest
//!   test->analyseResults() // implemented in FooTest
//!   test->getTestResult()  // implemented in IFunctionalTest

class IStandardTest : public INamed
{
public:
    IStandardTest(const std::string& name) : INamed(name) {}
    virtual ~IStandardTest() {}

    bool execute(int argc, char** argv);

    virtual IFunctionalTest* getTest() const = 0; //!< overloaded in (Core|Py|GUI)Suite.cpp

protected:
    virtual GISASSimulation* getSimulation() const;
    std::string getTestDescription() const;
    virtual double getTestThreshold() const;

private:
    const SimulationInfo* m_info;
    const IParameterized* m_subtest_item;

    bool execute_onetest();
    bool execute_subtests();
};

#endif // ISTANDARDTEST_H
