#include "TestFit02.h"
#include "MaterialManager.h"
#include "MessageService.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "InterferenceFunctions.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include "FormFactorPrism3.h"
//#include "FitSuiteObserverFactory.h"
#include "MathFunctions.h"
#include "Utils.h"

#include "TBenchmark.h"

#include <iostream>
#include <iomanip>
#include <boost/format.hpp>

using namespace FunctionalTests;


TestFit02::TestFit02()
    : m_test_name("TestFit02")
    , m_test_description("Fitting using sample builder.")
{ }


TestFit02::~TestFit02()
{ }


int TestFit02::run()
{
    //std::numeric_limits<double>::signaling_NaN();

    SampleBuilder *sample_builder = new SampleBuilder();

    Simulation *simulation = createSimulation();
    simulation->setSampleBuilder(sample_builder);

    OutputData<double> *real_data = createRealData(simulation);
    std::cout << "real_data" << real_data->totalSum() << std::endl;
    return 0;

    FitSuite *fitSuite = new FitSuite();
    fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );
    //fitSuite->setPrintLevel(10);
    //fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    //fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );

    fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  6*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 4*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    6*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());
    //fitSuite->addFitParameter("*Normalizer/scale",    1, 0.01*Units::nanometer, AttLimits::limited(0.9,1.1) );


    // setting up fitSuite
    ChiSquaredModule chiModule;
    //chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
//    chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() );
    chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer() );
    //chiModule.setIntensityFunction( IntensityFunctionLog() );
    fitSuite->addSimulationAndRealData(*simulation, *real_data, chiModule);

    fitSuite->getFitParameters()->printParameters();
//    for(FitSuiteParameters::iterator it = fitSuite->getFitParameters()->begin(); it!=fitSuite->getFitParameters()->end(); ++it) {
//        std::cout << (*it) << std::endl;
//    }

    fitSuite->runFit();

    delete simulation;
    delete sample_builder;
    delete real_data;
    return 0;
}


// create simulation
Simulation *TestFit02::createSimulation()
{
    Simulation *simulation = new Simulation();
    simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
    simulation->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    return simulation;
}

// generating real data by adding noise to the simulated data
OutputData<double> *TestFit02::createRealData(Simulation *simulation)
{
    const double noise_factor = 0.1;
    simulation->runSimulation();
    OutputData<double> *result = simulation->getOutputDataClone();
    OutputData<double>::iterator it = result->begin();
    while (it != result->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        ++it;
    }
    return result;
}


// ----------------------------------------------------------------------------
// Sample builder to build mixture of cylinders and prisms on top of substrate
// 5 parameters
// ----------------------------------------------------------------------------
TestFit02::SampleBuilder::SampleBuilder()
    : m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
    , m_prism3_half_side(5.0*Units::nanometer)
    , m_prism3_height(5.0*Units::nanometer)
    , m_cylinder_ratio(0.2)
{
    init_parameters();
}

// registering parameters in parameter pool
void TestFit02::SampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("m_cylinder_height", &m_cylinder_height);
    getParameterPool()->registerParameter("m_cylinder_radius", &m_cylinder_radius);
    getParameterPool()->registerParameter("m_prism3_half_side", &m_prism3_half_side);
    getParameterPool()->registerParameter("m_prism3_height", &m_prism3_height);
    getParameterPool()->registerParameter("m_cylinder_ratio", &m_cylinder_ratio);
}

// build sample from registered parameters
ISample *TestFit02::SampleBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();
    const IMaterial *air_material = MaterialManager::getHomogeneousMaterial("Air", 1.0, 1.0);
    const IMaterial *substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)),0.0, m_cylinder_ratio);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(m_prism3_height, m_prism3_half_side)), 0.0, 1.0 - m_cylinder_ratio);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer->addLayer(air_layer_decorator);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;

//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration;
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)),0.0, m_cylinder_ratio);
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(m_prism3_height, m_prism3_half_side)), 0.0, 1.0 - m_cylinder_ratio);
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);

//    return p_multi_layer;
}

#ifdef STANDALONE
int main()
{
    Utils::EnableFloatingPointExceptions();
    FunctionalTests::TestFit02 test;
    return test.run();
}
#endif

