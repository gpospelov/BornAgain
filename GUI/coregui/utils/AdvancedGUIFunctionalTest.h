#ifndef ADVANCEDGUIFUNCTIONALTEST_H
#define ADVANCEDGUIFUNCTIONALTEST_H

#include "WinDllMacros.h"
#include "IFunctionalTest.h"
#include "OutputData.h"
#include <string>

class GISASSimulation;

class BA_CORE_API_ AdvancedGUIFunctionalTest : public IFunctionalTest
{
public:

    AdvancedGUIFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *reference_simulation, double threshold);
    ~AdvancedGUIFunctionalTest();

    void runTest();
    int analyseResults();

    const OutputData<double>* getOutputData() const;

    double getDifference() const { return m_difference;}

    void printResults(std::ostream &ostr) const;

private:
    void createDomainSimulation();

    GISASSimulation *m_reference_simulation;
    GISASSimulation *m_domain_simulation;
    double m_threshold;
    double m_difference;
};


BA_CORE_API_ int ADVANCED_GUI_FUNCTIONAL_TEST(const std::string &test_name);


#endif

