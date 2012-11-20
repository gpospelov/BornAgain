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

#include "IObserver.h"
#include "FitSuite.h"
#include "ROOTMinimizer.h"
#include "FitSuiteStrategy.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"


TestFittingModule2::TestFittingModule2()
: mp_exact_data(0)
, mp_real_data(0)
, mp_simulated_data(0)
, mp_experiment(0)
, mp_sample_builder(0)
, m_fitSuite(0)
{
}


TestFittingModule2::~TestFittingModule2()
{
    delete mp_exact_data;
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_experiment;
    delete mp_sample_builder;
    delete m_fitSuite;
}


//template<class T> const bool haveSameDimensions(const OutputData<T>& left, const OutputData<T>& right)
//{

//    return true;
//}


void TestFittingModule2::execute()
{
//    OutputData<double > *data1 = new OutputData<double>;
//    data1->addAxis(std::string("a1"), 0., 10., 100);
//    data1->addAxis(std::string("a2"), 0., 10., 100);

//    OutputData<double > *data2 = new OutputData<double>;
//    data2->addAxis(std::string("a1"), 0., 10., 100);
//    data2->addAxis(std::string("a2"), 0., 10., 99.9999999999999999999);

//    if( data1->hasSameDimensions(*data2) ) {
//        std::cout << "Same dimensions " << std::endl;
//    } else {
//        std::cout << "Not Same dimensions " << std::endl;

//    }
//    if( data1->hasSameShape(*data2) ) {
//        std::cout << "Same shape " << std::endl;
//    } else {
//        std::cout << "Not Same shape " << std::endl;
//    }

    // new sample builder
    mp_sample_builder = new TestSampleBuilder();
    ParameterPool *pool = mp_sample_builder->createParameterTree();
    std::cout << *pool << std::endl;
    delete pool;

    // creating fit suite
    m_fitSuite = new FitSuite();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1,15) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1,15) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1,15) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::limited(1,15) );

    //m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.5, 0.1, AttLimits::limited(0.1, 0.9));
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

    // Applying fit strategy: disturning data to get out of local minima
    //m_fitSuite->addFitStrategy(new FitSuiteStrategyBootstrap());

    initializeExperiment();
    generateRealData(0.1);

    // drawing initial data
    std::string canvas_name("TestFittingModule_c1");
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), "Test of the fitting suite", 800, 600);
    c1->cd(); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*mp_exact_data, "CONT4 Z", "exact data");
    c1->Update();
\
    // setting up fitSuite
//    m_fitSuite->setExperiment(mp_experiment);
//    m_fitSuite->setRealData(*mp_real_data);
    m_fitSuite->addExperimentAndRealData(mp_experiment, mp_real_data);

    m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );

    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );
    //fitSuite->attachObserver( new FitSuiteObserverWriteTree() );

    m_fitSuite->runFit();

//    delete drawObserver;
//    delete writeObserver;
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
    mp_experiment->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    mp_experiment->setBeamIntensity(1e10);
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


/* ************************************************************************* */
// generate real data
/* ************************************************************************* */
void TestFittingModule2::generateRealData(double noise_factor)
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


