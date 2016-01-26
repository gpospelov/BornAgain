// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingModule1.cpp
//! @brief     Implements class TestFittingModule1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFittingModule1.h"
#include "AttLimits.h"
#include "DrawHelper.h"
#include "Exceptions.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactors.h"
#include "Simulation.h"
#include "ISquaredFunction.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSTools.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DGaussian.h"
#include "Units.h"
#include "ROOTMinimizer.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TPaveText.h"


TestFittingModule1::TestFittingModule1()
    : mp_real_data(0)
    , mp_simulated_data(0)
    , mp_simulation(0)
    , mp_sample(0)
    , m_fitSuite(0)
{
    m_fitSuite = new FitSuite();
}


TestFittingModule1::~TestFittingModule1()
{
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_simulation;
    delete mp_sample;
}


void TestFittingModule1::execute()
{
    // initializing data
    initializeSample1();
    initializeSimulation();
    initializeRealData();
    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

    //ROOTMinimizer *root_minimizer = dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer());
    //ROOT::Math::Minimizer *minim = root_minimizer->getROOTMinimizer();
    //std::cout << " tolerance: " << minim->Tolerance() << " precision:" << minim->Precision() << std::endl;
    //std::cout << " max_iterations: " << minim->MaxIterations() << " max_function_calls:" << minim->MaxFunctionCalls() << std::endl;

    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLLMA") ); // LMA
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );

    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createTreeObserver() );

    m_fitSuite->runFit();
}


/* ************************************************************************* */
// initializing simulation
/* ************************************************************************* */
void TestFittingModule1::initializeSimulation()
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
void TestFittingModule1::initializeSample1()
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
//                          5*Units::nanometer, 5*Units::nanometer));
//    ParticleLayout particle_layout(particle);
//    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);
//    mp_sample = p_multi_layer;

//    // defining parameters for minimization
//    if( !m_fitSuite ) {
//        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
//    }

////    m_fitSuite->addFitParameter("*height", 4.*Units::nanometer, 0.04*Units::nanometer, AttLimits::lowerLimited(0.01) );
////    m_fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*height", 4.*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(0.01, 10.) );
//    m_fitSuite->addFitParameter("*radius", 6.*Units::nanometer, 0.06*Units::nanometer, AttLimits::limited(0.01, 10.) );
}


/* ************************************************************************* */
// initialize sample: layer + substrate + nanoparticles, 4 parameters
/* ************************************************************************* */
void TestFittingModule1::initializeSample2()
{
    throw NotImplementedException("Code is obsolete");

//    delete mp_sample;

//    double cylinder_height = 5.0*Units::nanometer;
//    double cylinder_radius = 5.0*Units::nanometer;
//    double prism3_length = 10.0*Units::nanometer;
//    double prism3_height = 5.0*Units::nanometer;

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
//                           cylinder_radius, cylinder_height) );
//    Particle particle2(particle_material, FormFactorPrism3(
//                           prism3_length, prism3_height) );
//    particle_layout.addParticle(particle1, 0.2);
//    particle_layout.addParticle(particle2, 0.8);
//    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);

//    mp_sample = p_multi_layer;
//    // defining parameters for minimization
//    if( !m_fitSuite ) {
//        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
//    }

//    m_fitSuite->addFitParameter("*FormFactorCylinder/height", 12*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorCylinder/radius", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/length", 24*Units::nanometer, 2*Units::nanometer, AttLimits::lowerLimited(0.01) );
//    m_fitSuite->addFitParameter("*FormFactorPrism3/height", 2*Units::nanometer, 1*Units::nanometer, AttLimits::lowerLimited(0.01) );
}

/* ************************************************************************* */
// initializing real data
/* ************************************************************************* */
void TestFittingModule1::initializeRealData()
{
    if( !mp_simulation ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No simulation of sample defined ");

    mp_simulation->runSimulation();
    //mp_simulation->normalize();
    //m_fitSuite->getFitObjects()->setSimulationNormalize(true);
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_simulation->getOutputData());
}




