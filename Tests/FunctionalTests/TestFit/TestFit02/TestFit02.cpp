#include "TestFit02.h"
#include "SampleBuilder.h"

#include "MaterialManager.h"
#include "MessageService.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include "MathFunctions.h"
#include "Utils.h"
#include "FitSuiteParameters.h"

#include <iostream>
#include <iomanip>
#include <boost/format.hpp>

using namespace FunctionalTests;



TestFit02::TestFit02()
    : m_test_name("TestFit02")
    , m_test_description("Fitting using sample builder.")
{ }


int TestFit02::run()
{
    // values we want to find
    double cylinder_height(5.0*Units::nanometer);
    double cylinder_radius(5.0*Units::nanometer);
    double prism3_half_side(5.0*Units::nanometer);
    double prism3_height(5.0*Units::nanometer);
    double cylinder_ratio(0.2);

    // setting sample builder to initial values
    SampleBuilder_t sample_builder(new SampleBuilder());
    sample_builder->setParameterValue("cylinder_height", cylinder_height);
    sample_builder->setParameterValue("cylinder_radius", cylinder_radius);
    sample_builder->setParameterValue("prism3_half_side", prism3_half_side);
    sample_builder->setParameterValue("prism3_height", prism3_height);
    sample_builder->setParameterValue("cylinder_ratio", cylinder_ratio);

    Simulation *simulation = createSimulation();
    simulation->setSampleBuilder(sample_builder);

    OutputData<double> *real_data = createRealData(simulation);

    // setting up fitting
    FitSuite *fitSuite = new FitSuite();
    fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2",
            "Combined") );
    fitSuite->initPrint(10);

    fitSuite->addFitParameter("*SampleBuilder/cylinder_height",
            4*Units::nanometer, 0.01*Units::nanometer,
            AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/cylinder_radius",
            6*Units::nanometer, 0.01*Units::nanometer,
            AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/prism3_half_side",
            4*Units::nanometer, 0.01*Units::nanometer,
            AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/prism3_height",
            6*Units::nanometer, 0.01*Units::nanometer,
            AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/cylinder_ratio", 0.2, 0.1,
            AttLimits::fixed());

    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( new SquaredFunctionMeanSquaredError() );
    //chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer() );
    fitSuite->addSimulationAndRealData(*simulation, *real_data, chiModule);

    fitSuite->runFit();

    delete simulation;
    delete real_data;

    // ---------------------------------------------------------------
    // analysing fit results
    // ---------------------------------------------------------------
    std::vector<double > initialParameters;
    initialParameters.push_back(cylinder_height);
    initialParameters.push_back(cylinder_radius);
    initialParameters.push_back(prism3_half_side);
    initialParameters.push_back(prism3_height);
    initialParameters.push_back(cylinder_ratio);
    std::vector<double > results = fitSuite->getFitParameters()->getValues();
    const double threshold = 1.0e-02;
    bool isSuccess = true;
    for(size_t i=0; i<results.size(); ++i) {
        double diff = std::fabs(results[i] - initialParameters[i])/
                initialParameters[i];
        if(diff > threshold) isSuccess=false;
    }

    std::cout << m_test_name << " " << m_test_description << " " <<
            (isSuccess ? "[OK]" : "[FAILED]") << std::endl;
    return (isSuccess ? 0 : 1);
}


// create simulation
Simulation *TestFit02::createSimulation()
{
    Simulation *simulation = new Simulation();
    simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100 , 0.0*Units::degree, 2.0*Units::degree);
    simulation->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    return simulation;
}


// generating "real" data by adding noise to the simulated data
OutputData<double> *TestFit02::createRealData(Simulation *simulation)
{
    const double noise_factor = 0.1;
    simulation->runSimulation();
    OutputData<double> *result = simulation->getIntensityData();
    OutputData<double>::iterator it = result->begin();
    int index(0);
    while (it != result->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        index++;

        ++it;
    }
    return result;
}


#ifdef STANDALONE
int main()
{
    //Utils::EnableFloatingPointExceptions();
    FunctionalTests::TestFit02 test;
    return test.run();
}
#endif

