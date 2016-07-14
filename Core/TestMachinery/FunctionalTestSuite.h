// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/FunctionalTestSuite.h
//! @brief     Declares class FunctionalTestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTSUITE_H
#define FUNCTIONALTESTSUITE_H


#include "ISampleBuilder.h"

//! @class FunctionalTestSuite
//! @brief To execute one functional test of given name.

//! Used in functional tests (Core|Py|GUI)Suite, where it is subclassed
//! as a singleton, and called through instance().execute(argc, argv).

//! When processing execute, dependent classes will call back getTest().
//! Certain tests have subtests; they will call back getFormFactor() etc.

class BA_CORE_API_ FunctionalTestSuite : public INamed
{
public:
    FunctionalTestSuite() {}
    virtual ~FunctionalTestSuite() {}

    int execute(int argc, char** argv);

    virtual class IFunctionalTest* getTest() const = 0; //!< overloaded in (Core|Py|GUI)Suite.cpp

protected:
    virtual class GISASSimulation* getSimulation() const;
    std::string getTestName() const { return m_test_name; }
    std::string getTestDescription() const;
    double getTestThreshold() const;

private:
    const class FunctionalTestInfo* m_info;
    std::string m_test_name;
    const class IParameterized* m_subtest_item;

    int execute_onetest();
    int execute_subtests();
};

#endif // FUNCTIONALTESTSUITE_H
