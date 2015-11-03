// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingModule4.cpp
//! @brief     Implements class TestFittingModule4.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFittingModule4.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include "Units.h"
#include "FitSuiteObserverFactory.h"
#include "HomogeneousMaterial.h"
#include "MultiLayer.h"
#include "FormFactors.h"
#include "Materials.h"
#include "IsGISAXSTools.h"
#include "ROOTMinimizer.h"
//#include "Math/GeneticMinimizer.h"
#include "Math/GenAlgoOptions.h"
#include "FitStrategyAdjustMinimizer.h"

TestFittingModule4::TestFittingModule4()
    : mp_real_data(0)
    , mp_simulated_data(0)
    , mp_simulation(0)
    , mp_sample(0)
    , m_fitSuite(0)
{
    m_fitSuite = new FitSuite();
}


TestFittingModule4::~TestFittingModule4()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_simulation;
    delete mp_sample;
}


void TestFittingModule4::execute()
{
    throw NotImplementedException("Code is obsolete");

//    // initializing data
//    initializeSample();
//    initializeSimulation();
//    initializeRealData();

//    ChiSquaredModule chiModule;
//    //chiModule.setChiSquaredFunction( SquaredFunctionSimError() );
//    chiModule.setChiSquaredFunction( new SquaredFunctionDefault() );

//    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data, chiModule);

//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLLMA") ); // LMA
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );


//    //m_fitSuite->getMinimizer()->getOptions().setPrintLevel(10);

//    // Genetic
////    m_fitSuite->getMinimizer()->getOptions().setMaxIterations(5);
////    m_fitSuite->getMinimizer()->getOptions().setValue("Steps",5);
////    m_fitSuite->getMinimizer()->getOptions().setValue("PopSize",100);
////    m_fitSuite->getMinimizer()->getOptions().setTolerance(100);

//    // GSLSimAn
////    m_fitSuite->getMinimizer()->getOptions().setValue("ntries",50);
////    m_fitSuite->getMinimizer()->getOptions().setValue("niters_fixed_t",5);
////    m_fitSuite->getMinimizer()->getOptions().setMaxIterations(5);

////    m_fitSuite->getMinimizer()->getOptions().setValue("Strategy",2);

//    //m_fitSuite->getMinimizer()->getOptions().print();


//    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver(100) );
//    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );

//    FitStrategyAdjustMinimizer *strategy1 = new FitStrategyAdjustMinimizer();
//    strategy1->setMinimizer(MinimizerFactory::createMinimizer("Genetic"));
//    strategy1->getMinimizer()->getOptions().setMaxIterations(5);
//    strategy1->getMinimizer()->getOptions().setValue("Steps",5);
//    m_fitSuite->addFitStrategy(strategy1);

//    FitStrategyAdjustMinimizer *strategy2 = new FitStrategyAdjustMinimizer();
//    strategy2->setMinimizer(MinimizerFactory::createMinimizer("Minuit2","Migrad"));
//    m_fitSuite->addFitStrategy(strategy2);

//    m_fitSuite->runFit();
}


/* ************************************************************************* */
// initializing simulation
/* ************************************************************************* */
void TestFittingModule4::initializeSimulation()
{
    if( !mp_sample ) {
        throw NullPointerException("TestFittingModule1::initializeSimulation() -> No sample defined");
    }
    delete mp_simulation;
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setSample(*mp_sample);
    mp_simulation->setDetectorParameters(100, 0.0*Units::degree,
            2.0*Units::degree,100 , 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    mp_simulation->setBeamIntensity(1e10);
}


/* ************************************************************************* */
// initialize sample: layer + nanoparticles, 2 parameters
/* ************************************************************************* */
void TestFittingModule4::initializeSample()
{
    throw NotImplementedException("Code is obsolete");

//    delete mp_sample;

//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    HomogeneousMaterial air_material("Air", n_air);
//    HomogeneousMaterial particle_material("Particle", n_particle);

//    Layer air_layer;
//    air_layer.setMaterial(air_material);
//    Particle particle(particle_material, FormFactorCylinder(
//                          5*Units::nanometer, 5*Units::nanometer) );
//    ParticleLayout particle_layout(particle);

//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);
//    mp_sample = p_multi_layer;

//    // defining parameters for minimization
//    if( !m_fitSuite ) {
//        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
//    }

//    m_fitSuite->addFitParameter("*height", 1.*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(0.01, 30.) );
//    m_fitSuite->addFitParameter("*radius", 20.*Units::nanometer, 0.06*Units::nanometer, AttLimits::limited(0.01, 30.) );
////    m_fitSuite->addFitParameter("*height", 6.*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(0.01, 30.) );
////    m_fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::limited(0.01, 30.) );
}


void TestFittingModule4::initializeRealData()
{
    if( !mp_simulation ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No simulation of sample defined ");

    mp_simulation->runSimulation();
    //mp_simulation->normalize();
    //m_fitSuite->getFitObjects()->setSimulationNormalize(true);
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_simulation->getOutputData());
}




