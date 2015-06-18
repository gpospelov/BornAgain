#include "FunctionalTestComponentService.h"
#include "SimulationRegistry.h"
#include "SampleBuilderFactory.h"
#include "TestFormFactorsRegistry.h"

FunctionalTestComponentService::FunctionalTestComponentService(const std::string &simulation_name,
                                                                 const std::string &sample_builder_name,
                                                                 const std::string &factory_name)
{
    SimulationRegistry sim_registry;
    GISASSimulation *simulation = sim_registry.createSimulation(simulation_name);

    SampleBuilderFactory sample_factory;
    SampleBuilder_t builder = sample_factory.createBuilder(sample_builder_name);


    TestFormFactorsRegistry registry;

    for( std::map<std::string, IFormFactor *>::iterator it=registry.begin(); it!=registry.end(); ++it) {

    }
}
