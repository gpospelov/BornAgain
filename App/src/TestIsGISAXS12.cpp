// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS12.cpp
//! @brief     Implements class TestIsGISAXS12.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS12.h"
#include "DrawHelper.h"
#include "FitSuite.h"
#include "FitSuiteObserverFactory.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MinimizerTest.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "Particle.h"
#include "Distributions.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DGaussian.h"
#include "Units.h"
#include "Utils.h"
#include "FileSystem.h"

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


/* ************************************************************************* */
//
/* ************************************************************************* */
TestIsGISAXS12::TestIsGISAXS12()
    : IApplicationTest("TestIsGISAXS12")
    , m_simulation(0)
    , m_sample_builder(new TestSampleBuilder())
    , m_fitSuite(0)
{
    std::cout << "TestIsGISAXS12::TestIsGISAXS12() -> Info" << std::endl;
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-12/" ));
}


TestIsGISAXS12::~TestIsGISAXS12()
{
    delete m_simulation;
    delete m_fitSuite;
}


/* ************************************************************************* */
// execute
/* ************************************************************************* */
void TestIsGISAXS12::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();

    // run our standard isgisaxs comparison for given sample
    //run_isgisaxs_comparison();

    // plot IsGISAXS data and IsGISAXS fit results
    //plot_isgisaxs_fit_results();

    // run isgisaxs ex-12 style fit
   run_isgisaxs_fit();

    // additional tests for debugging
    //run_test_minimizer(); // run test minimizer
    //run_test_chimodule(); // run test
}



/* ************************************************************************* */
// standard ixgisaxs comparison
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_comparison()
{
    // run simulation for default sample parameters
    m_simulation->runSimulation();
    IntensityDataIOFactory::writeOutputData(*(m_simulation->getOutputData()), "this_fitconstraints.ima");

    // plotting results of comparison we/isgisaxs for the sample with default parameters
    std::string isgi_file(getOutputPath()+"isgi_fitconstraints_optimal.ima.gz");
    std::string this_file("this_fitconstraints.ima");

    // -------------
    // plot results
    // -------------
    OutputData<double> *isgi_data = IntensityDataIOFactory::readOutputData(isgi_file);
    OutputData<double> *our_data = IntensityDataIOFactory::readOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data,"TestIsGISAXS12_c1", "ex-12: Mixture of cylindrical particles with different size distribution");
    delete isgi_data;
    delete our_data;
}


