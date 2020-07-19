// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/IStandardTest.h
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_ISTANDARDTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_ISTANDARDTEST_H

#include "Wrap/WinDllMacros.h"
#include <memory>
#include <string>

class Simulation;

//! Base class for tests that compare results with reference data.
//! @ingroup standard_samples

class BA_CORE_API_ IStandardTest
{
public:
    IStandardTest(const std::string& name, const Simulation& simulation, double threshold);

    ~IStandardTest();

    virtual bool runTest() = 0;

protected:
    std::string m_name;
    std::unique_ptr<Simulation> m_reference_simulation;
    double m_threshold;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_ISTANDARDTEST_H
