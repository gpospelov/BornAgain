// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.h
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISTANDARDTEST_H
#define ISTANDARDTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include <map>
#include <string>

//! Base class for tests that compare results with reference data.
//! @ingroup standard_samples

class BA_CORE_API_ IStandardTest : public IFunctionalTest
{
public:
    IStandardTest();
    IStandardTest(const std::string& name, const std::string& description, double threshold)
        : IFunctionalTest(name, description), m_threshold(threshold) {}
    virtual ~IStandardTest() {}

    bool runTest() =0;

protected:
    double m_threshold;

    static bool runPython(const std::string& py_command);
};

#endif // ISTANDARDTEST_H
