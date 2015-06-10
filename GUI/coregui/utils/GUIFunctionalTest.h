// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFunctionalTest.h
//! @brief     Defines class GUIFunctionalTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIFUNCTIONALTEST_H
#define GUIFUNCTIONALTEST_H

#include <string>
#include "WinDllMacros.h"
#include "OutputData.h"
class GISASSimulation;

//! Simple test for converting domain simulation into GUI and back, and then
//! comparing results of two simulations in domain space
class BA_CORE_API_ GUIFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED};
    GUIFunctionalTest(const std::string &name);
    virtual ~GUIFunctionalTest();
    virtual void runTest();
    virtual int analyseResults();

private:
    void createDomainSimulation();

    std::string m_name;
    double m_threshold;
    GISASSimulation *m_reference_simulation;
    GISASSimulation *m_domain_simulation;
};

//! run functional tests with given name
BA_CORE_API_ int GUI_FUNCTIONAL_TEST(const std::string &name);


#endif


