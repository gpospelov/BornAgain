// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestToySimulation.cpp
//! @brief     Implements classes ToySimulation and TestToySimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Exceptions.h"
#include "FitSuite.h"
#include "BornAgainNamespace.h"
#include "FitSuiteObserverFactory.h"
#include "IsGISAXSTools.h"
#include "MinimizerFactory.h"
#include "TestToySimulation.h"

#include <iostream>

/* ************************************************************************* */
// implement class ToySimulation
/* ************************************************************************* */

void ToySimulation::runSimulation()
{
    if( !m_func )
        throw NullPointerException
            ("ToySimulation::runSimulation() -> "
             "Error! No function is defined.");
    const std::string s_phi_f(BornAgain::PHI_AXIS_NAME);
    const std::string s_alpha_f(BornAgain::ALPHA_AXIS_NAME);

    m_func->SetParameters(&pars[0]);
    m_intensity_map.setAllTo(0.0);
    OutputData<double>::iterator it = m_intensity_map.begin();
    while( it!= m_intensity_map.end() ) {
        double phi_f = m_intensity_map.getAxisValue(it.getIndex(), s_phi_f);
        double alpha_f = m_intensity_map.getAxisValue(it.getIndex(), s_alpha_f);
        double value = m_func->Eval(phi_f, alpha_f);
        (*it) = value;
        ++it;
    }
}

void ToySimulation::init_parameters()
{
    clearParameterPool();
    for(size_t i=0; i<pars.size(); ++i) {
        std::ostringstream ostr;
        ostr << "par"<< i;
        registerParameter(ostr.str(), &pars[i]);
    }
}

/* ************************************************************************* */
// implement class TestToySimulation
/* ************************************************************************* */

TestToySimulation::TestToySimulation()
    : m_func_object(0)
    , m_func(0)
    , m_sigma_noise(0.01)
    , m_simulation(0)
    , m_real_data(0)
    , m_fitSuite(0)
{
    m_func_object = new SincXSincYFunctionObject();
    m_func = new TF2("sincxy", m_func_object, -10.,10., -10.,10., 3, "SincXSincYFunctionObject");
}


TestToySimulation::~TestToySimulation()
{
    delete m_func_object;
    delete m_func;
    delete m_simulation;
    delete m_real_data;
    delete m_fitSuite;
}


void TestToySimulation::execute()
{
    throw NotImplementedException("Code is obsolete");

//    std::cout << "TestToySimulation()::execute() -> Hello World!"   << std::endl;
//    initializeSimulationAndRealData();

//    // setting up fitSuite
//    m_fitSuite = new FitSuite();

//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLLMA") );
//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
//    //m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
//    //m_fitSuite->getMinimizer()->setOptions("ntries=100:niters=10:step_size=1.0:k=1:t_initial=50.0:mu=1.05:t_min=0.1");

//    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver() );
////    m_fitSuite->attachObserver( ObserverFactory::createDrawObserver() );

////    m_fitSuite->addFitParameter("*/par0",  1.0, 0.01, AttLimits::limited(0.5, 1.5));
////    m_fitSuite->addFitParameter("*/par1",  0.0, 0.01, AttLimits::limited(0.0, 3.0));
////    m_fitSuite->addFitParameter("*/par2",  0.0, 0.01, AttLimits::limited(0.0, 3.0));
//    m_fitSuite->addFitParameter("*/par0",  1.0, 0.01, AttLimits::lowerLimited(0.0));
//    m_fitSuite->addFitParameter("*/par1",  0.0, 0.01, AttLimits::lowerLimited(0.0));
//    m_fitSuite->addFitParameter("*/par2",  0.0, 0.01, AttLimits::lowerLimited(0.0));

//    ChiSquaredModule chi_module;
//    chi_module.setChiSquaredFunction(new SquaredFunctionGaussianError(m_sigma_noise) );
//    m_fitSuite->addSimulationAndRealData(*m_simulation, *m_real_data, chi_module);
//    m_fitSuite->runFit();
}

void TestToySimulation::initializeSimulationAndRealData()
{
    delete m_simulation;
    m_simulation = new ToySimulation(m_func);

    OutputData<double > tmp;
    tmp.addAxis(BornAgain::PHI_AXIS_NAME, 100, m_func->GetXmin(), m_func->GetXmax());
    tmp.addAxis(BornAgain::ALPHA_AXIS_NAME, 100, m_func->GetYmin(), m_func->GetYmax());
    m_simulation->setDetectorParameters(tmp);

    // generating real data
    delete m_real_data;
    m_simulation->setParameter(0, 1.0);
    m_simulation->setParameter(1, 2.0);
    m_simulation->setParameter(2, 2.5);

    m_simulation->runSimulation();
    m_real_data = IsGISAXSTools::createDataWithGaussianNoise(*m_simulation->getOutputData(), m_sigma_noise);
}




