#include "TestIsGISAXS13.h"
#include "TestIsGISAXS5.h"

#include "Utils.h"
#include "OutputData.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "MaterialManager.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "FormFactorCylinder.h"
#include "StochasticSampledParameter.h"
#include "ParticleBuilder.h"
#include "LayerDecorator.h"
#include "Units.h"
#include "StochasticGaussian.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "GISASExperiment.h"
#include "DrawHelper.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "ResolutionFunction2DSimple.h"
#include "MathFunctions.h"
#include "OutputDataFunctions.h"
#include "ExperimentConstants.h"
#include "OutputDataIOFactory.h"
#include "IsGISAXSData.h"
#include "MinimizerScan.h"
#include "ROOTGSLSimAnMinimizer.h"
#include "MinimizerFactory.h"

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
    // reading info about two 1D scans defined in isgisaxs example
    IsGISAXSData::DataSet_t isgi_scans;
    //IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitexample.out", isgi_scans, IsGISAXSData::kData2fit);
    IsGISAXSData::read_datfile(getOutputPath()+"isgi_simulated_annealing.dat", isgi_scans);

    // creating fit suite
    m_fitSuite = new FitSuite();
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Scan") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Fumili") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiFit", "") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Fumili", "") );

    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("GSLSimAn") );
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Genetic") );

//    ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer()))->getROOTMinimizer();
//    minim->SetPrintLevel(4);
//    minim->SetMaxIterations(400);
//    minim->SetMaxFunctionCalls(1000);
//    minim->SetTolerance(0.1);
    //minim->SetPrecision(0.004);
//    minim->SetStrategy(1);
//    minim->SetPrecision(1.);


//    ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer()))->getROOTMinimizer();
//    if( !minim ) throw NullPointerException("TestToyExperiment::execute() -> Can't cast minimizer #1");
//    ROOT::Patch::GSLSimAnMinimizer *siman = dynamic_cast<ROOT::Patch::GSLSimAnMinimizer *>(minim);
//    if( !siman ) throw NullPointerException("TestToyExperiment::execute() -> Can't cast minimizer #2");
//    ROOT::Math::GSLSimAnParams &pars = siman->getSolver().Params();
//    siman->SetPrintLevel(2);
//    pars.n_tries = 100;
//    pars.iters_fixed_T = 10;
//    pars.step_size = 0.5;
//    pars.k = 1;
//    pars.t_initial = 50;
//    pars.mu = 1.05;
//    pars.t_min = 0.5;


//    m_fitSuite->setMinimizer( new MinimizerScan(20) );

    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver(10) );
    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver(50) );


    // Migrad
//    0    *Normalizer/scale                      1.333150e+05  7.316920e+04  6.781978e-01
//    1    *Normalizer/shift                      1.212894e+00  1.469154e+01  2.140932e-01
//    2    *SampleBuilder/particle_radius         5.011497e+00  3.715283e+00  9.739466e-01
//    3    *SampleBuilder/dispersion_radius       1.991729e-01  5.871223e-01  9.218360e-01
//    4    *SampleBuilder/height_aspect_ratio     9.937262e-01  8.881097e-01  9.706328e-01
//    5    *SampleBuilder/interf_distance         1.497518e+01  3.358856e+00  7.777025e-01
//      6    *SampleBuilder/interf_width            3.023607e+00  1.937917e+00  8.123996e-01

// Fumili
//    0                                           1.333427e+05  3.134186e+03  -1.000000e+00
//    1                                           2.105625e-01  1.615254e+01  -1.000000e+00
//    2                                           5.006825e+00  1.560112e-01  -1.000000e+00
//    3                                           1.993733e-01  1.461612e-02  -1.000000e+00
//    4                                           9.945538e-01  3.213714e-02  -1.000000e+00
//    5                                           1.497745e+01  1.211807e-01  -1.000000e+00
//    6                                           3.024541e+00  7.130375e-02  -1.000000e+00

//    6    *SampleBuilder/interf_width            3.023607e+00  1.937917e+00  8.123996e-01
//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1, AttLimits::limited(1e4, 2e5));
//    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.01, AttLimits::limited(0., 20.));
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius",  5*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(1., 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius",  0.2, 0.01, AttLimits::limited(0.01, 1.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio",  1.0, 0.01, AttLimits::limited(0.01, 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  15*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 50.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 10.) );

//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1e5, AttLimits::limited(1e4, 2e5));
//    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 10, AttLimits::limited(0., 20.));

    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1e3, AttLimits::limited(1e4, 2e5));
    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.1, AttLimits::limited(0., 20.));

//    m_fitSuite->addFitParameter("*Normalizer/scale", 1.333150e+05, 1e5, AttLimits::fixed());
//    m_fitSuite->addFitParameter("*Normalizer/shift", 1.212894e+00, 10, AttLimits::fixed());
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius", 4.0e+00*Units::nanometer, 0.04*Units::nanometer, AttLimits::limited(2.0, 8.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius",  1.991729e-01, 0.2, AttLimits::fixed() );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius",  0.2, 0.002, AttLimits::limited(0.01, 1.0) );
    //m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio",  9.937262e-01, 1.0, AttLimits::fixed() );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio",  0.8, 0.08, AttLimits::limited(0.5, 1.5) );

//    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  1.497518e+01*Units::nanometer, 15.*Units::nanometer, AttLimits::fixed() );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3.023607e+00*Units::nanometer, 3.0*Units::nanometer, AttLimits::fixed() );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  15*Units::nanometer, 0.015*Units::nanometer, AttLimits::limited(0.01, 50.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3*Units::nanometer, 0.03*Units::nanometer, AttLimits::limited(0.01, 10.) );


    // setting up fitSuite
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    //chiModule.setChiSquaredFunction(SquaredFunctionDefault());// isgisaxs uses epsion=0, which correspond to our SquaredFunctionDefault
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );
    //chiModule.setIntensityFunction( IntensityFunctionLog() );

    for(IsGISAXSData::DataSet_t::iterator it=isgi_scans.begin(); it!= isgi_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
    }

    m_fitSuite->runFit();

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


