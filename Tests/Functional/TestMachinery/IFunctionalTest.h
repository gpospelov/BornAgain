// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IFunctionalTest.h
//! @brief     Declares pure virtual base class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFUNCTIONALTEST_H
#define IFUNCTIONALTEST_H

#include "INamed.h" // inheriting from
#include <map>

//! @class IFunctionalTest
//! @ingroup standard_samples
//! @brief Base class for all functional tests.

class IFunctionalTest : public INamed
{
public:
    enum ETestResult { SUCCESS, FAILED, FAILED_DIFF, FAILED_NOREF};

    IFunctionalTest();
    IFunctionalTest(const std::string& name, const std::string& description);
    virtual ~IFunctionalTest() {}

    virtual void runTest() = 0;

    std::string getDescription() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }

    ETestResult getTestResult() const { return m_result; }
    std::string getTestResultString() const;

protected:
    std::string m_description;
    double m_threshold;
    ETestResult m_result;
    static std::map<ETestResult, std::string> m_result_to_string;
};

#endif // IFUNCTIONALTEST_H
