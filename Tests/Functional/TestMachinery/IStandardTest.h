// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.h
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ISTANDARDTEST_H
#define ISTANDARDTEST_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"
#include <memory>
#include <string>

class Simulation;
class GISASSimulation;

//! Base class for tests that compare results with reference data.
//! @ingroup standard_samples

class BA_CORE_API_ IStandardTest : public IFunctionalTest
{
public:
    IStandardTest(const std::string& name, const std::string& description,
                  const Simulation& simulation, double threshold);

    ~IStandardTest();

    bool runTest() = 0;

protected:
    std::unique_ptr<Simulation> m_reference_simulation;
    double m_threshold;
};

#endif // ISTANDARDTEST_H
