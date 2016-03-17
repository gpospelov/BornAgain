// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingModule2.cpp
//! @brief     Implements class TestFittingModule2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFittingModule2.h"
#include "AttLimits.h"
#include "DrawHelper.h"
#include "Exceptions.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FitStrategyAdjustParameters.h"
#include "FormFactors.h"
#include "Simulation.h"
#include "IIntensityFunction.h"
#include "IObserver.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSTools.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "OutputDataFunctions.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DGaussian.h"
#include "Units.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TH2D.h"



TestFittingModule2::TestFittingModule2()
    : mp_real_data(0)
    , mp_simulated_data(0)
    , mp_simulation(0)
    , mp_sample_builder( new SampleBuilder())
    , m_fitSuite(0)
{
    // setting up fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer(
        MinimizerFactory::createMinimizer("Minuit2", "Combined") );
    m_fitSuite->attachObserver(
        FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver(
        FitSuiteObserverFactory::createDrawObserver() );
    m_fitSuite->attachObserver(
        FitSuiteObserverFactory::createTreeObserver() );
}


TestFittingModule2::~TestFittingModule2()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_simulation;
    delete m_fitSuite;
}


void TestFittingModule2::execute()
{
    // basic fit example
    //fit_example_basics();

    // fit example with normalizer
    fit_example_chimodule();

    // fit example with strategies
    //fit_example_strategy_data();
    //fit_example_strategy_parameters();

    // fit example with data masking
    //fit_example_mask();
}

//! Basic fit example.

void TestFittingModule2::fit_example_basics()
{
    throw NotImplementedException("Code is obsolete");

//    initializeSimulation();
//    initializeRealData();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",
//                                5*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",
//                                6*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_length",
//                                10*Units::nanometer, 2*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",
//                                6*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio",
//                                0.2, 0.1,
//                                AttLimits::fixed());

//    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

//    m_fitSuite->runFit();
}

//! Fit example with chi2 module adjustment.

void TestFittingModule2::fit_example_chimodule()
{
    throw NotImplementedException("Code is obsolete");
//    initializeSimulation();
//    initializeRealData();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",
//                                4*Units::nanometer, 0.01*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",
//                                6*Units::nanometer, 0.01*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_length",
//                                8*Units::nanometer, 0.02*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",
//                                6*Units::nanometer, 0.01*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio",
//                                0.2, 0.1,
//                                AttLimits::fixed());

//    // setting up fitSuite
//    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError() );
//    chiModule.setIntensityNormalizer( IntensityScaleAndShiftNormalizer() );
//    m_fitSuite->addSimulationAndRealData(
//        *mp_simulation, *mp_real_data, chiModule);


////    ParameterPool *pool = m_fitSuite->getFitObjects()->createParameterTree();
////    std::cout << *pool;

//    m_fitSuite->getFitParameters()->printParameters();
//    m_fitSuite->getFitObjects()->printParameters();


//    for(FitSuiteParameters::iterator it =
//            m_fitSuite->getFitParameters()->begin();
//        it!=m_fitSuite->getFitParameters()->end(); ++it)
//        std::cout << (*it) << std::endl;
//    m_fitSuite->runFit();
}


//! Fit example with strategies.

void TestFittingModule2::fit_example_strategy_data()
{
    throw NotImplementedException("TestFittingModule2::fit_example_strategy_data() -> Obsolete code.");

//    initializeSimulation();
//    initializeRealData();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",
//                                12*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",
//                                2*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_length",
//                                24*Units::nanometer, 2*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",
//                                2*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio",
//                                0.2, 0.1,
//                                AttLimits::fixed());

//    // Applying fit strategy: resizing real data
//    m_fitSuite->addFitStrategy(new FitStrategyAdjustData(3));
//    m_fitSuite->addFitStrategy(new FitStrategyAdjustData(2));
//    m_fitSuite->addFitStrategy(new FitStrategyAdjustData(1));
//    m_fitSuite->addFitStrategy(new FitStrategyDefault());

//    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

//    m_fitSuite->setMinimizer(
//        MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

//    m_fitSuite->runFit();
}


//! Fix example with adjust parameters strategies
void TestFittingModule2::fit_example_strategy_parameters()
{
    throw NotImplementedException("Code is obsolete");

//    initializeSimulation();
//    initializeRealData();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",
//                                12*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",
//                                2*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side",
//                                12*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",
//                                2*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio",
//                                0.2, 0.1,
//                                AttLimits::fixed());

//    // Applying fit strategy
//    FitStrategyReleaseParameters strategy;
//    std::vector<std::string> pars = boost::assign::list_of("*SampleBuilder/m_cylinder_height")("*SampleBuilder/m_cylinder_radius");
//    strategy.setReleased(pars);
//    m_fitSuite->addFitStrategy(strategy);
//    pars = boost::assign::list_of("*SampleBuilder/m_prism3_half_side")("*SampleBuilder/m_prism3_height");
//    strategy.setReleased(pars);
//    m_fitSuite->addFitStrategy(strategy);

////    FitStrategyFixParameters strategy2;
////    pars = boost::assign::list_of("*SampleBuilder/m_cylinder_ratio");
////    strategy2.setFixed(pars);
////    m_fitSuite->addFitStrategy(strategy2);

//    pars = boost::assign::list_of("*SampleBuilder/m_cylinder_height")("*SampleBuilder/m_cylinder_radius")("*SampleBuilder/m_prism3_half_side")("*SampleBuilder/m_prism3_height");
//    strategy.setReleased(pars);
//    m_fitSuite->addFitStrategy(strategy);

//    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

//    m_fitSuite->setMinimizer(
//        MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

//    m_fitSuite->runFit();
}


