#include "AdvancedGUIFunctionalTest.h"
#include "AdvancedFunctionalTestRegistry.h"
#include "FunctionalTestComponentService.h"
#include "AdvancedFunctionalTest.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "Utils.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>

namespace {

const size_t width_name = 20;
const size_t width_description = 40;
const size_t width_result = 18;

}


AdvancedGUIFunctionalTest::AdvancedGUIFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *simulation, OutputData<double> *reference, double threshold)
    : IAdvancedFunctionalTest(name, description)
    , m_simulation(simulation)
    , m_reference(reference)
    , m_threshold(threshold)
    , m_difference(0)
{

}

AdvancedGUIFunctionalTest::~AdvancedGUIFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void AdvancedGUIFunctionalTest::runTest()
{
    if(!m_simulation) {
        throw NullPointerException("AdvancedFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }
    m_simulation->runSimulation();
}

int AdvancedGUIFunctionalTest::analyseResults()
{
    if(!m_reference)  {
        m_result = FAILED_NOREF;
    } else {
        m_difference = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(), *m_reference);
        m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    }
    return m_result;
}

const OutputData<double> *AdvancedGUIFunctionalTest::getOutputData() const
{
    if(m_simulation) {
        return m_simulation->getOutputData();
    }
    return 0;
}

void AdvancedGUIFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr <<  Utils::AdjustStringLength(getName(), width_name);
    ostr <<  Utils::AdjustStringLength(getDescription(), width_description);
    ostr << Utils::AdjustStringLength(getTestResultString(), width_result);
    if(getTestResult() == SUCCESS || getTestResult() == FAILED_DIFF)
        ostr << getDifference();
    ostr << "\n";
}


int ADVANCED_GUI_FUNCTIONAL_TEST(const std::string &test_name)
{
    AdvancedFunctionalTestRegistry catalogue;
    if(!catalogue.isValidTest(test_name)) {
        std::cout << "FUNCTIONAL_TEST() -> Non existing test with name '" << test_name << "', "
                  << "use argument from the list of defined tests" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    AdvancedFunctionalTestInfo info = catalogue.getTestInfo(test_name);

    FunctionalTestComponentService *service = new FunctionalTestComponentService(info);
    boost::scoped_ptr<IAdvancedFunctionalTest> test(new AdvancedFunctionalMultiTest(test_name, info.m_test_description, service));
    test->runTest();
    return test->analyseResults();
}
