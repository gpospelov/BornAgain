#include "TestIsGISAXS13.h"
#include "DrawHelper.h"
#include "ExperimentConstants.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactorCylinder.h"
#include "GISASExperiment.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MinimizerScan.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "OutputDataIOFactory.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleDecoration.h"
#include "ResolutionFunction2DSimple.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
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


TestIsGISAXS13::TestIsGISAXS13()
    : IFunctionalTest("TestIsGISAXS13")
    , m_experiment(0)
    , m_sample_builder(0)

{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-13/");
}


void TestIsGISAXS13::execute()
{
    // initializing experiment and sample builder
    initialiseExperiment();

    // run isgisaxs ex-13 style fit
    run_isgisaxs_fit();
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS13::run_isgisaxs_fit()
{

    m_fitSuite = new FitSuite();

    // minimizer
    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Fumili") );
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Fumili") );
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLMultiFit") ); // LMA
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Genetic") );
    // m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Scan") );

    // observers
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver(10) );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver(50) );

    // fit parameters
    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1e3, AttLimits::limited(1e4, 2e5));
    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.1, AttLimits::limited(0., 20.));
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius", 4.0e+00*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(2.0, 8.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius",  0.2, 0.002, AttLimits::limited(0.01, 1.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio",  0.8, 0.08, AttLimits::limited(0.5, 1.5) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  15*Units::nanometer, 0.015*Units::nanometer, AttLimits::limited(0.01, 50.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3*Units::nanometer, 0.03*Units::nanometer, AttLimits::limited(0.01, 10.) );

    // reading 1D data scans defined in isgisaxs example
    IsGISAXSData::DataSet_t isgi_scans;
    IsGISAXSData::read_datfile(getOutputPath()+"isgi_simulated_annealing.dat", isgi_scans);

    // chi squared module
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );
    //chiModule.setIntensityFunction( IntensityFunctionLog() );
    for(IsGISAXSData::DataSet_t::iterator it=isgi_scans.begin(); it!= isgi_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
    }

    m_fitSuite->runFit();

    // Scan Minimizer
//    TCanvas *c1 = new TCanvas("c1","c1",1024,768);
//    c1->cd();
//    MinimizerScan *minim = dynamic_cast<MinimizerScan *>(m_fitSuite->getMinimizer());
//    std::cout << "Results " << minim->getMinValue() << std::endl;
//    for(size_t i=0; i<minim->getNumberOfVariables(); ++i) {
//        std::cout << i << " " << minim->getValueOfVariableAtMinimum(i) << std::endl;
//    }
//    const OutputData<double> *data = minim->getOutputData();
//    if(data->getNdimensions()==1) {
//        TH1 * h1 = IsGISAXSTools::getOutputDataTH123D(*data,"hist");
//        h1->Draw();
//        gPad->SetLogy();
//    } else {
//        TH2D *hist = IsGISAXSTools::getOutputDataTH2D( *data, "hist");
//        hist->Draw("colz");
//        gPad->SetLogz();
//    }

    // drawing results
    TCanvas *c2 = new TCanvas("c2","GISASFW fit results",800,600);
    c2->Divide(2,2);
    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
    leg1->SetBorderSize(1);
    leg1->SetFillStyle(0);
    for(size_t i_set=0; i_set<m_fitSuite->getFitObjects()->size(); ++i_set) {
        c2->cd((int)i_set+1);
        const FitObject *obj = m_fitSuite->getFitObjects()->getObject(i_set);
        TH1D *hreal = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getRealData(),"gisasfw_real");
        TH1D *hsimul = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getSimulationData(),"gisasfw_simul");
        hreal->SetLineColor(kBlue);
        gPad->SetLogy();
        hreal->DrawCopy();
        hsimul->DrawCopy("same");
        if(i_set==0) leg1->AddEntry(hreal,"GISASFW data","lp");
        if(i_set==0) leg1->AddEntry(hsimul,"GISASFW simul","lp");
    }
    c2->cd(1); leg1->Draw();
    c2->cd(2); leg1->Draw();

    // drawing ratio
    TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
    leg2->SetBorderSize(1);
    leg2->SetFillStyle(0);
    for(size_t i_set=0; i_set<m_fitSuite->getFitObjects()->size(); ++i_set) {
        c2->cd(3+1);
        const FitObject *obj = m_fitSuite->getFitObjects()->getObject(i_set);
        OutputData<double > *real = obj->getChiSquaredModule()->getRealData()->clone();
        OutputData<double > *simul = obj->getChiSquaredModule()->getSimulationData()->clone();

        c2->cd((int)(i_set+3));
        *simul /= *real;
        TH1D *hratio = IsGISAXSTools::getOutputDataScanHist(*simul,"gisasfw_real_simul_ratio");
        hratio->DrawCopy();
        if(i_set==0) {
            leg2->AddEntry(hratio,"GISASFW simul/real","lp");
        }
        delete real;
        delete simul;
    }
    c2->cd(3); leg2->Draw();
    c2->cd(4); leg2->Draw();

    c2->Update();
}


/* ************************************************************************* */
// initialize experiment
/* ************************************************************************* */
void TestIsGISAXS13::initialiseExperiment()
{
    delete m_sample_builder;
    m_sample_builder = new TestIsGISAXS5::SampleBuilder();
    delete m_experiment;
    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSampleBuilder(m_sample_builder);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
}


