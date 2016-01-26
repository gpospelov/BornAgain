// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFumiliLMA.cpp
//! @brief     Implements class TestFumiliLMA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFumiliLMA.h"
#include "OutputData.h"
#include "IsGISAXSTools.h"
#include "MathFunctions.h"
#include "ChiSquaredModule.h"
#include "ISquaredFunction.h"

#include <iostream>
#include <cmath>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TH2D.h"
#include "TRandom.h"



/* ************************************************************************* */
//
/* ************************************************************************* */
TestFumiliLMA::TestFumiliLMA()
    : m_root_minimizer(0)
    , m_fcn(0)
    , m_func_object(0)
    , m_func(0)
    , m_chi_module(0)
    , m_real_data(0)
    , m_ndim(0)
    , m_sigma(0.01)
    , m_c1(0)
{
    // "simulation"
    m_ndim = 3;
    m_func_object = new SincXSincYFunctionObject();
    //m_func = new TF2("sincxy", m_func_object, -50.,50., -50.,50., m_ndim, "SincXSincYFunctionObject");
    m_func = new TF2("sincxy", m_func_object, -10.,10., -10.,10., 3, "SincXSincYFunctionObject");
    m_func->SetParameters(1.0, -2.0, -2.5); // parameters we have to find


    // chi module
    m_chi_module = new ChiSquaredModule();
    m_chi_module->setChiSquaredFunction(new SquaredFunctionGaussianError(m_sigma) );

    // "real" data
    OutputData<double> data;
    FillOutputDataFromFunction(data, m_func);
    m_real_data = IsGISAXSTools::createDataWithGaussianNoise(data, m_sigma);


}


