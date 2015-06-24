
#ifndef OBSOLETEGUIFUNCTIONALTEST_H
#define OBSOLETEGUIFUNCTIONALTEST_H

#include <string>
#include "WinDllMacros.h"
#include "OutputData.h"
class GISASSimulation;


class BA_CORE_API_ ObsoleteGUIFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED};
    ObsoleteGUIFunctionalTest(const std::string &name);
    virtual ~ObsoleteGUIFunctionalTest();
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
BA_CORE_API_ int OBSOLETE_GUI_FUNCTIONAL_TEST(const std::string &name);

#endif


