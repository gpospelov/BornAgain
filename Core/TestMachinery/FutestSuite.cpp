// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FutestSuite.cpp
//! @brief     Implements class FutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>

#include "FunctionalTestRegistry.h"
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
#include "FutestSuite.h"

FutestSuite::FutestSuite(const FunctionalTestInfo* info)
    : m_info(info)
    , m_formfactor(0)
    , m_ft_distribution_2d(0)
    , m_ff_registry(0)
    , m_ft2d_registry(0)
    , m_current_component(0)
{
    init_registry(m_info->m_component_registry_name);
}

FutestSuite::~FutestSuite()
{
    delete m_formfactor;
    delete m_ff_registry;

    delete m_ft_distribution_2d;
    delete m_ft2d_registry;
}

IFormFactor* FutestSuite::getFormFactor() const
{
    if(!m_formfactor)
        throw NullPointerException(
            "FutestSuite::getFormFactor() -> Error. No form factor defined.");
    return m_formfactor->clone();
}

IFTDistribution2D* FutestSuite::getFTDistribution2D() const
{
    if(!m_ft_distribution_2d)
        throw NullPointerException(
            "FutestSuite::getFTDistribution2D() -> Error. "
            "No FT distribution defined.");
    return m_ft_distribution_2d->clone();
}

GISASSimulation* FutestSuite::getSimulation() const
{
    SimulationRegistry sim_registry;
    GISASSimulation* result = sim_registry.createItem(m_info->m_simulation_name);
    result->setSampleBuilder(getSampleBuilder());
    return result;
}

std::shared_ptr<class ISampleBuilder> FutestSuite::getSampleBuilder() const
{
    SampleBuilderFactory sample_factory;
    std::shared_ptr<class ISampleBuilder> sample_builder(
        sample_factory.createItem(m_info->m_sample_builder_name) );
    sample_builder->init_from(this);
    return sample_builder;
}

OutputData<double>* FutestSuite::getReferenceData() const
{
    OutputData<double>* result(nullptr);
    std::string filename = Utils::FileSystem::GetReferenceDataDir() + getReferenceFileName();

    try {
        result = IntensityDataIOFactory::readOutputData(filename);
    } catch(const std::exception& ex) {
        std::cout << "FutestSuite::getReferenceData() -> Exception caught."
                  << ex.what() << std::endl;
    }
    return result;
}

void FutestSuite::initComponent(size_t component_index)
{
    if(component_index >= getNumberOfComponents())
        throw OutOfBoundsException(
            "FutestSuite::setComponent() -> Error. Out of bounds");
    m_current_component = component_index;
    if(m_ff_registry) {
        delete m_formfactor;
        m_formfactor = m_ff_registry->createItem(m_component_names[component_index]);
    }
    if(m_ft2d_registry) {
        delete m_ft_distribution_2d;
        m_ft_distribution_2d = m_ft2d_registry->createItem(m_component_names[component_index]);
    }
}

std::string FutestSuite::getCurrentComponentName() const
{
    return m_component_names[m_current_component];
}

std::string FutestSuite::getReferenceFileName() const
{
    std::string result("ref_");
    result += m_info->m_test_name;
    if(m_component_names[m_current_component] != "Default")
        result += std::string("_")+m_component_names[m_current_component];
    result += std::string(".int.gz");
    return result;
}

void FutestSuite::init_registry(const std::string& registry_name)
{
    m_component_names.clear();
    m_current_component = 0;

    std::cout << "FutestSuite::init_registry() ->" << registry_name << std::endl;
    if       (registry_name == "None") {
        m_component_names.push_back("Default");

    } else if(registry_name == "FormFactorsRegistry") {
        m_ff_registry = new TestFormFactorsRegistry;
        m_component_names = m_ff_registry->getNames();

    } else if(registry_name == "FTDistributions2DRegistry") {
        m_ft2d_registry= new TestFTDistribution2DRegistry;
        m_component_names = m_ft2d_registry->getNames();

    } else
        throw RuntimeErrorException("FutestSuite::init_factory -> Error. "
                                    "Unknown factory '"+registry_name+"'.");
}

//! Constructs functional test name corresponding to the current component. The goal is to have
//! different names of test depending from the context (single test, or multi test).
std::string FutestSuite::getTestName() const
{
    std::string result = m_info->m_test_name;
    if(getCurrentComponentName() != "Default")
        result += "_" + getCurrentComponentName();
    return result;
}

//! Constructs functional test description corresponding to the current component.
std::string FutestSuite::getTestDescription() const
{
    return m_info->m_test_description;
}

double FutestSuite::getTestThreshold() const
{
    return m_info->m_threshold;
}
