#ifndef FUNCTIONALTESTFACTORY_H
#define FUNCTIONALTESTFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FunctionalTestFactory.h
//! @brief  Definition of factory class to hold collection of functional tests
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <string>
#include <map>
#include "ISingleton.h"
#include "IFactory.h"
#include "IFunctionalTest.h"


class TBenchmark;
class ProgramOptions;

class FunctionalTestFactory : public ISingleton<FunctionalTestFactory>, public IFactory<std::string, IFunctionalTest>
{
public:
    FunctionalTestFactory();
    virtual ~FunctionalTestFactory();

    //! execute specified test
    static void execute(std::string name, ProgramOptions *p_options) { instance().this_execute(name, p_options); }

    //! profile specified test
    static void profile(std::string name, ProgramOptions *p_options)  { instance().this_profile(name, p_options); }

    //! execute all registered tests
    static void execute_all(ProgramOptions *p_options)  { instance().this_execute_all(p_options); }

    //! print names of registered tests
    static void print_testnames() { instance().this_print_testnames(); }

    //! print benchmark summary
    static void print_benchmarks() { instance().this_print_benchmarks(); }

    static iterator begin() { return instance().m_descriptions.begin(); }
    static iterator end() { return instance().m_descriptions.end(); }

private:
    void this_execute(std::string name, ProgramOptions *p_options);
    void this_profile(std::string name, ProgramOptions *p_options);
    void this_execute_all(ProgramOptions *p_options);
    void this_print_testnames();
    void this_print_benchmarks();

    TBenchmark *m_benchmark;
};

#endif // FUNCTIONALTESTFACTORY_H
