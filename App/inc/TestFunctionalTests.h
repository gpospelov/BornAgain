// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFunctionalTests.h
//! @brief     Defines class TestFunctionalTests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFUNCTIONALTESTS_H
#define TESTFUNCTIONALTESTS_H


#include "IApplicationTest.h"
#include "FunctionalTestRegistry.h"
#include <string>
#include <vector>

//! Plot results of given functional test

class TestFunctionalTests : public IApplicationTest
{
public:
    TestFunctionalTests() {}
    virtual ~TestFunctionalTests() {}

    virtual void execute();

private:
    //! read names of functional tests from command line and check if they are Ok
    bool readTestNames();

    FunctionalTestRegistry m_testRegistry;
    std::vector<std::string> m_testNames;
};


#endif // TESTFUNCTIONALTESTS_H


