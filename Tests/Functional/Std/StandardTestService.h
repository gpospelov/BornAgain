// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/StandardTestService.h
//! @brief     Defines class StandardTestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTSERVICE_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTSERVICE_H

#include "Wrap/WinDllMacros.h"
#include <string>
class IStandardTest;
class Simulation;

//! Main class to run standard functional test from standalone executable.
//! @ingroup standard_samples

class BA_CORE_API_ StandardTestServiceBase
{
public:
    virtual ~StandardTestServiceBase() = default;
    bool execute(int argc, char** argv);

private:
    virtual IStandardTest* createStdTest(const std::string& name, const Simulation& simulation,
                                         double threshold) = 0;
};

//! @brief
//! Extends main class to run standard functional test from standalone executable.
//! Concrete test type is templated.
//! @ingroup standard_samples

template <typename T> class StandardTestService : public StandardTestServiceBase
{

private:
    IStandardTest* createStdTest(const std::string& name, const Simulation& simulation,
                                 double threshold) override
    {
        return new T(name, simulation, threshold);
    }
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTSERVICE_H
