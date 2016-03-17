// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS13.cpp
//! @brief     Implements class TestIsGISAXS13.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS13.h"
#include "DrawHelper.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "GISASSimulation.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MinimizerScan.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DGaussian.h"
#include "TestIsGISAXS5.h"
#include "Units.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TROOT.h"
#include "TLegend.h"
#include "FileSystem.h"


TestIsGISAXS13::TestIsGISAXS13()
: IApplicationTest("TestIsGISAXS13")
, mp_simulation(0)
, mp_sample_builder(new TestIsGISAXS5::SampleBuilder())
, mp_fitSuite(0)
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-13/" ));
}


void TestIsGISAXS13::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();

    // run isgisaxs ex-13 style fit
    run_isgisaxs_fit();
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS13::run_isgisaxs_fit()
{
    throw NotImplementedException("Obsolete code");

//    mp_fitSuite = new FitSuite();

//    // minimizer
//    mp_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLLMA") ); // LMA
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
//    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );

//    // observers
//    mp_fitSuite->attachObserver( FitSuiteObserverFactory::
//            createPrintObserver(10) );
//    mp_fitSuite->attachObserver( FitSuiteObserverFactory::
//            createDrawObserver(50) );

//    // fit parameters
//    mp_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1e3,
//            AttLimits::limited(1e4, 2e5));
//    mp_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.1,
//            AttLimits::limited(0., 20.));
//    mp_fitSuite->addFitParameter("*SampleBuilder/particle_radius",
//            4.0e+00*Units::nanometer, 0.04*Units::nanometer,
//            AttLimits::limited(2.0, 8.0) );
//    mp_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius",
//            0.2, 0.002, AttLimits::limited(0.01, 1.0) );
//    mp_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio",
//            0.8, 0.08, AttLimits::limited(0.5, 1.5) );
//    mp_fitSuite->addFitParameter("*SampleBuilder/interf_distance",
//            15*Units::nanometer, 0.015*Units::nanometer,
//            AttLimits::limited(0.01, 50.0) );
//    mp_fitSuite->addFitParameter("*SampleBuilder/interf_width",
//            3*Units::nanometer, 0.03*Units::nanometer,
//            AttLimits::limited(0.01, 10.) );

//    // reading 1D data scans defined in isgisaxs example
//    IsGISAXSData::DataSet_t isgi_scans;
//    IsGISAXSData::read_datfile(getOutputPath()+"isgi_simulated_annealing.dat",
//            isgi_scans);

//    // chi squared module
//    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError(0.08) );
//    chiModule.setIntensityNormalizer( IntensityNormalizer() );
//    //chiModule.setIntensityFunction( IntensityFunctionLog() );
//    for(IsGISAXSData::DataSet_t::iterator it=isgi_scans.begin();
//            it!= isgi_scans.end(); ++it) {
//        mp_fitSuite->addSimulationAndRealData(*mp_simulation, *(*it),
//                chiModule);
//    }

//    mp_fitSuite->runFit();

//    // Scan Minimizer
////    TCanvas *c1 = new TCanvas("c1","c1",1024,768);
////    c1->cd();
////    MinimizerScan *minim = dynamic_cast<MinimizerScan *>(m_fitSuite->getMinimizer());
////    std::cout << "Results " << minim->getMinValue() << std::endl;
////    for(size_t i=0; i<minim->getNumberOfVariables(); ++i) {
////        std::cout << i << " " << minim->getValueOfVariableAtMinimum(i) << std::endl;
////    }
////    const OutputData<double> *data = minim->getOutputData();
////    if(data->getNdimensions()==1) {
////        TH1 * h1 = IsGISAXSTools::getOutputDataTH123D(*data,"hist");
////        h1->Draw();
////        gPad->SetLogy();
////    } else {
////        TH2D *hist = IsGISAXSTools::getOutputDataTH2D( *data, "hist");
////        hist->Draw("colz");
////        gPad->SetLogz();
////    }

//    // drawing results
//    TCanvas *c2 = new TCanvas("c2","BornAgain fit results",800,600);
//    c2->Divide(2,2);
//    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
//    leg1->SetBorderSize(1);
//    leg1->SetFillStyle(0);
//    for(size_t i_set=0; i_set<mp_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd((int)i_set+1);
//        const FitObject *obj = mp_fitSuite->getFitObjects()->getObject(i_set);
//        TH1D *hreal = IsGISAXSTools::getOutputDataScanHist(*obj->
//                getChiSquaredModule()->getRealData(),"BornAgain_real");
//        TH1D *hsimul = IsGISAXSTools::getOutputDataScanHist(*obj->
//                getChiSquaredModule()->getSimulationData(),"BornAgain_simul");
//        hreal->SetLineColor(kBlue);
//        gPad->SetLogy();
//        hreal->DrawCopy();
//        hsimul->DrawCopy("same");
//        if(i_set==0) {
//            leg1->AddEntry(hreal,"BornAgain data","lp");
//            leg1->AddEntry(hsimul,"BornAgain simul","lp");
//        }
//    }
//    c2->cd(1); leg1->Draw();
//    c2->cd(2); leg1->Draw();

//    // drawing ratio
//    TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
//    leg2->SetBorderSize(1);
//    leg2->SetFillStyle(0);
//    for(size_t i_set=0; i_set<mp_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd(3+1);
//        const FitObject *obj = mp_fitSuite->getFitObjects()->getObject(i_set);
//        OutputData<double > *real = obj->getChiSquaredModule()->
//                getRealData()->clone();
//        OutputData<double > *simul = obj->getChiSquaredModule()->
//                getSimulationData()->clone();

//        c2->cd((int)(i_set+3));
//        *simul /= *real;
//        TH1D *hratio = IsGISAXSTools::getOutputDataScanHist(*simul,
//                "BornAgain_real_simul_ratio");
//        hratio->DrawCopy();
//        if(i_set==0) {
//            leg2->AddEntry(hratio,"BornAgain simul/real","lp");
//        }
//        delete real;
//        delete simul;
//    }
//    c2->cd(3); leg2->Draw();
//    c2->cd(4); leg2->Draw();

//    c2->Update();
}


/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestIsGISAXS13::initializeSimulation()
{
    delete mp_simulation;
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(
            100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(1.0*Units::angstrom,
            0.2*Units::degree, 0.0*Units::degree);
}




