// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalMultiTest.h
//! @brief     Defines class FunctionalMultiTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ADVANCEDFUNCTIONALTEST_H
#define ADVANCEDFUNCTIONALTEST_H

#include "IFunctionalTest.h"
#include <vector>

class FunctionalTestComponentService;

//! @class FunctionalMultiTest
//! @ingroup standard_samples
//! @brief Functional multi test constructs the collection of standard functional
//! tests using component service, runs them one-by-one, and then reports results in a single table.

class BA_CORE_API_ FunctionalMultiTest : public IFunctionalTest
{
public:
    FunctionalMultiTest(const std::string &name, const std::string &description,
                        FunctionalTestComponentService *service);
    ~FunctionalMultiTest();

    void runTest();
    int analyseResults();

    void printResults(std::ostream &ostr) const;

private:
    void saveReferenceDataForFailedTests();

    FunctionalTestComponentService *m_componentService;
    std::vector<IFunctionalTest *> m_tests;
    std::map<const IFunctionalTest *, std::string > m_test_to_reference_fname;
};

#endif
