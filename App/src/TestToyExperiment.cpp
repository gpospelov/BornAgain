#include "TestToyExperiment.h"
#include "Exceptions.h"
#include "IsGISAXSTools.h"
#include "FitSuite.h"
#include "FitSuiteHelper.h"
#include "ROOTMinimizer.h"
#include <iostream>


/* ************************************************************************* */
//
/* ************************************************************************* */
void ToyExperiment::runSimulation()
{
    if( !m_func ) throw NullPointerException("ToyExperiment::runSimulation() -> Error! No function is defined.");
    const std::string s_phi_f("phi_f");
    const std::string s_alpha_f("alpha_f");

    m_func->SetParameters(&pars[0]);
    m_intensity_map.setAllTo(0.0);
    OutputData<double>::iterator it = m_intensity_map.begin();
    while( it!= m_intensity_map.end() ) {
        double phi_f = m_intensity_map.getValueOfAxis(s_phi_f, it.getIndex());
        double alpha_f = m_intensity_map.getValueOfAxis(s_alpha_f, it.getIndex());
        double value = m_func->Eval(phi_f, alpha_f);
        (*it) = value;
        ++it;
    }
}

void ToyExperiment::runSimulationElement(size_t index)
{
    if( !m_func ) throw NullPointerException("ToyExperiment::runSimulation() -> Error! No function is defined.");

    m_func->SetParameters(&pars[0]);
    const std::string s_phi_f("phi_f");
    const std::string s_alpha_f("alpha_f");
    double phi_f = m_intensity_map.getValueOfAxis(s_phi_f, index);
    double alpha_f = m_intensity_map.getValueOfAxis(s_alpha_f, index);
    double value = m_func->Eval(phi_f, alpha_f);
    m_intensity_map[index] = value;
}


void ToyExperiment::init_parameters()
{
    getParameterPool()->clear();
    for(size_t i=0; i<pars.size(); ++i) {
        std::ostringstream ostr;
        ostr << "par"<< i;
        getParameterPool()->registerParameter(ostr.str(), &pars[i]);
    }
}


/* ************************************************************************* */
//
/* ************************************************************************* */
TestToyExperiment::TestToyExperiment()
    : m_func_object(0)
    , m_func(0)
    , m_sigma_noise(0)
    , m_experiment(0)
    , m_real_data(0)
    , m_fitSuite(0)
{
    m_sigma_noise = 0.01;
    m_func_object = new SincXSincYFunctionObject();
//    m_func = new TF2("sincxy", m_func_object, -5.,5., -5.,5., 3, "SincXSincYFunctionObject");
    m_func = new TF2("sincxy", m_func_object, -10.,10., -10.,10., 3, "SincXSincYFunctionObject");
    //m_func->SetParameters(1.0, 1.0, 0.5); // parameters we have to find
}


TestToyExperiment::~TestToyExperiment()
{
    delete m_func_object;
    delete m_func;
    delete m_experiment;
    delete m_real_data;
    delete m_fitSuite;
}


void TestToyExperiment::execute()
{
    std::cout << "TestToyExperiment()::execute() -> Hello World!"   << std::endl;

    initializeExperimentAndRealData();

    // setting up fitSuite
    FitSuite *m_fitSuite = new FitSuite();
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiFit") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint() );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw() );

    m_fitSuite->addFitParameter("*/par0",  1.0, 0.01);
    m_fitSuite->addFitParameter("*/par1",  0.0, 0.01);
    m_fitSuite->addFitParameter("*/par2",  0.0, 0.01);

    ChiSquaredModule chi_module;
    chi_module.setChiSquaredFunction(SquaredFunctionWithGaussianError(m_sigma_noise) );
    m_fitSuite->addExperimentAndRealData(*m_experiment, *m_real_data, chi_module);
//    m_fitSuite->addExperimentAndRealData(*m_experiment, *m_real_data);
    m_fitSuite->runFit();

}



/* ************************************************************************* */
//
/* ************************************************************************* */
void TestToyExperiment::initializeExperimentAndRealData()
{
    delete m_experiment;
    m_experiment = new ToyExperiment(m_func);

    OutputData<double > tmp;
    tmp.addAxis("phi_f", 100, m_func->GetXmin(), m_func->GetXmax());
    tmp.addAxis("alpha_f", 100, m_func->GetYmin(), m_func->GetYmax());
    m_experiment->setDetectorParameters(tmp);

    // generating real data
    delete m_real_data;
    m_experiment->setParameter(0, 1.0);
    m_experiment->setParameter(1, -2.0);
    m_experiment->setParameter(2, -2.5);
//    m_experiment->setParameter(0, 2.0);
//    m_experiment->setParameter(1, 1.0);
//    m_experiment->setParameter(2, 0.5);
    m_experiment->runSimulation();
    m_real_data = IsGISAXSTools::createDataWithGaussianNoise(*m_experiment->getOutputData(), m_sigma_noise);
}