/* ************************************************************************* */
// plot IsGISAXS data (*.dat file) and IsGISAXS fit results (*.out file)
/* ************************************************************************* */
void TestIsGISAXS12::plot_isgisaxs_fit_results()
{
    // reading two 1D scans defined in isgisaxs example (399 points/scan)
    IsGISAXSData::DataSet_t isgi_scans;
    IsGISAXSData::read_datfile(getOutputPath()+"isgi_fitconstraints.dat", isgi_scans);

    // reading isgisaxs scans which actually have been used for a fit together with fit results (100 points/scan)
    IsGISAXSData::DataSet_t isgi_scans_smoothed;
    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_scans_smoothed, IsGISAXSData::DATA_TO_FIT);
    IsGISAXSData::DataSet_t isgi_results;
    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_results, IsGISAXSData::SIM_RESULT);

    print_axes(isgi_scans);
    print_axes(isgi_scans_smoothed);
    print_axes(isgi_results);

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("c1_isgisaxs_data", "Looking on IsGISAXS data and fit results", 768, 1024);
    c1->Divide(2,3);

    // drawing real data with fine and coars granularity on top of each other
    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
    leg1->SetBorderSize(1);
    leg1->SetFillStyle(0);

    for(int i_set=0; i_set<(int)isgi_scans.size(); ++i_set) {
        c1->cd(1+i_set); gPad->SetLogy();
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_scans[i_set], "data");
        hdata->DrawCopy();
        if(i_set==0) leg1->AddEntry(hdata,"isgisaxs data fine","lp");
        TH1D *hdata_smoothed = IsGISAXSTools::getOutputDataScanHist(*isgi_scans_smoothed[i_set], "data_smoothed");
        hdata_smoothed->SetLineColor(kBlue);
        hdata_smoothed->DrawCopy("same");
        if(i_set==0) leg1->AddEntry(hdata_smoothed,"isgisaxs data","lp");
    }
    c1->cd(1); leg1->Draw();
    c1->cd(2); leg1->Draw();

    // drawing isgsaxs fit results on top of isgisaxs real data
    TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
    leg2->SetBorderSize(1);
    leg2->SetFillStyle(0);
    for(int i_set=0; i_set<(int)isgi_scans.size(); ++i_set) {
        c1->cd(3+i_set); gPad->SetLogy();
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "data");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        if(i_set==0) leg2->AddEntry(hdata,"isgisaxs results","lp");
        TH1D *hdata_smoothed = IsGISAXSTools::getOutputDataScanHist(*isgi_scans_smoothed[i_set], "data_smoothed");
        hdata_smoothed->SetLineColor(kBlue);
        hdata_smoothed->DrawCopy("same");
        if(i_set==0) leg2->AddEntry(hdata_smoothed,"isgisaxs data","lp");
    }
    c1->cd(3); leg2->Draw();
    c1->cd(4); leg2->Draw();

    // drawing ratio of isgisaxs data/results
    TLegend *leg3 = new TLegend(0.5,0.6,0.85,0.85);
    leg3->SetBorderSize(1);
    leg3->SetFillStyle(0);
    for(int i_set=0; i_set<(int)isgi_scans.size(); ++i_set) {
        c1->cd(5+i_set);
        *isgi_results[i_set] /= *isgi_scans_smoothed[i_set];
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "isgisaxs_results_data");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        if(i_set==0) leg3->AddEntry(hdata,"isgisaxs results/data","lp");
    }
    c1->cd(5); leg3->Draw();
    c1->cd(6); leg3->Draw();

    c1->Update();
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_fit()
{
    throw NotImplementedException("Obsolete code");

//    // reading 1D data scans defined in isgisaxs example
//    IsGISAXSData::DataSet_t isgi_scans;
//    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_scans, IsGISAXSData::DATA_TO_FIT);

//    // creating fit suite
//    m_fitSuite = new FitSuite();
//    m_fitSuite->setMinimizer( MinimizerFactory::createMinimizer("Minuit2", "Migrad") );
//    m_fitSuite->attachObserver( FitSuiteObserverFactory::createPrintObserver(10) );
//    m_fitSuite->attachObserver( FitSuiteObserverFactory::createDrawObserver(10) );

//    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1, AttLimits::limited(1e4, 2e5));
//    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.01, AttLimits::limited(1., 20.));

//    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability1",  0.4, 0.01, AttLimits::limited(0.01, 1.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(1., 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2, 0.01, AttLimits::limited(0.01, 1.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8, 0.01, AttLimits::limited(0.01, 10.) );

//    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability2",  0.6, 0.01, AttLimits::limited(0.01, 1.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(1., 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2, 0.01, AttLimits::limited(0.01, 1.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8, 0.01, AttLimits::limited(0.01, 10.) );

//    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 50.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 10.) );


//    // setting up fitSuite
//    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError(0.08) );
//    chiModule.setIntensityNormalizer( IntensityNormalizer() );

//    for(IsGISAXSData::DataSet_t::iterator it=isgi_scans.begin(); it!= isgi_scans.end(); ++it) {
//        m_fitSuite->addSimulationAndRealData(*m_simulation, *(*it), chiModule);
//    }

//    m_fitSuite->runFit();

//    // drawing results
//    TCanvas *c2 = new TCanvas("c2","BornAgain fit results",800,600);
//    c2->Divide(2,2);
//    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
//    leg1->SetBorderSize(1);
//    leg1->SetFillStyle(0);
//    for(size_t i_set=0; i_set<m_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd((int)i_set+1);
//        const FitObject *obj = m_fitSuite->getFitObjects()->getObject(i_set);
//        TH1D *hreal = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getRealData(),"BornAgain_real");
//        TH1D *hsimul = IsGISAXSTools::getOutputDataScanHist(*obj->getChiSquaredModule()->getSimulationData(),"BornAgain_simul");
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
//    for(size_t i_set=0; i_set<m_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd(3+1);
//        const FitObject *obj = m_fitSuite->getFitObjects()->getObject(i_set);
//        OutputData<double > *real = obj->getChiSquaredModule()->getRealData()->clone();
//        OutputData<double > *simul = obj->getChiSquaredModule()->getSimulationData()->clone();

//        c2->cd((int)(i_set+3));
//        *simul /= *real;
//        TH1D *hratio = IsGISAXSTools::getOutputDataScanHist(*simul,"BornAgain_real_simul_ratio");
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
// Various debugging
/* ************************************************************************* */

// run chi module test on isgisaxs data/result pair to check module numericaly
void TestIsGISAXS12::run_test_chimodule()
{
    throw NotImplementedException("Code is obsolete");

//    IsGISAXSData::DataSet_t isgi_scans;
//    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_scans, IsGISAXSData::DATA_TO_FIT);

//    IsGISAXSData::DataSet_t isgi_results;
//    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_results, IsGISAXSData::SIM_RESULT);

//    // setting up fitSuite
//    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError(0.08) );

//    IntensityNormalizer normalizer(1.31159E+05, -8.10009E-02);

//    double max_intensity(0);
//    for(int i=0; i<(int)isgi_results.size(); ++i) {
//        OutputData<double>::const_iterator cit = std::max_element(isgi_results[i]->begin(), isgi_results[i]->end());
//        max_intensity = std::max(max_intensity, *cit);
//    }
//    std::cout << "XXX " << max_intensity << std::endl;
//    normalizer.setMaximumIntensity(max_intensity);
////    chiModule.setOutputDataNormalizer( normalizer );

//    double chi_sum(0);
//    for(int i=0; i<(int)isgi_scans.size(); ++i) {
//        chiModule.setRealAndSimulatedData(*isgi_scans[i], *isgi_results[i]);
//        std::cout << " AAA " << isgi_scans.size()*isgi_results[i]->getAllocatedSize() - 12 << std::endl;
//        chiModule.setNdegreeOfFreedom((int)(isgi_scans.size()*isgi_results[i]->getAllocatedSize()) - 12);
//        double chi = 0.5*0.5*chiModule.calculateChiSquared();
//        chi_sum += chi;
//        std::cout << "chi : " << chi << " chi_sum:" << chi_sum << std::endl;
//    }
//    std::cout << "chi_sum " << chi_sum << std::endl;

//    return;
}


// run test minimizer to check the whole chain
void TestIsGISAXS12::run_test_minimizer()
{
//    // reading isgisaxs real data
//    IsGISAXSData::DataSet_t isgi_scans_smoothed;
//    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_scans_smoothed, IsGISAXSData::DATA_TO_FIT);
//    // isgisaxs fit results
//    IsGISAXSData::DataSet_t isgi_results;
//    IsGISAXSData::read_outfile(getOutputPath()+"isgi_fitconstraints.out", isgi_results, IsGISAXSData::SIM_RESULT);

//    // Putting parameters found by isgisaxs into our sample and run FitSuite once with the help of TestMinimizer to see if
//    // our simulation produces numerically same results

//    m_fitSuite = new FitSuite();
//    m_fitSuite->setMinimizer( new MinimizerTest() );

//    m_fitSuite->addFitParameter("*Normalizer/scale", 1.31159E+05, 100, AttLimits::limited(1e4, 2e5));
//    m_fitSuite->addFitParameter("*Normalizer/shift", -8.10009E-02, 1, AttLimits::limited(-10., 20.));

//    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability1",  5.34055E-01, 0.1, AttLimits::limited(0.01, 1.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4.90801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  1.90651E-01, 0.1, AttLimits::limited(0.01, 1.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  1.00193E+00, 0.1, AttLimits::limited(0.01, 10.) );

//    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability2",  4.70783E-01, 0.1, AttLimits::limited(0.01, 1.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  5.16801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  2.03908E-01, 0.1, AttLimits::limited(0.01, 1.) );
//    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  9.77402E-01, 0.1, AttLimits::limited(0.01, 10.) );

//    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  1.49681E+01, 1*Units::nanometer, AttLimits::limited(0.01, 50.0) );
//    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3.03315E+00, 1*Units::nanometer, AttLimits::limited(0.01, 10.) );

//    // setting up fitSuite
//    ChiSquaredModule chiModule;
//    chiModule.setChiSquaredFunction( new SquaredFunctionSystematicError(0.08) );
//    chiModule.setIntensityNormalizer( IntensityNormalizer() );
//    for(IsGISAXSData::DataSet_t::iterator it=isgi_scans_smoothed.begin(); it!= isgi_scans_smoothed.end(); ++it) {
//        m_fitSuite->addSimulationAndRealData(*m_simulation, *(*it), chiModule);
//    }
//    m_fitSuite->runFit();

//    TCanvas *c1 = new TCanvas("c1_test_minimizer","TestMinimizer", 800, 600);
//    c1->Divide(2,2);

//    // drawing BornAgain simul on top of isgisaxs simul
//    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
//    leg1->SetBorderSize(1);
//    leg1->SetFillStyle(0);
//    for(int i_set=0; i_set<(int)isgi_results.size(); ++i_set) {
//        c1->cd(1+i_set);
//        gPad->SetLogy();
//        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "data");
//        hdata->SetLineColor(kRed);
//        hdata->DrawCopy();
//        const OutputData<double > *data = m_fitSuite->getFitObjects()->getObject(i_set)->getChiSquaredModule()->getSimulationData();
//        TH1D *simul_data = IsGISAXSTools::getOutputDataScanHist(*data, "data_from_module");
//        simul_data->SetLineColor(kBlue);
//        simul_data->DrawCopy("same");

//        if(i_set==0) leg1->AddEntry(hdata,"isgisaxs results","lp");
//        if(i_set==0) leg1->AddEntry(simul_data,"BornAgain simul","lp");
//    }
//    c1->cd(1); leg1->Draw();
//    c1->cd(2); leg1->Draw();

//    TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
//    leg2->SetBorderSize(1);
//    leg2->SetFillStyle(0);
//    for(int i_set=0; i_set<(int)isgi_results.size(); ++i_set) {
//        c1->cd(3+i_set);
//        OutputData<double > *data = m_fitSuite->getFitObjects()->getObject(i_set)->getChiSquaredModule()->getSimulationData()->clone();
//        *data /= *isgi_results[i_set];
//        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*data, "BornAgain_isgisaxs_simul");
//        hdata->SetLineColor(kRed);
//        hdata->DrawCopy();
//        delete data;
//        if(i_set==0) leg2->AddEntry(hdata,"BornAgain/isgisaxs simul","lp");
//    }
//    c1->cd(3); leg1->Draw();
//    c1->cd(4); leg1->Draw();
}


/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestIsGISAXS12::initializeSimulation()
{
    delete m_simulation;
    m_simulation = new GISASSimulation(mp_options);
    m_simulation->setSampleBuilder(m_sample_builder);
    m_simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    m_simulation->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
}


/* ************************************************************************* */
// Sample Builder
/* ************************************************************************* */
TestIsGISAXS12::TestSampleBuilder::TestSampleBuilder()
// optimal parameters as found by isgisaxs
  : m_particle_probability1(5.34055E-01)
  , m_particle_radius1(4.90801E+00*Units::nanometer)
  , m_dispersion_radius1(1.90651E-01)
  , m_height_aspect_ratio1(1.00193E+00)
  , m_particle_probability2(4.70783E-01)
  , m_particle_radius2(5.16801E+00*Units::nanometer)
  , m_dispersion_radius2(2.03908E-01)
  , m_height_aspect_ratio2(9.77402E-01)
  , m_interf_distance(1.49681E+01*Units::nanometer)
  , m_interf_width(3.03315E+00*Units::nanometer)

{
    init_parameters();
}


void TestIsGISAXS12::TestSampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("particle_probability1", &m_particle_probability1);
    registerParameter("particle_radius1", &m_particle_radius1);
    registerParameter("dispersion_radius1", &m_dispersion_radius1);
    registerParameter("height_aspect_ratio1", &m_height_aspect_ratio1);
    registerParameter("particle_probability2", &m_particle_probability2);
    registerParameter("particle_radius2", &m_particle_radius2);
    registerParameter("dispersion_radius2", &m_dispersion_radius2);
    registerParameter("height_aspect_ratio2", &m_height_aspect_ratio2);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}


