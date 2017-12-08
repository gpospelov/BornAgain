#include "IFittingTest.h"
#include "FitSuite.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "MinimizerFactory.h"
#include "SampleBuilderFactory.h"
#include "SimulationFactory.h"
#include "FitParameterSet.h"
#include <boost/format.hpp>

namespace {
    const double default_parameter_tolerance = 0.01;
}

IFittingTest::IFittingTest(const std::string& minimizer_name,
                           const std::string& minimizer_algorithm,
                           const std::string& simulation_name,
                           const std::string& builder_name)
    : m_minimizer_name(minimizer_name), m_minimizer_algorithm(minimizer_algorithm),
      m_simulation_name(simulation_name), m_sample_builder_name(builder_name)
{
}

IFittingTest::~IFittingTest() = default;


bool IFittingTest::runTest()
{
    initParameterPlan();

    std::unique_ptr<MultiLayer> sample(createSample());

    std::unique_ptr<Simulation> simulation(createSimulation());
    simulation->setSample(*sample.get());
    simulation->runSimulation();

    std::unique_ptr<OutputData<double> > real_data(createOutputData(simulation.get()));

    std::unique_ptr<FitSuite> fitSuite(createFitSuite());
    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    std::cout << fitSuite->treeToString() << std::endl;
    std::cout << fitSuite->parametersToString() << std::endl;
    std::cout << fitSuite->setupToString() << std::endl;
    fitSuite->runFit();

    std::vector<double> valuesAtMinimum = fitSuite->fitParameters()->values();

    // analyze results
    bool success = true;
    size_t index(0);
    for(auto& plan : m_parplans) {
        double foundValue = valuesAtMinimum[index];
        double diff = std::abs(foundValue - plan->expectedValue()) / plan->expectedValue();
        if (diff > plan->tolerance())
            success = false;
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) %s\n") %
            ("par"+std::to_string(index)) % foundValue % diff % (success ? "OK" : "FAILED");
        ++index;
    }

    return success;
}

void IFittingTest::initParameterPlan() {
  for(auto& plan : m_parplans)
      plan->setTolerance(default_parameter_tolerance);
}

std::unique_ptr<FitSuite> IFittingTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    IMinimizer* minimizer = MinimizerFactory::createMinimizer(
                m_minimizer_name, m_minimizer_algorithm);
    result->setMinimizer(minimizer);

    for(auto& plan : m_parplans)
        result->addFitParameter(plan->fitParameter());

    return result;
}

std::unique_ptr<MultiLayer> IFittingTest::createSample()
{
    SampleBuilderFactory builderFactory;
    std::unique_ptr<MultiLayer> result(builderFactory.createSample(m_sample_builder_name));
    for(auto& plan : m_parplans)
        for(auto pattern : plan->fitParameter().patterns())
            result->setParameterValue(pattern, plan->expectedValue());
    return result;
}

std::unique_ptr<Simulation> IFittingTest::createSimulation()
{
    SimulationFactory simRegistry;
    return simRegistry.create(m_simulation_name);
}

std::unique_ptr<OutputData<double> > IFittingTest::createOutputData(
    const Simulation* simulation)
{
    std::unique_ptr<OutputData<double>> result(simulation->getDetectorIntensity());
    return result;
}
