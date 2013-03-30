// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingModule2.cpp 
//! @brief     Implements class TestFittingModule2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "TestFittingModule2.h"
#include "AttLimits.h"
#include "DrawHelper.h"
#include "Exceptions.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "IFitSuiteStrategy.h"
#include "FormFactors.h"
#include "Simulation.h"
#include "IIntensityFunction.h"
#include "IObserver.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSTools.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "OutputDataFunctions.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "ResolutionFunction2DSimple.h"
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
    , mp_sample_builder(0)
    , m_fitSuite(0)
{
    mp_sample_builder = new SampleBuilder();

    // setting up fitSuite
    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Combined") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createTreeObserver() );

}


TestFittingModule2::~TestFittingModule2()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_simulation;
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

    // fit example with data masking
    //fit_example_mask();
}


/* ************************************************************************* */
// basic fit example
/* ************************************************************************* */
void TestFittingModule2::fit_example_basics()
{
    initializeSimulation();
    initializeRealData();

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  5*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  6*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 5*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    6*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());

    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

    m_fitSuite->runFit();

}


/* ************************************************************************* */
// fit example with chi2 module adjustment
/* ************************************************************************* */
void TestFittingModule2::fit_example_chimodule()
{
    initializeSimulation();
    initializeRealData();

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  6*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 4*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    6*Units::nanometer, 0.01*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());
    //m_fitSuite->addFitParameter("*Normalizer/scale",    1, 0.01*Units::nanometer, AttLimits::limited(0.9,1.1) );


    // setting up fitSuite
    ChiSquaredModule chiModule;
    //chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
//    chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() );
    chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer() );
    //chiModule.setIntensityFunction( IntensityFunctionLog() );
    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data, chiModule);

    for(FitSuiteParameters::iterator it = m_fitSuite->getFitParameters()->begin(); it!=m_fitSuite->getFitParameters()->end(); ++it) {
        std::cout << (*it) << std::endl;
    }

    m_fitSuite->runFit();

}


/* ************************************************************************* */
// fit example with strategies
/* ************************************************************************* */
void TestFittingModule2::fit_example_strategies()
{
    initializeSimulation();
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

    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

    m_fitSuite->runFit();
}

// ----------------------------------------------------------------------------
// fit example with data masking
// ----------------------------------------------------------------------------
void TestFittingModule2::fit_example_mask()
{
    initializeSimulation();
    initializeRealData();
    mp_simulation->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("c1_test_meso_crystal", "mesocrystal");
    c1->cd(); gPad->SetLogz();
    c1->Divide(2,2);

    c1->cd(1);
    gPad->SetLogz();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    IsGISAXSTools::setMinimum(1.0);
    IsGISAXSTools::setMaximum(1e10);
    IsGISAXSTools::drawOutputDataInPad(*mp_real_data, "COLZ", "real_data");
    c1->Update();

    const double minima[]={0.003, 0.003};
    const double maxima[]={0.03, 0.03};
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(*mp_real_data, minima, maxima);
    mp_real_data->setMask(*mask1);

    c1->cd(2);
    gPad->SetLogz();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    IsGISAXSTools::drawOutputDataInPad(*mp_real_data, "COLZ", "real_data");
    c1->Update();

    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_height",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_radius",  4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_half_side", 4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_prism3_height",    4*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
    m_fitSuite->addFitParameter("*SampleBuilder/m_cylinder_ratio", 0.2, 0.1, AttLimits::fixed());
//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e10, 1, AttLimits::limited(0.1*1e10, 2.*1e10));
//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e10, 1, AttLimits::limited(1e8, 1e12));

    ChiSquaredModule chiModule;
    //chiModule.setChiSquaredFunction( SquaredFunctionDefault() );
//    chiModule.setChiSquaredFunction( SquaredFunctionWhichOnlyWorks() ); // it works only with resolution function, without it fit doesn't converge
    //chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() );
    chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer(1.0,0) );


    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data, chiModule);

    m_fitSuite->runFit();

}



/* ************************************************************************* */
// initializing simulation
/* ************************************************************************* */
void TestFittingModule2::initializeSimulation()
{
    if( !mp_sample_builder ) {
        throw NullPointerException("TestFittingModule2::initializeSimulation() -> No sample builder defined");
    }
    delete mp_simulation;
    mp_simulation = new Simulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    //mp_simulation->setBeamIntensity(1e10);
}


/* ************************************************************************* */
// initializing real data
/* ************************************************************************* */
void TestFittingModule2::initializeRealData()
{
    if( !mp_simulation ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No simulation of sample defined ");

    // generating "real" data
    mp_simulation->runSimulation();
   // mp_simulation->normalize();
    //m_fitSuite->getFitObjects()->setSimulationNormalize(true);
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_simulation->getOutputData());

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
TestFittingModule2::SampleBuilder::SampleBuilder()
    : m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
    , m_prism3_half_side(5.0*Units::nanometer)
    , m_prism3_height(5.0*Units::nanometer)
    , m_cylinder_ratio(0.2)
{
    init_parameters();
}


ISample *TestFittingModule2::SampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
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

void TestFittingModule2::SampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("m_cylinder_height", &m_cylinder_height);
    getParameterPool()->registerParameter("m_cylinder_radius", &m_cylinder_radius);
    getParameterPool()->registerParameter("m_prism3_half_side", &m_prism3_half_side);
    getParameterPool()->registerParameter("m_prism3_height", &m_prism3_height);
    getParameterPool()->registerParameter("m_cylinder_ratio", &m_cylinder_ratio);
}


