// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.h
//! @brief     Defines class IFunctionalTest.
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

#include "GISASSimulation.h"
#include <string>
#include <map>

//! @class IAdvancedFunctionalTest
//! @ingroup standard_samples
//! @brief Interface to the functional tests

class BA_CORE_API_ IAdvancedFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED, FAILED_DIFF, FAILED_NOREF};

    IAdvancedFunctionalTest(const std::string &name, const std::string &description);
    virtual ~IAdvancedFunctionalTest() {}

    virtual void runTest() = 0;
    virtual int analyseResults() = 0;

    std::string getName() const { return m_name; }
    std::string getDescription() const { return m_description; }
    double getDifference() const { return m_difference;}

    ETestResult getTestResult() const { return m_result; }
    std::string getTestResultString() const { return m_result_to_string[m_result]; }

    virtual void printResults(std::ostream &ostr);

protected:
    std::string m_name;
    std::string m_description;
    double m_difference;
    ETestResult m_result;

    static std::map<ETestResult, std::string> m_result_to_string;
};


//! @class AdvancedFunctionalTest
//! @ingroup standard_samples
//! @brief Basic functional test

class BA_CORE_API_ AdvancedFunctionalTest : public IAdvancedFunctionalTest
{
public:

    AdvancedFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *simulation, OutputData<double> *reference, double threshold);
    ~AdvancedFunctionalTest();

    void runTest();
    int analyseResults();

    const OutputData<double>* getOutputData() const;

private:
    GISASSimulation *m_simulation;
    OutputData<double> *m_reference;
    double m_threshold;
};

//! @class AdvancedFunctionalMultiTest
//! @ingroup standard_samples
//! @brief Functional multi test constructs the collection of standard functional tests using component service,
//! runs them one-by-one, and then reports results in single table.

class FunctionalTestComponentService;

class BA_CORE_API_ AdvancedFunctionalMultiTest : public IAdvancedFunctionalTest
{
public:
    AdvancedFunctionalMultiTest(const std::string &name, const std::string &description, FunctionalTestComponentService *service);
    ~AdvancedFunctionalMultiTest();

    void runTest();
    int analyseResults();

    void printResults(std::ostream &ostr);

private:
    void saveReferenceDataForFailedTests();

    FunctionalTestComponentService *m_componentService;
    std::vector<AdvancedFunctionalTest *> m_tests;
    std::map<AdvancedFunctionalTest *, std::string > m_test_to_reference_fname;
};

#endif
