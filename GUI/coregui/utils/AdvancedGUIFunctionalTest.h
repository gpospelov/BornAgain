#ifndef ADVANCEDGUIFUNCTIONALTEST_H
#define ADVANCEDGUIFUNCTIONALTEST_H

#include "WinDllMacros.h"
#include "AdvancedFunctionalTest.h"
#include <string>


class BA_CORE_API_ AdvancedGUIFunctionalTest : public IAdvancedFunctionalTest
{
public:

    AdvancedGUIFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *simulation, OutputData<double> *reference, double threshold);
    ~AdvancedGUIFunctionalTest();

    void runTest();
    int analyseResults();

    const OutputData<double>* getOutputData() const;

    double getDifference() const { return m_difference;}

    void printResults(std::ostream &ostr) const;

private:
    GISASSimulation *m_simulation;
    OutputData<double> *m_reference;
    double m_threshold;
    double m_difference;
};


BA_CORE_API_ int ADVANCED_GUI_FUNCTIONAL_TEST(const std::string &test_name);


#endif

