#include "FunctionalTestComponentService.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "TestFormFactorsRegistry.h"
#include "Exceptions.h"
#include "IFormFactor.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"
#include <iostream>


FunctionalTestComponentService::FunctionalTestComponentService(const AdvancedFunctionalTestInfo &info)
    : m_testInfo(info)
    , m_form_factor(0)
    , m_simulation(0)
    , m_ff_registry(0)
    , m_current_component(0)
    , m_number_of_components(1)
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
    if(m_ff_registry) {
        delete m_form_factor;
        m_form_factor = m_ff_registry->createItem(m_component_names[current_component]);
    }

}

std::string FunctionalTestComponentService::getReferenceFileName()
{
    std::string result("ref_");
    result += m_testInfo.m_test_name;
    if(m_component_names.size() > m_current_component)
        result += std::string("_")+m_component_names[m_current_component];
    result += std::string(".int");
    return result;
}

double FunctionalTestComponentService::getThreshold() const
{
    return m_testInfo.m_threshold;
}

AdvancedFunctionalTestInfo FunctionalTestComponentService::getTestInfo() const
{
    return m_testInfo;
}

void FunctionalTestComponentService::init_registry(const std::string &registry_name)
{
    std::cout << "FunctionalTestComponentService::init_registry() ->" << registry_name << std::endl;
    if(registry_name == "FormFactorsRegistry") {
        m_ff_registry = new TestFormFactorsRegistry;
        m_component_names.clear();
        for(TestFormFactorsRegistry::iterator it = m_ff_registry->begin(); it!= m_ff_registry->end(); ++it) {
            m_component_names.push_back(it->first);
        }
        m_number_of_components = m_component_names.size();
    } else {
        throw RuntimeErrorException("FunctionalTestComponentService::init_factory -> Error. "
                                    "Unknown factory '"+registry_name+"'.");
    }
}