ISample *TestIsGISAXS12::TestSampleBuilder::buildSample() const
{
//    MultiLayer *p_multi_layer = new MultiLayer();

//    complex_t n_particle(1.0-6e-4, 2e-8);
//    HomogeneousMaterial air_material("Air", 0.0, 0.0);
//    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
//    HomogeneousMaterial particle_material("Particle", n_particle);

//    Layer air_layer(air_material);

//    // preparing nano particles prototypes for seeding layer's particle_layout
//    double particle_probability1 = m_particle_probability1;
////    double particle_probability2 = 1. - m_particle_probability1;
//    double particle_probability2 = m_particle_probability2;

//    double radius1 = m_particle_radius1;
//    double radius2 = m_particle_radius2;
//    double height1 = m_height_aspect_ratio1*radius1;
//    double height2 = m_height_aspect_ratio2*radius2;
//    FormFactorCylinder p_ff_cylinder1(radius1, height1);
//    Particle cylinder1(particle_material, p_ff_cylinder1 );

//    FormFactorCylinder p_ff_cylinder2(radius2, height2);
//    Particle cylinder2(particle_material, p_ff_cylinder2 );

//    // radius of nanoparticles will be sampled with gaussian probability
//    int nbins=20;
//    double sigma1 = radius1*m_dispersion_radius1;
//    double sigma2 = radius2*m_dispersion_radius2;
//    int nfwhm(2); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
//    DistributionGaussian gauss1(radius1, sigma1);
//    DistributionGaussian gauss2(radius2, sigma2);

//    ParticleLayout particle_layout;
//    InterferenceFunctionRadialParaCrystal *p_interference_function =
//            new InterferenceFunctionRadialParaCrystal(m_interf_distance,
//                    1e7*Units::nanometer); // peak_distance, corr_length
//    FTDistribution1DGauss pdf(m_interf_width);
//    p_interference_function->setProbabilityDistribution(pdf);
//    particle_layout.addInterferenceFunction(p_interference_function);

//    // building nano particles
//    ParameterDistribution par_distr1("*/radius", gauss1, nbins, nfwhm);
//    ParticleDistribution particle_collection1(cylinder1, par_distr1);
//    particle_layout.addParticle(particle_collection1, particle_probability1);
//    ParameterDistribution par_distr2("*/radius", gauss2, nbins, nfwhm);
//    ParticleDistribution particle_collection2(cylinder2, par_distr2);
//    particle_layout.addParticle(particle_collection2, particle_probability2);

//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);

//    Layer substrate_layer;
//    substrate_layer.setMaterial(substrate_material);
//    p_multi_layer->addLayer(substrate_layer);

//    return p_multi_layer;
    throw Exceptions::NotImplementedException("Cleanup the code!");

}


void TestIsGISAXS12::print_axes(IsGISAXSData::DataSet_t& data)
{
    for(size_t i_set=0; i_set<data.size(); ++i_set) {
        std::cout << "scan #" << i_set << "  ";
        for(size_t i_axis=0; i_axis<data[(int)i_set]->getRank(); ++i_axis) {
            const IAxis *axis = data[(int)i_set]->getAxis(i_axis);
            std::cout << "( " << axis->getName() << ", " << axis->getSize() << ", " << axis->getMin() << ", " << axis->getMax() << " )   ";
        }
        std::cout << std::endl;
    }
}