//! Fit example with data masking.

void TestFittingModule2::fit_example_mask()
{
    throw NotImplementedException("Code is obsolete");

//    initializeSimulation();
//    initializeRealData();

//    ResolutionFunction2DGaussian resfunc(0.0002, 0.0002);
//    mp_simulation->setDetectorResolutionFunction(resfunc);

//    TCanvas *c1 = DrawHelper::createAndRegisterCanvas(
//        "c1_test_meso_crystal", "mesocrystal");
//    c1->cd(); gPad->SetLogz();
//    c1->Divide(2,2);

//    c1->cd(1);
//    gPad->SetLogz();
//    gPad->SetRightMargin(0.115);
//    gPad->SetLeftMargin(0.115);
//    IsGISAXSTools::setMinimum(1.0);
//    IsGISAXSTools::setMaximum(1e10);
//    IsGISAXSTools::drawOutputDataInPad(*mp_real_data, "COLZ", "real_data");
//    c1->Update();

//    const double minima[]={0.003, 0.003};
//    const double maxima[]={0.03, 0.03};
//    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(
//        *mp_real_data, minima, maxima);
//    mp_real_data->setMask(*mask1);

//    c1->cd(2);
//    gPad->SetLogz();
//    gPad->SetRightMargin(0.115);
//    gPad->SetLeftMargin(0.115);
//    IsGISAXSTools::drawOutputDataInPad(*mp_real_data, "COLZ", "real_data");
//    c1->Update();

//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",
//                                4*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",
//                                4*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_length",
//                                8*Units::nanometer, 2*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",
//                                4*Units::nanometer, 1*Units::nanometer,
//                                AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio",
//                                0.2, 0.1,
//                                AttLimits::fixed());

//    ChiSquaredModule chiModule;
//    chiModule.setIntensityNormalizer( IntensityScaleAndShiftNormalizer(1.0,0) );
//    m_fitSuite->addSimulationAndRealData(
//        *mp_simulation, *mp_real_data, chiModule);

//    m_fitSuite->runFit();
}

//! Initialize simulation.

void TestFittingModule2::initializeSimulation()
{
    if( !mp_sample_builder )
        throw NullPointerException(
            "TestFittingModule2::initializeSimulation() -> "
            "No sample builder defined");
    delete mp_simulation;
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(
         1.0*Units::angstrom,
         0.2*Units::degree,
         0.0*Units::degree);
}


//! Create noisy data (simulated experiment).

void TestFittingModule2::initializeRealData()
{
    if( !mp_simulation )
        throw NullPointerException(
            "TestFittingModule2::initializeRealData() -> "
            "Error! No simulation of sample defined ");

    mp_simulation->runSimulation();
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(
        *mp_simulation->getOutputData());

    // draw data
    TCanvas *c1 = new TCanvas("c1","c1",640, 480);
    c1->cd(); gPad->SetLogz();
    TH2D *hist = IsGISAXSTools::getOutputDataTH2D( *mp_real_data, "real_data");
    hist->Draw("COLZ");
    c1->Update();
}


// simple sample - mixture of cylinders and prisms on top of substrate
// builder via ISampleBuilder
// 5 fit parameters

TestFittingModule2::SampleBuilder::SampleBuilder()
    : m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
    , m_prism3_length(10.0*Units::nanometer)
    , m_prism3_height(5.0*Units::nanometer)
    , m_cylinder_ratio(0.2)
{
    init_parameters();
}


ISample *TestFittingModule2::SampleBuilder::buildSample() const
{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    HomogeneousMaterial air_material("Air", n_air);
//    HomogeneousMaterial substrate_material("Substrate", n_substrate);
//    HomogeneousMaterial particle_material("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(substrate_material);
//    ParticleLayout particle_layout;
//    Particle particle1(particle_material, FormFactorCylinder(
//                           m_cylinder_radius, m_cylinder_height) );
//    Particle particle2(particle_material, FormFactorPrism3(
//                           m_prism3_length, m_prism3_height) );
//    particle_layout.addParticle(particle1, m_cylinder_ratio);
//    particle_layout.addParticle(particle2, 1.0 - m_cylinder_ratio);
//    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);

//    return p_multi_layer;
    throw Exceptions::NotImplementedException("Cleanup the code!");

}


void TestFittingModule2::SampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("m_cylinder_radius", &m_cylinder_radius);
    registerParameter("m_cylinder_height", &m_cylinder_height);
    registerParameter("m_prism3_length", &m_prism3_length);
    registerParameter("m_prism3_height", &m_prism3_height);
    registerParameter("m_cylinder_ratio", &m_cylinder_ratio);
}
