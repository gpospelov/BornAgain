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
#include "ISingleton.h"
#include "IFactory.h"
#include "IFunctionalTest.h"


class TBenchmark;

class TestFactory : public ISingleton<TestFactory>, public IFactory<std::string, IFunctionalTest>
//before it was template class ISingleton<IFactory<std::string, IFunctionalTest> >;
{
public:
    TestFactory();
    virtual ~TestFactory();

    //! execute specified test
    void execute(std::string name);

    //! profile specified test
    void profile(std::string name);

    //! execute all registered tests
    void execute_all();

    //! print names of registered tests
    void print_testnames();

    //! print benchmark summary
    void print_benchmarks();

    //! return vector of registere test names
    std::vector<std::string > get_testnames();

private:
    TBenchmark *m_benchmark;
};

#endif // TESTFACTORY_H
