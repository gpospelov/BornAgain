// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.h
//! @brief     Defines class IFunctionalTest.
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

#include "WinDllMacros.h"
#include <map>
#include <string>

//! @class IFunctionalTest
//! @ingroup standard_samples
//! @brief Basic class for all functional tests

class BA_CORE_API_ IFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED, FAILED_DIFF, FAILED_NOREF};

    IFunctionalTest();
    IFunctionalTest(const std::string &name, const std::string &description);
    virtual ~IFunctionalTest() {}

    virtual void runTest() = 0;
    virtual int analyseResults() = 0;

    std::string getName() const;
    void setName(const std::string &name);

    std::string getDescription() const;
    void setDescription(const std::string &description);

    ETestResult getTestResult() const;
    std::string getTestResultString() const;

    std::string getFormattedInfoString() const;

    friend std::ostream &operator<<(std::ostream &ostr, const IFunctionalTest &m)
    {
        m.printResults(ostr);
        return ostr;
    }

protected:
    virtual void printResults(std::ostream &ostr) const;

    std::string m_name;
    std::string m_description;
    ETestResult m_result;
    static std::map<ETestResult, std::string> m_result_to_string;
};


#endif
