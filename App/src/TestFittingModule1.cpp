#include "TestFittingModule1.h"
#include "Units.h"
#include "MathFunctions.h"
#include "GISASExperiment.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "Particle.h"
#include "FormFactors.h"
#include "Exceptions.h"
#include "DrawHelper.h"
#include "FitSuiteHelper.h"
#include "ResolutionFunction2DSimple.h"
#include "AttLimits.h"
#include "ISquaredFunction.h"
#include "IOutputDataNormalizer.h"

#include "IObserver.h"
#include "FitSuite.h"
#include "ROOTMinimizer.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"


TestFittingModule1::TestFittingModule1()
: mp_exact_data(0)
, mp_real_data(0)
, mp_simulated_data(0)
, mp_experiment(0)
, mp_sample(0)
, m_fitSuite(0)
{
}


TestFittingModule1::~TestFittingModule1()
{
    delete mp_exact_data;
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_experiment;
    delete mp_sample;
}


void TestFittingModule1::execute()
{
    // creating fit suite
    m_fitSuite = new FitSuite();

    // initializing data
    initializeSample2();

    initializeExperiment();
    generateRealData(0.1);

    // drawing initial data
    std::string canvas_name("TestFittingModule_c1");
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), "Test of the fitting suite", 800, 600);
    c1->cd(); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*mp_exact_data, "CONT4 Z", "exact data");
    c1->Update();
\
    m_fitSuite->addExperimentAndRealData(*mp_experiment, *mp_real_data);

    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Simplex") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Minimize") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Combined") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Fumili") ); //doesn't work, Fumili wants special function with derivative
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiMin", "ConjugateFR") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiMin", "BFGS") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiMin", "SteepestDescent") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLSimAn", "") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Genetic", "") );
    // tuning minimizer
    //ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer()))->getROOTMinimizer();
    //minim->SetPrecision(0.00001);
    //minim->SetTolerance(0.00001);
    //minim->SetStrategy(2);
    //minim->SetMaxFunctionCalls(50); // for Minuit
    //minim->SetMaxIterations(50); // for GSL
    //minim->SetPrintLevel(4);

    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );
    //fitSuite->attachObserver( new FitSuiteObserverWriteTree() );

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
// simple sample - cylinders in BA
// 2 fit parameters
/* ************************************************************************* */
void TestFittingModule1::initializeSample()
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
    m_fitSuite->addFitParameter("*height", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*radius", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
}


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
//    m_fitSuite->addFitParameter("*FormFactorCylinder/height", 12*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1.,15.) );
//    m_fitSuite->addFitParameter("*FormFactorCylinder/radius", 2*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1.,15.) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1.,15.) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/height", 2*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1.,15.) );
}




/* ************************************************************************* */
// generate real data
/* ************************************************************************* */
void TestFittingModule1::generateRealData(double noise_factor)
{
    if(mp_exact_data) delete mp_exact_data;

    mp_experiment->runSimulation();
    mp_experiment->normalize();
    mp_exact_data = mp_experiment->getOutputDataClone();
    if (mp_real_data) delete mp_real_data;

    mp_real_data = mp_exact_data->clone();
    OutputData<double>::iterator it = mp_real_data->begin();
    while (it != mp_real_data->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        ++it;
    }
}

