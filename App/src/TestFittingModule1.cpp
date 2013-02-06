#include "TestFittingModule1.h"
#include "AttLimits.h"
#include "DrawHelper.h"
#include "Exceptions.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactors.h"
#include "GISASExperiment.h"
#include "ISquaredFunction.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSTools.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "ResolutionFunction2DSimple.h"
#include "Units.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"


TestFittingModule1::TestFittingModule1()
    : mp_real_data(0)
    , mp_simulated_data(0)
    , mp_experiment(0)
    , mp_sample(0)
    , m_fitSuite(0)
{
    m_fitSuite = new FitSuite();
}


TestFittingModule1::~TestFittingModule1()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_experiment;
    delete mp_sample;
}


void TestFittingModule1::execute()
{
    // initializing data
    initializeSample1();
    initializeExperiment();
    initializeRealData();
    m_fitSuite->addExperimentAndRealData(*mp_experiment, *mp_real_data);

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLMultiFit") ); // LMA
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );

    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );
    //fitSuite->attachObserver( ObserverFactory::createTreeObserver() );

    m_fitSuite->runFit();
}


/* ************************************************************************* */
// initializing experiment
/* ************************************************************************* */
void TestFittingModule1::initializeExperiment()
{
    if( !mp_sample ) {
        throw NullPointerException("TestFittingModule1::initializeExperiment() -> No sample defined");
    }
    delete mp_experiment;
    mp_experiment = new GISASExperiment(mp_options);
    mp_experiment->setSample(*mp_sample);
    mp_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
    mp_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    //mp_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    mp_experiment->setBeamIntensity(1e10);
}


/* ************************************************************************* */
// initialize sample: layer + nanoparticles, 2 parameters
/* ************************************************************************* */
void TestFittingModule1::initializeSample1()
{
    delete mp_sample;

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    mp_sample = p_multi_layer;

    // defining parameters for minimization
    if( !m_fitSuite ) {
        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
    }

    m_fitSuite->addFitParameter("*height", 4.*Units::nanometer, 0.04*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*height", 4.*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(0.01, 10.) );
//    m_fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::limited(0.01, 10.) );
}


/* ************************************************************************* */
// initialize sample: layer + substrate + nanoparticles, 4 parameters
/* ************************************************************************* */
void TestFittingModule1::initializeSample2()
{
    delete mp_sample;

    double cylinder_height = 5.0*Units::nanometer;
    double cylinder_radius = 5.0*Units::nanometer;
    double prism3_half_side = 5.0*Units::nanometer;
    double prism3_height = 5.0*Units::nanometer;

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(cylinder_height, cylinder_radius)),0.0, 0.2);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(prism3_height, prism3_half_side)), 0.0, 0.8);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);

    mp_sample = p_multi_layer;
    // defining parameters for minimization
    if( !m_fitSuite ) {
        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
    }

    m_fitSuite->addFitParameter("*FormFactorCylinder/height", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorCylinder/radius", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorPrism3/half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*FormFactorPrism3/height", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
}



/* ************************************************************************* */
// initializing real data
/* ************************************************************************* */
void TestFittingModule1::initializeRealData()
{
    if( !mp_experiment ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No experiment o sample defined ");

    mp_experiment->runSimulation();
    mp_experiment->normalize();
    m_fitSuite->getFitObjects()->setExperimentNormalize(true);
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_experiment->getOutputData());
}


