#include "FunctionalTestComponentService.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "TestFormFactorsRegistry.h"
#include "Exceptions.h"
#include "IFormFactor.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTest.h"
#include <iostream>


namespace {
const std::string FormFactorsRegistryName = "FormFactorsRegistry";
const std::string NoneRegistryName = "None";
const std::string DefaultComponentName = "Default";
}

FunctionalTestComponentService::FunctionalTestComponentService(const FunctionalTestInfo &info)
    : m_testInfo(info)
    , m_form_factor(0)
    , m_simulation(0)
    , m_ff_registry(0)
    , m_current_component(0)
{
    SimulationRegistry sim_registry;
    m_simulation = sim_registry.createSimulation(m_testInfo.m_simulation_name);

    SampleBuilderFactory sample_factory;
    m_sample_builder = sample_factory.createBuilder(m_testInfo.m_sample_builder_name);

    init_registry(m_testInfo.m_component_registry_name);
}

FunctionalTestComponentService::~FunctionalTestComponentService()
{
    delete m_form_factor;
    delete m_simulation;
    delete m_ff_registry;
}

IFormFactor *FunctionalTestComponentService::getFormFactor()
{
    return m_form_factor;
}

GISASSimulation *FunctionalTestComponentService::getSimulation()
{
    m_simulation->setSampleBuilder(getSampleBuilder());
    return m_simulation->clone();
}

OutputData<double> *FunctionalTestComponentService::getReferenceData()
{
    OutputData<double> *result(0);
    std::string filename = Utils::FileSystem::GetReferenceDataDir() + getReferenceFileName();

    try {
        result = IntensityDataIOFactory::readIntensityData(filename);
    } catch(const std::exception &ex) {
        std::cout << "FunctionalTestComponentService::getReferenceData() -> Exception caught."
                  << ex.what() << std::endl;
    }

    return result;
}

SampleBuilder_t FunctionalTestComponentService::getSampleBuilder()
{
    m_sample_builder->init_from(this);
    return m_sample_builder;
}

void FunctionalTestComponentService::setComponent(size_t current_component)
{
    if(current_component >= getNumberOfComponents()) {
        throw OutOfBoundsException("FunctionalTestComponentService::setComponent() -> Error. Out of bounds");
    }
    m_current_component = current_component;
    if(m_ff_registry) {
        delete m_form_factor;
        m_form_factor = m_ff_registry->createItem(m_component_names[current_component]);
    }

}

std::string FunctionalTestComponentService::getReferenceFileName()
{
    std::string result("ref_");
    result += m_testInfo.m_test_name;
    if(m_component_names[m_current_component] != DefaultComponentName)
        result += std::string("_")+m_component_names[m_current_component];
    result += std::string(".int.gz");
    return result;
}

double FunctionalTestComponentService::getThreshold() const
{
    return m_testInfo.m_threshold;
}

FunctionalTestInfo FunctionalTestComponentService::getTestInfo() const
{
    return m_testInfo;
}

std::string FunctionalTestComponentService::getCurrentComponentName() const
{
    return m_component_names[m_current_component];
}

IFunctionalTest *FunctionalTestComponentService::getFunctionalTest()
{
    CoreFunctionalTest *result = new CoreFunctionalTest(m_testInfo.m_test_name, m_testInfo.m_test_description, getSimulation(), getReferenceData(), getThreshold());
    return result;
}

void FunctionalTestComponentService::init_registry(const std::string &registry_name)
{
    m_component_names.clear();
    m_current_component = 0;

    std::cout << "FunctionalTestComponentService::init_registry() ->" << registry_name << std::endl;
    if(registry_name == NoneRegistryName) {
        m_component_names.push_back(DefaultComponentName);

    }else if(registry_name == FormFactorsRegistryName) {
        m_ff_registry = new TestFormFactorsRegistry;
        for(TestFormFactorsRegistry::iterator it = m_ff_registry->begin(); it!= m_ff_registry->end(); ++it) {
            m_component_names.push_back(it->first);
        }

    } else {
        throw RuntimeErrorException("FunctionalTestComponentService::init_factory -> Error. "
                                    "Unknown factory '"+registry_name+"'.");
    }

}

