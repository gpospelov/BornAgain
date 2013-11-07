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

class FunctionalTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    FunctionalTestFactory();
    virtual ~FunctionalTestFactory();

    //! execute specified test
    void execute(std::string name, ProgramOptions *p_options);

    //! profile specified test
    void profile(std::string name, ProgramOptions *p_options);

    //! execute all registered tests
    void execute_all(ProgramOptions *p_options);

    //! Prints names of registered tests
    void print_testnames();

    //! Prints benchmark summary
    void print_benchmarks();

    iterator begin() { return m_descriptions.begin(); }
    iterator end() { return m_descriptions.end(); }

private:
    TBenchmark *m_benchmark;
};

void RegisterFunctionalTests(FunctionalTestFactory *p_test_factory);

#endif // FUNCTIONALTESTFACTORY_H


