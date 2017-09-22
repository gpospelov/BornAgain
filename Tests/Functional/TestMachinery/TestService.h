// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestService.h
//! @brief     Defines class TestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTSERVICE_H
#define TESTSERVICE_H

#include <string>
#include <memory>
class IFunctionalTest;
class GISASSimulation;

//! @class TestServiceBase
//! @ingroup standard_samples
//! @brief Main class to run standard functional test from standalone executable.

class TestServiceBase
{
public:
    virtual ~TestServiceBase() = default;
    bool execute(int argc, char** argv);

private:
    virtual IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                        const GISASSimulation& simulation,
                                        double threshold) = 0;
};


//! @class TestService
//! @ingroup standard_samples
//! @brief Extends main class to run standard functional test from standalone executable.
//! Concrete test type is templated.

template<typename T>
class TestService : public TestServiceBase
{

private:
    virtual IFunctionalTest* createTest(const std::string& name, const std::string& description,
                                        const GISASSimulation&  simulation,
                                        double threshold)
    {
        return createStandardTest(name, description, std::move(simulation), threshold);
    }

    T* createStandardTest(const std::string& name, const std::string& description,
                          const GISASSimulation&  simulation, double threshold) {
        return new T(name, description, simulation, threshold);
    }
};

#endif // TESTSERVICE_H
