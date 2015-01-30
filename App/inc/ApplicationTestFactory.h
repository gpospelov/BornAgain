// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FunctionalTestFactory.h
//! @brief     Defines class FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef APPLICATIONTESTFACTORY_H
#define APPLICATIONTESTFACTORY_H

#include <string>
#include <map>
#include "ISingleton.h"
#include "IFactory.h"
#include "IApplicationTest.h"

class TBenchmark;
class ProgramOptions;

class ApplicationTestFactory : public IFactory<std::string, IApplicationTest>
{
public:
    ApplicationTestFactory();
    virtual ~ApplicationTestFactory();

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

private:
    TBenchmark *m_benchmark;
};

void RegisterApplicationTests(ApplicationTestFactory *p_test_factory);

#endif // APPLICATIONTESTFACTORY_H



