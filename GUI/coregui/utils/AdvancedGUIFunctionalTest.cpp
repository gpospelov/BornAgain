#include "AdvancedGUIFunctionalTest.h"
#include "SimulationRegistry.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "Instrument.h"
#include "DomainObjectBuilder.h"
#include "ParameterizedItem.h"
#include "IntensityDataFunctions.h"
#include "DomainSimulationBuilder.h"

#include "IFunctionalTest.h"
#include "GUIFunctionalTestService.h"
#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"

#include <boost/scoped_ptr.hpp>
#include <QDebug>


namespace {

const size_t width_name = 20;
const size_t width_description = 40;
const size_t width_result = 18;

}


AdvancedGUIFunctionalTest::AdvancedGUIFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *reference_simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
{

}

AdvancedGUIFunctionalTest::~AdvancedGUIFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void AdvancedGUIFunctionalTest::runTest()
{
    if(!m_reference_simulation) {
        throw NullPointerException("AdvancedGUIFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }

    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}

int AdvancedGUIFunctionalTest::analyseResults()
{
    boost::scoped_ptr<OutputData<double> > P_domain_data(m_domain_simulation->getIntensityData());
    boost::scoped_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getIntensityData());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    return m_result;
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


//! returns new simulation from
void AdvancedGUIFunctionalTest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());

    // initializing necessary GUI
    boost::scoped_ptr<SampleModel> P_sampleModel(new SampleModel());
    boost::scoped_ptr<InstrumentModel> P_instrumentModel(new InstrumentModel());
    boost::scoped_ptr<MaterialModel> P_materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> P_materialEditor(new MaterialEditor(P_materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(P_sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(P_instrumentModel.get(), *m_reference_simulation);

    m_domain_simulation
        = DomainSimulationBuilder::getSimulation(P_sampleModel.get(), P_instrumentModel.get());
}



// -------------------------------------------------------------------------------------------------


int ADVANCED_GUI_FUNCTIONAL_TEST(const std::string &test_name)
{
    FunctionalTestRegistry catalogue;
    if(!catalogue.isValidTest(test_name)) {
        std::cout << "FUNCTIONAL_TEST() -> Non existing test with name '" << test_name << "', "
                  << "use argument from the list of defined tests" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    FunctionalTestInfo info = catalogue.getTestInfo(test_name);

    GUIFunctionalTestService *service = new GUIFunctionalTestService(info);
    boost::scoped_ptr<IFunctionalTest> test(new FunctionalMultiTest(test_name, info.m_test_description, service));
    test->runTest();
    return test->analyseResults();
}