TestFumiliLMA::~TestFumiliLMA()
{
    delete m_root_minimizer;
    delete m_fcn;
    //delete m_func_object;
    //delete m_func;
    delete m_chi_module;
    delete m_real_data;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestFumiliLMA::execute()
{
    std::cout << "TestFumiliLMA::execute() -> Hello world" << std::endl;
    //m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad" );
    //m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Fumili" ); // same as ("Fumili2")
    //m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("Fumili2"); // same as ("Minuit2", "Fumili" )
    //m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Fumili2" ); // same as ("Minuit2", "Migrad" ), i.e. Fumili2 is wrong key
    m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("Fumili"); //
    //m_root_minimizer = ROOT::Math::Factory::CreateMinimizer("GSLLMA");
    m_root_minimizer->SetVariable(0, "p0", 1.0, 0.01);
    m_root_minimizer->SetVariable(1, "p1", 0.0, 0.01);
    m_root_minimizer->SetVariable(2, "p2", 0.0, 0.01);
//    m_root_minimizer->SetVariable(0, "p0", 5.0, 0.01);
//    m_root_minimizer->SetVariable(1, "p1", -10.0, 0.01);
//    m_root_minimizer->SetVariable(2, "p2", 10.0, 0.01);


    m_c1 = new TCanvas("c1","c1", 1024, 768);
    m_c1->Divide(2,2);

    m_c1->cd(1);
    m_func->DrawCopy("SURF");

    TH2D *h2_real = IsGISAXSTools::getOutputDataTH2D(*m_real_data, "real_data");
    m_c1->cd(2);
    h2_real->DrawCopy("SURF");

    // fitting function
//    boost::function<double(const double *)> fcn = boost::bind(&TestFumiliLMA::functionToMinimize, this, _1);
//    m_fcn = new ROOT::Math::Functor(fcn, m_ndim);
//    m_root_minimizer->SetFunction(*m_fcn);

    // fitting function with gradient
    MyChi2Function *chi = new MyChi2Function(this);
    m_root_minimizer->SetFunction(*chi);

    m_root_minimizer->SetPrintLevel(3);
    m_root_minimizer->Minimize();
    m_root_minimizer->PrintResults();

    std::cout << "MyResults: " << m_root_minimizer->MinValue() << std::endl;
    for(size_t i=0; i<m_root_minimizer->NFree(); ++i) {
        std::cout << " i " << m_root_minimizer->X()[i]<< std::endl;
    }

//    ROOT::Fit::Fitter fitter;
//    const int Npar = 3;
//    double par0[Npar] = { 5.0, -10.0, 10.0};

//    // create before the parameter settings in order to fix or set range on them
//    fitter.Config().SetParamsSettings(3,par0);
//    fitter.Config().ParSettings(0).SetStepSize(0.01);
//    fitter.Config().ParSettings(1).SetStepSize(0.01);
//    fitter.Config().ParSettings(2).SetStepSize(0.01);

//    fitter.Config().MinimizerOptions().SetPrintLevel(3);
//    fitter.Config().MinimizerOptions().SetMinimizerType("GSLMultiFit");

//    MyChi2Function *chi = new MyChi2Function(this);
////    m_root_minimizer->SetFunction(*chi);
//    fitter.FitFCN(*chi);
//    ROOT::Fit::FitResult result = fitter.Result();
//    result.Print(std::cout);

}


/* ************************************************************************* */
//
/* ************************************************************************* */
double TestFumiliLMA::functionToMinimize(const double */*pars*/)
{
    throw NotImplementedException("Code is obsolete");
//    m_func->SetParameters(pars);
//    OutputData<double> simulated_data;
//    FillOutputDataFromFunction(simulated_data, m_func);
//    m_chi_module->setRealAndSimulatedData(*m_real_data, simulated_data);
//    double chi = m_chi_module->calculateChiSquared();

//    TH2D *h2_simul = IsGISAXSTools::getOutputDataTH2D(simulated_data, "simulated_data");
//    m_c1->cd(3);
//    h2_simul->DrawCopy("SURF");
//    delete h2_simul;
//    m_c1->Update();

//    return chi;
    return 0.0;
}


/* ************************************************************************* */
//
/* ************************************************************************* */
void TestFumiliLMA::FillOutputDataFromFunction(OutputData<double>& data, TF2 *fun, int nbinsx, int nbinsy)
{
    data.clear();
    data.addAxis("x", nbinsx, fun->GetXmin(), fun->GetXmax());
    data.addAxis("y", nbinsy, fun->GetYmin(), fun->GetYmax());
    data.setAllTo(0.0);

    OutputData<double>::iterator it=data.begin();
    const IAxis *xaxis = data.getAxis(0);
    const IAxis *yaxis = data.getAxis(1);
    while( it!= data.end() )
    {
        size_t index_x = data.getAxisBinIndex(it.getIndex(), 0);
        size_t index_y = data.getAxisBinIndex(it.getIndex(), 1);
        double x = (*xaxis)[index_x];
        double y = (*yaxis)[index_y];
        double value = fun->Eval(x,y);
        (*it)=value;
        ++it;
    }
}


double MyChi2Function::DataElement(const double *pars, unsigned int index, double *g ) const
{
    m_test->m_func->SetParameters(pars);
    std::cout << " DataElement() -> " << g << " " << index;
    for(int ipar=0; ipar<m_test->m_func->GetNpar(); ++ipar) std::cout << " p: (" << ipar << " " << pars[ipar] << ")";
    std::cout << "g:" << g << std::endl;
    const IAxis *xaxis = m_test->m_real_data->getAxis(0);
    const IAxis *yaxis = m_test->m_real_data->getAxis(1);
    size_t index_x = m_test->m_real_data->getAxisBinIndex(index, 0);
    size_t index_y = m_test->m_real_data->getAxisBinIndex(index, 1);
    double x = (*xaxis)[index_x];
    double y = (*yaxis)[index_y];
    double value = m_test->m_func->Eval(x,y);

    if(index==0) {
        m_test->m_c1->cd(3);
        m_test->m_func->Draw("SURF");
        m_test->m_c1->Update();
    }

    double real_value = (*m_test->m_real_data)[index];
//    std::cout << " DataElement " << i << " ix:" << index_x << " iy:" << index_y << " x:" << x << " y:" << y << " value:" << value << " real_val:" << real_value<< std::endl;
    double weight = 1./( m_test->m_sigma);
    //double weight = 1./(m_test->m_sigma * m_test->m_sigma);
    double residual = weight * ( real_value - value ) ;
    if (g != 0)    {
        std::cout << " gradient ! " << std::endl;
        m_test->m_func->SetParameters(pars);
        double xx[2];
        xx[0] = x;
        xx[1] = y;
        m_test->m_func->GradientPar( xx, g,1.E-9);
        // need to mutiply by -1*weight
        for (int ipar = 0; ipar < m_test->m_func->GetNpar(); ++ipar) {
            //g[ipar] *= -1 * weight;
            g[ipar] *= -1.0;
        }
    }
    return residual;
}





