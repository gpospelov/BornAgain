// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IReferencedTest.h
//! @brief     Defines pure virtual base class IReferencedTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IREFERENCEDTEST_H
#define IREFERENCEDTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include <map>

//! @class IReferencedTest
//! @ingroup standard_samples
//! @brief Base class for tests that compare results with reference data.

class IReferencedTest : public IFunctionalTest
{
public:
    IReferencedTest();
    IReferencedTest(const std::string& name, const std::string& description, double threshold)
        : IFunctionalTest(name, description), m_threshold(threshold) {}
    virtual ~IReferencedTest() {}

    virtual void runTest() = 0;

protected:
    double m_threshold;

    ETestResult compareIntensityMaps(
        const OutputData<double>& dat, const OutputData<double>& ref) const;
};

#endif // IREFERENCEDTEST_H
