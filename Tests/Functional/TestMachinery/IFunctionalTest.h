// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IFunctionalTest.h
//! @brief     Defines IFunctionalTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H

#include "Wrap/WinDllMacros.h"
#include <map>
#include <string>

//! Base class for all functional tests.
//! @class IFunctionalTest

class BA_CORE_API_ IFunctionalTest
{
public:
    IFunctionalTest() {}
    IFunctionalTest(const std::string& name, const std::string& description)
        : m_name(name), m_description(description)
    {
    }
    virtual ~IFunctionalTest() = default;

    bool execute() { return runTest(); }

    std::string description() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }

    void setName(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }

protected:
    virtual bool runTest() = 0; //!< Returns true when successful

private:
    std::string m_name {""};
    std::string m_description {""};
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H
