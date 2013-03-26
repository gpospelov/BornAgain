// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FunctionalTestFactory.h 
//! @brief     Defines class FunctionalTestFactory.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTFACTORY_H
#define FUNCTIONALTESTFACTORY_H

#include <string>
#include <map>
#include "ISingleton.h"
#include "IFactory.h"
#include "IFunctionalTest.h"

class TBenchmark;
class ProgramOptions;

class FunctionalTestFactory : public ISingleton<FunctionalTestFactory>,
                              public IFactory<std::string, IFunctionalTest>
{
 public:
    FunctionalTestFactory();
    virtual ~FunctionalTestFactory();

    //! execute specified test
    static void execute(std::string name, ProgramOptions *p_options)
    { instance().this_execute(name, p_options); }

    //! profile specified test
    static void profile(std::string name, ProgramOptions *p_options)
    { instance().this_profile(name, p_options); }

    //! execute all registered tests
    static void execute_all(ProgramOptions *p_options)
    { instance().this_execute_all(p_options); }

    //! print names of registered tests
    static void print_testnames()
    { instance().this_print_testnames(); }

    //! print benchmark summary
    static void print_benchmarks()
    { instance().this_print_benchmarks(); }

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
