// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingModule4.cpp
//! @brief     Implements class TestFittingModule4.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
#include "MaterialManager.h"
#include "IsGISAXSTools.h"
#include "ROOTMinimizer.h"
#include "Math/GeneticMinimizer.h"
#include "Math/GenAlgoOptions.h"


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
    // initializing data
    initializeSample();
    initializeSimulation();
    initializeRealData();
    m_fitSuite->addSimulationAndRealData(*mp_simulation, *mp_real_data);

    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );

    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLMultiFit") ); // LMA
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );


    ROOTMinimizer *root_minimizer = dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer());
    ROOT::Math::Minimizer *minim = root_minimizer->getROOTMinimizer();

    //minim->SetMaxFunctionCalls(100);
    //minim->SetMaxIterations(100);

    minim->SetPrintLevel(10);

//    ROOT::Math::MinimizerOptions options = minim->Options();
//    options.Print();
//    options.SetMaxIterations(5);
//    //minim->SetMaxFunctionCalls(100);

//    //ROOT::Math::GeneticMinimizer *genetic = dynamic_cast<ROOT::Math::GeneticMinimizer *>(minim);

//    ROOT::Math::IOptions *extra_options = options.ExtraOptions();
//    ROOT::Math::GenAlgoOptions *extra_genetic = dynamic_cast<ROOT::Math::GenAlgoOptions *>(extra_options);
//    if(extra_genetic) {
//        std::cout << "!!!" << std::endl;
//        extra_genetic->SetValue("Steps",20);
////        std::ostream ostr = std::cout;
////        extra_genetic->PrintAllDefault();
////        extra_genetic->Print(std::cout);
////        std::cout << extra_genetic->fConvCrit << std::endl;
//        options.Print();
//        std::cout << "---" << std::endl;
//    }

//    minim->SetOptions(options);
//    std::cout << "---" << std::endl;
//    minim->Options().Print();

    m_fitSuite->getMinimizer()->getOptions().setMaxIterations(5);
    m_fitSuite->getMinimizer()->getOptions().setValue("Steps",5);
//    m_fitSuite->getMinimizer()->getOptions().setValue("PopSize",1000);
    m_fitSuite->getMinimizer()->getOptions().setTolerance(0.1);


    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver(100) );
    //m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver() );

    m_fitSuite->runFit();
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
    mp_simulation = new Simulation(mp_options);
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
    delete mp_sample;

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", n_air);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    ParticleDecoration particle_decoration( new Particle(particle_material,
            new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));

    air_layer.setDecoration(particle_decoration);

    p_multi_layer->addLayer(air_layer);
    mp_sample = p_multi_layer;

    // defining parameters for minimization
    if( !m_fitSuite ) {
        throw NullPointerException("TestFittingModule::initializeSample() -> Error! No FitSuite is defined");
    }

    m_fitSuite->addFitParameter("*height", 2.*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(0.01, 30.) );
    m_fitSuite->addFitParameter("*radius", 20.*Units::nanometer, 0.06*Units::nanometer, AttLimits::limited(0.01, 30.) );
}


void TestFittingModule4::initializeRealData()
{
    if( !mp_simulation ) throw NullPointerException("TestFittingModule2::initializeRealData() -> Error! No simulation of sample defined ");

    mp_simulation->runSimulation();
    mp_simulation->normalize();
    m_fitSuite->getFitObjects()->setSimulationNormalize(true);
    delete mp_real_data;
    mp_real_data = IsGISAXSTools::createNoisyData(*mp_simulation->getOutputData());
}




