// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentService.cpp
//! @brief     Implements class FunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestComponentService.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "TestComponentsRegistry.h"
#include "Exceptions.h"
#include "IFormFactor.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTest.h"
#include "FTDistributions.h"
#include <iostream>


namespace {
const std::string FormFactorsRegistryName = "FormFactorsRegistry";
const std::string FTDistributions2DName = "FTDistributions2DRegistry";
const std::string NoneRegistryName = "None";
const std::string DefaultComponentName = "Default";
}

FunctionalTestComponentService::FunctionalTestComponentService(const FunctionalTestInfo* info)
    : m_testInfo(info)
    , m_form_factor(0)
    , m_ft_distribution_2d(0)
    , m_ff_registry(0)
    , m_ft2d_registry(0)
    , m_current_component(0)
{
    init_registry(m_testInfo->m_component_registry_name);
}

FunctionalTestComponentService::~FunctionalTestComponentService()
{
    delete m_form_factor;
    delete m_ff_registry;

    delete m_ft_distribution_2d;
    delete m_ft2d_registry;
}

IFormFactor* FunctionalTestComponentService::getFormFactor() const
{
    if(!m_form_factor)
        throw NullPointerException(
            "FunctionalTestComponentService::getFormFactor() -> Error. No form factor defined.");
    return m_form_factor->clone();
}

IFTDistribution2D* FunctionalTestComponentService::getFTDistribution2D() const
{
    if(!m_ft_distribution_2d)
        throw NullPointerException(
            "FunctionalTestComponentService::getFTDistribution2D() -> Error. "
            "No FT distribution defined.");
    return m_ft_distribution_2d->clone();
}


GISASSimulation* FunctionalTestComponentService::getSimulation() const
{
    SimulationRegistry sim_registry;
    GISASSimulation* result = sim_registry.createSimulation(m_testInfo->m_simulation_name);
    result->setSampleBuilder(getSampleBuilder());
    return result;
}

std::shared_ptr<class ISampleBuilder> FunctionalTestComponentService::getSampleBuilder() const
{
    SampleBuilderFactory sample_factory;
    std::shared_ptr<class ISampleBuilder> sample_builder =
        sample_factory.createBuilder(m_testInfo->m_sample_builder_name);
    sample_builder->init_from(this);
    return sample_builder;
}

OutputData<double>* FunctionalTestComponentService::getReferenceData() const
{
    OutputData<double>* result(0);
    std::string filename = Utils::FileSystem::GetReferenceDataDir() + getReferenceFileName();

    try {
        result = IntensityDataIOFactory::readOutputData(filename);
    } catch(const std::exception& ex) {
        std::cout << "FunctionalTestComponentService::getReferenceData() -> Exception caught."
                  << ex.what() << std::endl;
    }

    return result;
}

size_t FunctionalTestComponentService::getNumberOfComponents() const
{
    return m_component_names.size();
}

void FunctionalTestComponentService::initComponent(size_t component_index)
{
    if(component_index >= getNumberOfComponents())
        throw OutOfBoundsException(
            "FunctionalTestComponentService::setComponent() -> Error. Out of bounds");
    m_current_component = component_index;
    if(m_ff_registry) {
        delete m_form_factor;
        m_form_factor = m_ff_registry->createItem(m_component_names[component_index]);
    }
    if(m_ft2d_registry) {
        delete m_ft_distribution_2d;
        m_ft_distribution_2d = m_ft2d_registry->createItem(m_component_names[component_index]);
    }
}

std::string FunctionalTestComponentService::getCurrentComponentName() const
{
    return m_component_names[m_current_component];
}

std::string FunctionalTestComponentService::getReferenceFileName() const
{
    std::string result("ref_");
    result += m_testInfo->m_test_name;
    if(m_component_names[m_current_component] != DefaultComponentName)
        result += std::string("_")+m_component_names[m_current_component];
    result += std::string(".int.gz");
    return result;
}

const FunctionalTestInfo* FunctionalTestComponentService::getTestInfo() const
{
    return m_testInfo;
}

void FunctionalTestComponentService::init_registry(const std::string& registry_name)
{
    m_component_names.clear();
    m_current_component = 0;

    std::cout << "FunctionalTestComponentService::init_registry() ->" << registry_name << std::endl;
    if(registry_name == NoneRegistryName) {
        m_component_names.push_back(DefaultComponentName);

    }else if(registry_name == FormFactorsRegistryName) {
        m_ff_registry = new TestFormFactorsRegistry;
        for(auto it = m_ff_registry->begin(); it!= m_ff_registry->end(); ++it) {
            m_component_names.push_back(it->first);
        }

    }else if(registry_name == FTDistributions2DName) {
        m_ft2d_registry= new TestFTDistribution2DRegistry;
        for(auto it = m_ft2d_registry->begin(); it!= m_ft2d_registry->end(); ++it) {
            m_component_names.push_back(it->first);
        }

    } else {
        throw RuntimeErrorException("FunctionalTestComponentService::init_factory -> Error. "
                                    "Unknown factory '"+registry_name+"'.");
    }
}

//! Constructs functional test name corresponding to the current component. The goal is to have
//! different names of test depending from the context (single test, or multi test).
std::string FunctionalTestComponentService::getTestName() const
{
    std::string result = m_testInfo->m_test_name;
    if(getCurrentComponentName() != DefaultComponentName)
        result.clear(); // i.e. no name for sub-test just for printing purpose
    return result;
}

//! Constructs functional test description corresponding to the current component.
std::string FunctionalTestComponentService::getTestDescription() const
{
    std::string result = m_testInfo->m_test_description;
    if(getCurrentComponentName() != DefaultComponentName) result = getCurrentComponentName();
    return result;
}

double FunctionalTestComponentService::getTestThreshold() const
{
    return m_testInfo->m_threshold;
}
