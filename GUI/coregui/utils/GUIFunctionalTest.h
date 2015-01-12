#ifndef GUIFUNCTIONALTEST_H
#define GUIFUNCTIONALTEST_H

#include <string>
#include "WinDllMacros.h"
#include "OutputData.h"
class Simulation;

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
    Simulation *m_reference_simulation;
    Simulation *m_domain_simulation;
};

//! run functional tests with given name
BA_CORE_API_ int GUI_FUNCTIONAL_TEST(const std::string &name);


#endif


