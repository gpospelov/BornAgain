#include "TestFittingModule2.h"
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
#include "IIntensityFunction.h"

#include "IObserver.h"
#include "FitSuite.h"
#include "ROOTMinimizer.h"
#include "FitSuiteStrategy.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TH2D.h"


TestFittingModule2::TestFittingModule2()
    : mp_real_data(0)
    , mp_simulated_data(0)
    , mp_experiment(0)
    , mp_sample_builder(0)
    , m_fitSuite(0)
{
    mp_sample_builder = new TestSampleBuilder();

    // setting up fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );
}


TestFittingModule2::~TestFittingModule2()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_experiment;
    delete mp_sample_builder;
    delete m_fitSuite;
}


void TestFittingModule2::execute()
{
    // basic fit example
    //fit_example_basics();

    // fit example with normalizer
    fit_example_chimodule();

    // fit example with strategies
    //fit_example_strategies();
}


/* ************************************************************************* */
// basic fit example
/* ************************************************************************* */
void TestFittingModule2::fit_example_basics()
{
    initializeExperiment();
    initializeRealData();

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    //m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.5, 0.1, AttLimits::limited(0.1, 0.9));
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());

    m_fitSuite->addExperimentAndRealData(*mp_experiment, *mp_real_data);

    m_fitSuite->runFit();

}


/* ************************************************************************* */
// fit example with chi2 module adjustment
/* ************************************************************************* */
void TestFittingModule2::fit_example_chimodule()
{
    initializeExperiment();
    //mp_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    initializeRealData();


    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e10, 1e3, AttLimits::limited(1e8, 1e12));

    // setting up fitSuite
    ChiSquaredModule chiModule;
    //chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() );
    //chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    //chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift(1e10,0) );
    chiModule.setIntensityFunction( IntensityFunctionLog() );
    m_fitSuite->addExperimentAndRealData(*mp_experiment, *mp_real_data, chiModule);

    m_fitSuite->runFit();

}


/* ************************************************************************* */
// fit example with strategies
/* ************************************************************************* */
void TestFittingModule2::fit_example_strategies()
{
    initializeExperiment();
    initializeRealData();

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());

    // Applying fit strategy: fixing/releasing parameters
//    FitSuiteStrategyAdjustParameters *strategy0 = new FitSuiteStrategyAdjustParameters("strategy0");
//    strategy0->fix_all().release("*SampleBuilder/m_cylinder_ratio");
//    m_fitSuite->addFitStrategy(strategy0);
//    FitSuiteStrategyAdjustParameters *strategy1 = new FitSuiteStrategyAdjustParameters("strategy1");
//    strategy1->release_all().fix("*SampleBuilder/m_cylinder_ratio");
//    m_fitSuite->addFitStrategy(strategy1);
//    FitSuiteStrategyAdjustParameters *strategy2 = new FitSuiteStrategyAdjustParameters("strategy2");
//    strategy2->release_all();
//    m_fitSuite->addFitStrategy(strategy2);

    // Applying fit strategy: resizing real data
    m_fitSuite->addFitStrategy(new FitSuiteStrategyAdjustData(3));
    m_fitSuite->addFitStrategy(new FitSuiteStrategyAdjustData(2));
    m_fitSuite->addFitStrategy(new FitSuiteStrategyAdjustData(1));
    m_fitSuite->addFitStrategy(new FitSuiteStrategyDefault());

    // Applying fit strategy: disturbing data to get out of local minima
    //m_fitSuite->addFitStrategy(new FitSuiteStrategyBootstrap());

    m_fitSuite->addExperimentAndRealData(*mp_experiment, *mp_real_data);

    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );

    m_fitSuite->runFit();

}



/* ************************************************************************* */
// initializing experiment
/* ************************************************************************* */
void TestFittingModule2::initializeExperiment()
{
    if( !mp_sample_builder ) {
        throw NullPointerException("TestFittingModule2::initializeExperiment() -> No sample builder defined");
    }
    delete mp_experiment;
    mp_experiment = new GISASExperiment(mp_options);
    mp_experiment->setSampleBuilder(mp_sample_builder);
    mp_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
    mp_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    //mp_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    mp_experiment->setBeamIntensity(1e10);
}


/* ************************************************************************* */
// initializing real data
/* ************************************************************************* */
void TestFittingModule2::initializeRealData()
{
    if( !mp_experiment ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No experiment o sample defined ");

    // generating "real" data
    mp_experiment->runSimulation();
    mp_experiment->normalize();
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_experiment->getOutputData());

    // drawing data
    TCanvas *c1 = new TCanvas("c1","c1",640, 480);
    c1->cd(); gPad->SetLogz();
    TH2D *hist = IsGISAXSTools::getOutputDataTH2D( *mp_real_data, "real_data");
    hist->Draw("COLZ");
    c1->Update();
}


/* ************************************************************************* */
// simple sample - mixture of cylinders and prisms on top of substrate
// builder via ISampleBuilder
// 5 fit parameters
/* ************************************************************************* */
TestFittingModule2::TestSampleBuilder::TestSampleBuilder()
    : m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
    , m_prism3_half_side(5.0*Units::nanometer)
    , m_prism3_height(5.0*Units::nanometer)
    , m_cylinder_ratio(0.2)
{
    init_parameters();
}


ISample *TestFittingModule2::TestSampleBuilder::buildSample() const
{
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
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)),0.0, m_cylinder_ratio);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(m_prism3_height, m_prism3_half_side)), 0.0, 1.0 - m_cylinder_ratio);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

void TestFittingModule2::TestSampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("m_cylinder_height", &m_cylinder_height);
    getParameterPool()->registerParameter("m_cylinder_radius", &m_cylinder_radius);
    getParameterPool()->registerParameter("m_prism3_half_side", &m_prism3_half_side);
    getParameterPool()->registerParameter("m_prism3_height", &m_prism3_height);
    getParameterPool()->registerParameter("m_cylinder_ratio", &m_cylinder_ratio);
}


