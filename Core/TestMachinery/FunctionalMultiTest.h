// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalMultiTest.h
//! @brief     Declares class FunctionalMultiTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALMULTITEST_H
#define FUNCTIONALMULTITEST_H

#include "IFunctionalTest.h"
#include <vector>

class FunctionalTestComponentService;

//! @class FunctionalMultiTest
//! @ingroup standard_samples
//! @brief Functional multi test constructs the collection of standard functional tests
//! using component service, runs them one-by-one, and then reports results in a single table.

class BA_CORE_API_ FunctionalMultiTest : public IFunctionalTest
{
public:
    FunctionalMultiTest(const std::string &name, FunctionalTestComponentService& service);
    virtual ~FunctionalMultiTest();

    virtual void runTest();
    virtual int analyseResults();
    virtual void printResults(std::ostream &ostr) const;

private:
    FunctionalTestComponentService& m_service;
    std::vector<IFunctionalTest*> m_tests;
};

#endif
