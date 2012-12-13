#include "TestIsGISAXS12.h"
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
#include "FitSuiteHelper.h"
#include "ResolutionFunction2DSimple.h"
#include "MathFunctions.h"
#include "ROOTMinimizer.h"
#include "OutputDataFunctions.h"

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
TestIsGISAXS12::TestIsGISAXS12() : IFunctionalTest("TestIsGISAXS12")
  , m_experiment(0)
  , m_sample_builder(0)
  , m_fitSuite(0)
  , m_isgi_fixed_alphaf(0)
  , m_isgi_fixed_phif(0)
{
    std::cout << "TestIsGISAXS12::TestIsGISAXS12() -> Info" << std::endl;
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/");
}


TestIsGISAXS12::~TestIsGISAXS12()
{
    delete m_experiment;
    delete m_sample_builder;
    delete m_fitSuite;
}


/* ************************************************************************* */
// execute
/* ************************************************************************* */
void TestIsGISAXS12::execute()
{

    // initializing experiment and sample builder
    initialiseExperiment();

    // run our standard isgisaxs comparison for given sample
//    run_isgisaxs_comparison();

    // plot isgisaxs data
//    plot_isgisaxs_data();

    // run test fit
//    run_test_minimizer();

    // run isgisaxs ex-12 style fit
   run_isgisaxs_fit();

//    run_test_chimodule();

}



/* ************************************************************************* */
// standard ixgisaxs comparison
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_comparison()
{
    // run simulation for default sample parameters
    m_experiment->runSimulation();
    IsGISAXSTools::writeOutputDataToFile(*(m_experiment->getOutputData()), m_data_path+"this_fitconstraints.ima");

    // plotting results of comparison we/isgisaxs for the sample with default parameters
    std::string isgi_file(m_data_path+"isgi_fitconstraints_optimal.ima");
    std::string this_file(m_data_path+"this_fitconstraints.ima");

    // -------------
    // plot results
    // -------------
    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_file);
    OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_file);

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS12_c1", "ex-12: Mixture of cylindrical particles with different size distribution");
    c1->Divide(2,2);

//    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
//    IsGISAXSTools::drawOutputDataInPad(*(m_experiment->getOutputData()), "CONT4 Z", "this");
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "this");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "isgi");

    // difference
    c1->cd(3);
    IsGISAXSTools::setMinimum(-0.0001);
    IsGISAXSTools::setMaximum(0.0001);
    IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

    // difference
    c1->cd(4);
    IsGISAXSTools::resetMinimumAndMaximum();
    IsGISAXSTools::setMinimum(1);
    IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

    delete isgi_data;
    delete our_data;

    c1->Update();
}


/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS12::run_isgisaxs_fit()
{
    // reading info about two 1D scans defined in isgisaxs example
    DataSet isgi_scans;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_scans);

    // creating fit suite
    m_fitSuite = new FitSuite();
    //m_fitSuite->setMinimizer( new ROOTMinimizer("Minuit2", "Migrad") );
    m_fitSuite->setMinimizer( new ROOTMinimizer("GSLMultiFit", "") );
    m_fitSuite->attachObserver( new FitSuiteObserverPrint(10) );
    m_fitSuite->attachObserver( new FitSuiteObserverDraw(50) );

//    ROOT::Math::Minimizer *minim = (dynamic_cast<ROOTMinimizer *>(m_fitSuite->getMinimizer()))->getROOTMinimizer();
//    minim->SetStrategy(1);
//    minim->SetPrecision(1.);

    m_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1, AttLimits::limited(1e4, 2e5));
    m_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.01, AttLimits::limited(1., 20.));

    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability1",  0.4, 0.01, AttLimits::limited(0.01, 1.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  0.2, 0.01, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  0.8, 0.01, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability2",  0.6, 0.01, AttLimits::limited(0.01, 1.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  4*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  0.2, 0.01, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  0.8, 0.01, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  12*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 50.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  6*Units::nanometer, 0.01*Units::nanometer, AttLimits::limited(0.01, 10.) );


//      m_fitSuite->addFitParameter("*Normalizer/scale", 1.31159E+05, 100, AttLimits::limited(1e4, 2e5));
//      m_fitSuite->addFitParameter("*Normalizer/shift", -8.10009E-02, 1, AttLimits::limited(-10., 20.));

//      m_fitSuite->addFitParameter("*SampleBuilder/particle_probability1",  5.34055E-01, 0.1, AttLimits::limited(0.01, 1.0) );
//      m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4.90801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
//      m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  1.90651E-01, 0.1, AttLimits::limited(0.01, 1.) );
//      m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  1.00193E+00, 0.1, AttLimits::limited(0.01, 10.) );

//      m_fitSuite->addFitParameter("*SampleBuilder/particle_probability2",  4.70783E-01, 0.1, AttLimits::limited(0.01, 1.0) );
//      m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  5.16801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
//      m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  2.03908E-01, 0.1, AttLimits::limited(0.01, 1.) );
//      m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  9.77402E-01, 0.1, AttLimits::limited(0.01, 10.) );

//      m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  1.49681E+01, 1*Units::nanometer, AttLimits::limited(0.01, 50.0) );
//      m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3.03315E+00, 1*Units::nanometer, AttLimits::limited(0.01, 10.) );

    // setting up fitSuite
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );

    for(DataSet::iterator it=isgi_scans.begin(); it!= isgi_scans.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
    }

    m_fitSuite->runFit();

    // drawing results
    TCanvas *c2 = new TCanvas("c2","GISASFW fit results",800,600);
    c2->Divide(2,2);
    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
    leg1->SetBorderSize(1);
    leg1->SetFillStyle(0);
    for(size_t i_set=0; i_set<m_fitSuite->getFitObjects()->size(); ++i_set) {
        c2->cd(i_set+1);
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

        c2->cd(i_set+3);
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
// run chi module test on isgisaxs data/result pair to check module numericaly
/* ************************************************************************* */
void TestIsGISAXS12::run_test_chimodule()
{
    DataSet isgi_scans;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_scans);

    DataSet isgi_results;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_results, true);

    // setting up fitSuite
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );

    OutputDataNormalizerScaleAndShift normalizer(1.31159E+05, -8.10009E-02);

    double max_intensity(0);
    for(size_t i=0; i<isgi_results.size(); ++i) {
        OutputData<double>::const_iterator cit = std::max_element(isgi_results[i]->begin(), isgi_results[i]->end());
        max_intensity = std::max(max_intensity, *cit);
    }
    std::cout << "XXX " << max_intensity << std::endl;
    normalizer.setMaximumIntensity(max_intensity);

    chiModule.setOutputDataNormalizer( normalizer );

    double chi_sum(0);
    for(size_t i=0; i<isgi_scans.size(); ++i) {
        chiModule.setRealAndSimulatedData(*isgi_scans[i], *isgi_results[i]);
        std::cout << " AAA " << isgi_scans.size()*isgi_results[i]->getAllocatedSize() - 12 << std::endl;
        chiModule.setNdegreeOfFreedom(isgi_scans.size()*isgi_results[i]->getAllocatedSize() - 12);
        double chi = 0.5*0.5*chiModule.calculateChiSquared();
        chi_sum += chi;
        std::cout << "chi : " << chi << " chi_sum:" << chi_sum << std::endl;
    }
    std::cout << "chi_sum " << chi_sum << std::endl;

    return;
}


/* ************************************************************************* */
// plot isgisaxs data together with test simulation
/* ************************************************************************* */
void TestIsGISAXS12::plot_isgisaxs_data()
{
    // reading two 1D scans defined in isgisaxs example (399 points/scan)
    DataSet isgi_scans;
    read_isgisaxs_datfile(m_data_path+"isgi_fitconstraints.dat", isgi_scans);

    // reading isgisaxs scans which actually have been used for a fit together with fit results (100 points/scan)
    DataSet isgi_scans_smoothed;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_scans_smoothed);
    DataSet isgi_results;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_results, true);

    print_axes(isgi_scans);
    print_axes(isgi_scans_smoothed);
    print_axes(isgi_results);

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("c1_isgisaxs_data", "Looking on IsGISAXS data and fit results", 768, 1024);
    c1->Divide(2,3);

    // drawing real data with fine and coars granularity on top of each other
    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
    leg1->SetBorderSize(1);
    leg1->SetFillStyle(0);

    for(size_t i_set=0; i_set<isgi_scans.size(); ++i_set) {
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
    for(size_t i_set=0; i_set<isgi_scans.size(); ++i_set) {
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
    for(size_t i_set=0; i_set<isgi_scans.size(); ++i_set) {
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
// run test minimizer to check the whole chain
/* ************************************************************************* */
void TestIsGISAXS12::run_test_minimizer()
{
    // reading isgisaxs real data
    DataSet isgi_scans_smoothed;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_scans_smoothed);
    // isgisaxs fit results
    DataSet isgi_results;
    read_isgisaxs_outfile(m_data_path+"isgi_fitconstraints.out", isgi_results, true);

    // Putting parameters found by isgisaxs into our sample and run FitSuite once with the help of TestMinimizer to see if
    // our simulation produces numerically same results

    m_fitSuite = new FitSuite();
    m_fitSuite->setMinimizer( new TestMinimizer() );

    m_fitSuite->addFitParameter("*Normalizer/scale", 1.31159E+05, 100, AttLimits::limited(1e4, 2e5));
    m_fitSuite->addFitParameter("*Normalizer/shift", -8.10009E-02, 1, AttLimits::limited(-10., 20.));

    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability1",  5.34055E-01, 0.1, AttLimits::limited(0.01, 1.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius1",  4.90801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius1",  1.90651E-01, 0.1, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio1",  1.00193E+00, 0.1, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/particle_probability2",  4.70783E-01, 0.1, AttLimits::limited(0.01, 1.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/particle_radius2",  5.16801E+00, 1*Units::nanometer, AttLimits::limited(1., 10.) );
    m_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius2",  2.03908E-01, 0.1, AttLimits::limited(0.01, 1.) );
    m_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio2",  9.77402E-01, 0.1, AttLimits::limited(0.01, 10.) );

    m_fitSuite->addFitParameter("*SampleBuilder/interf_distance",  1.49681E+01, 1*Units::nanometer, AttLimits::limited(0.01, 50.0) );
    m_fitSuite->addFitParameter("*SampleBuilder/interf_width",  3.03315E+00, 1*Units::nanometer, AttLimits::limited(0.01, 10.) );

    // setting up fitSuite
    ChiSquaredModule chiModule;
    chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
    chiModule.setOutputDataNormalizer( OutputDataNormalizerScaleAndShift() );
//    for(DataSet::iterator it=isgi_results.begin(); it!= isgi_results.end(); ++it) {
//        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
//    }
    for(DataSet::iterator it=isgi_scans_smoothed.begin(); it!= isgi_scans_smoothed.end(); ++it) {
        m_fitSuite->addExperimentAndRealData(*m_experiment, *(*it), chiModule);
    }
    m_fitSuite->runFit();

    TCanvas *c1 = new TCanvas("c1_test_minimizer","TestMinimizer", 800, 600);
    c1->Divide(2,2);

    // drawing GISASFW simul on top of isgisaxs simul
    TLegend *leg1 = new TLegend(0.5,0.6,0.85,0.85);
    leg1->SetBorderSize(1);
    leg1->SetFillStyle(0);
    for(size_t i_set=0; i_set<isgi_results.size(); ++i_set) {
        c1->cd(1+i_set);
        gPad->SetLogy();
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "data");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        const OutputData<double > *data = m_fitSuite->getFitObjects()->getObject(i_set)->getChiSquaredModule()->getSimulationData();
        TH1D *simul_data = IsGISAXSTools::getOutputDataScanHist(*data, "data_from_module");
        simul_data->SetLineColor(kBlue);
        simul_data->DrawCopy("same");

        if(i_set==0) leg1->AddEntry(hdata,"isgisaxs results","lp");
        if(i_set==0) leg1->AddEntry(simul_data,"gisasfw simul","lp");
    }
    c1->cd(1); leg1->Draw();
    c1->cd(2); leg1->Draw();

    TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
    leg2->SetBorderSize(1);
    leg2->SetFillStyle(0);
    for(size_t i_set=0; i_set<isgi_results.size(); ++i_set) {
        c1->cd(3+i_set);
        OutputData<double > *data = m_fitSuite->getFitObjects()->getObject(i_set)->getChiSquaredModule()->getSimulationData()->clone();
        *data /= *isgi_results[i_set];
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*data, "gisasfw_isgisaxs_simul");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        delete data;
        if(i_set==0) leg2->AddEntry(hdata,"gisasfw/isgisaxs simul","lp");
    }
    c1->cd(3); leg1->Draw();
    c1->cd(4); leg1->Draw();
}


/* ************************************************************************* */
// initialize experiment
/* ************************************************************************* */
void TestIsGISAXS12::initialiseExperiment()
{
    delete m_sample_builder;
    m_sample_builder = new TestSampleBuilder();
    delete m_experiment;
    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSampleBuilder(m_sample_builder);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
}




/* ************************************************************************* */
// read special isgisaxs *.dat file with data to fit
/* ************************************************************************* */
void TestIsGISAXS12::read_isgisaxs_datfile(const std::string &filename, DataSet &dataset)
{
    dataset.clear();

    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::vector<IsgiData > isgiScan;

    std::string sline;
    int n_dataset_line(0);
    while( std::getline(fin, sline))
    {
        //std::cout << sline << std::endl;
        std::string::size_type pos=sline.find("################################################");
        if( pos!= std::string::npos ) {
            n_dataset_line = 0; // it's a beginning of new data set ("cross-section" in isgisaxs terminology)
            if( !isgiScan.empty() ) {
                OutputData<double > *data = convert_isgi_scan(isgiScan);
                dataset.push_back(data);
                isgiScan.clear();
            }
        }
        if(n_dataset_line > 9) {
            // not a header, parsing records
            std::istringstream iss(sline.c_str());
            IsgiData isgiData;
            char ctmp;
            if ( !(iss >> ctmp >> isgiData.phif >> isgiData.alphaf >> isgiData.intensity) ) throw FormatErrorException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error!");
            iss >> isgiData.err; // column with errors can be absent in file, so no check for success here
            ctmp == 'T' ? isgiData.use_it = true : isgiData.use_it = false;
            isgiData.phif = std::asin(isgiData.phif); // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiData.alphaf = std::asin(isgiData.alphaf);  // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiScan.push_back(isgiData);
        }

        n_dataset_line++;
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

}


/* ************************************************************************* */
// read special isgisaxs *.out file with isgisaxs adjusted data and fit results
//
// if read_fit_results == false, then it loads isgisaxs data to fit
// if read_fit_results == true, then it loads isgisaxs fit results
/* ************************************************************************* */
void TestIsGISAXS12::read_isgisaxs_outfile(const std::string &filename, DataSet &dataset, bool read_fit_results)
{
    enum isgisaxs_keys_outfile {kSin_twotheta, kSin_alphaf, kQx, kQy, kQz, kGISAXS, kData2fit, kErrorbar, kIobs_Icalc, kFitted };

    dataset.clear();

    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::vector<IsgiData > isgiScan;

    std::string sline;
    while( std::getline(fin, sline))
    {
        std::string::size_type pos=sline.find("# Cut # =");
        if( pos!= std::string::npos ) {
            //std::cout << "beginning of one dataset " << isgiScan.size() << std::endl;
            if( !isgiScan.empty() ) {
                OutputData<double > *data = convert_isgi_scan(isgiScan);
                dataset.push_back(data);
                isgiScan.clear();
            }
        } else if (sline[0] != '#' && sline.size() >2){
            // not a header, parsing records
            std::istringstream iss(sline.c_str());
            IsgiData isgiData;

            vdouble1d_t buff;
            std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff));
            if( buff.size() != kFitted+1) {
                throw LogicErrorException("TestIsGISAXS12::read_isgisaxs_outfile -> Error! Line doesn't have enough double numbers. Not an *.out file? Line '"+sline+"'");
            }

            isgiData.phif = std::asin(buff[kSin_twotheta]);
            isgiData.alphaf = std::asin(buff[kSin_alphaf]);
            isgiData.intensity = buff[kData2fit];
            if( read_fit_results ) isgiData.intensity = buff[kGISAXS];

            isgiScan.push_back(isgiData);
        }
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

    if( !isgiScan.empty() ) {
        OutputData<double > *data = convert_isgi_scan(isgiScan);
        dataset.push_back(data);
        isgiScan.clear();
    }
}



/* ************************************************************************* */
// convert isgisaxs 1d scan to output data 2d object
/* ************************************************************************* */
OutputData<double> *TestIsGISAXS12::convert_isgi_scan(std::vector<IsgiData > &isgi_data)
{
    if(isgi_data.size() <2 ) throw LogicErrorException("TestIsGISAXS12::convert_isgi_scan() -> Error! Too short vector.");

//    // adjust data to get rid from the point with phi_f~0.0
//    std::vector<IsgiData > adjusted_data;
//    for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
//        if(isgi_data[i_point].phif > 0.001) {
//            adjusted_data.push_back(isgi_data[i_point]);
//        }
//    }

    // check if it is scan with fixed phi_f or with fixed alpha_f
    bool fixed_phif(true);
    bool fixed_alphaf(true);
    // if values of phif accross data points are chainging, then phif is not fixed
    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
        if( isgi_data[i_point].phif != isgi_data[i_point+1].phif ) {
            fixed_phif = false;
            break;
        }
    }
    // if values of alphaf accross data points are chainging, then alphaf is not fixed
    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
        if( isgi_data[i_point].alphaf != isgi_data[i_point+1].alphaf ) {
            fixed_alphaf = false;
            break;
        }
    }
    if(fixed_phif == fixed_alphaf) {
        throw LogicErrorException("TestIsGISAXS12::convert_isgi_scan() -> Error! Scan can't have both angle phif,alphaf fixed");
    }

    AxisDouble phi_axis("phi_f");
    AxisDouble alpha_axis("alpha_f");
    if( fixed_phif) {
        m_isgi_fixed_phif = isgi_data.back().phif;
        phi_axis.push_back(isgi_data.back().phif);
        std::cout << "fixed phi " << isgi_data.back().phif << std::endl;
        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
            alpha_axis.push_back(isgi_data[i_point].alphaf);
        }
    }else {
        m_isgi_fixed_alphaf = isgi_data.back().alphaf;
        alpha_axis.push_back(isgi_data.back().alphaf);
        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
            phi_axis.push_back(isgi_data[i_point].phif);
        }

    }
    OutputData<double > * data = new OutputData<double >;
    data->addAxis(phi_axis);
    data->addAxis(alpha_axis);
    data->setAllTo(0.0);
    OutputData<double>::iterator it = data->begin();
    int i_point(0);
    while( it!= data->end()) {
        (*it) = isgi_data[i_point].intensity;
        ++i_point;
        ++it;
    }

    return data;
}


/* ************************************************************************* */
//
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
    getParameterPool()->clear();
    getParameterPool()->registerParameter("particle_probability1", &m_particle_probability1);
    getParameterPool()->registerParameter("particle_radius1", &m_particle_radius1);
    getParameterPool()->registerParameter("dispersion_radius1", &m_dispersion_radius1);
    getParameterPool()->registerParameter("height_aspect_ratio1", &m_height_aspect_ratio1);
    getParameterPool()->registerParameter("particle_probability2", &m_particle_probability2);
    getParameterPool()->registerParameter("particle_radius2", &m_particle_radius2);
    getParameterPool()->registerParameter("dispersion_radius2", &m_dispersion_radius2);
    getParameterPool()->registerParameter("height_aspect_ratio2", &m_height_aspect_ratio2);
    getParameterPool()->registerParameter("interf_distance", &m_interf_distance);
    getParameterPool()->registerParameter("interf_width", &m_interf_width);
}


/* ************************************************************************* */
//
/* ************************************************************************* */
ISample *TestIsGISAXS12::TestSampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);

    Layer air_layer(air_material);

    // preparing nano particles prototypes for seeding layer's particle_decoration
    double particle_probability1 = m_particle_probability1;
//    double particle_probability2 = 1. - m_particle_probability1;
    double particle_probability2 = m_particle_probability2;

    double radius1 = m_particle_radius1;
    double radius2 = m_particle_radius2;
    double height1 = m_height_aspect_ratio1*radius1;
    double height2 = m_height_aspect_ratio2*radius2;
    FormFactorCylinder *p_ff_cylinder1 = new FormFactorCylinder(height1, radius1);
    Particle cylinder1(n_particle, p_ff_cylinder1 );

    FormFactorCylinder *p_ff_cylinder2 = new FormFactorCylinder(height2, radius2);
    Particle cylinder2(n_particle, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=20;
    double sigma1 = radius1*m_dispersion_radius1;
    double sigma2 = radius2*m_dispersion_radius2;
    int nfwhm(2); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticSampledParameter par1(StochasticDoubleGaussian(radius1, sigma1), nbins, nfwhm);
    StochasticSampledParameter par2(StochasticDoubleGaussian(radius2, sigma2), nbins, nfwhm);

    ParticleDecoration particle_decoration;
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(m_interf_distance, m_interf_width, 1e7*Units::nanometer); // peak_distance, width, corr_length
    particle_decoration.addInterferenceFunction(p_interference_function);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, particle_probability1);
    builder.plantParticles(particle_decoration);
    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, particle_probability2);
    builder.plantParticles(particle_decoration);

    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}


void TestIsGISAXS12::print_axes(DataSet &data)
{
    for(size_t i_set=0; i_set<data.size(); ++i_set) {
        std::cout << "scan #" << i_set << "  ";
        for(size_t i_axis=0; i_axis<data[i_set]->getNdimensions(); ++i_axis) {
            const AxisDouble *axis = data[i_set]->getAxis(i_axis);
            std::cout << "( " << axis->getName() << ", " << axis->getSize() << ", " << axis->getMin() << ", " << axis->getMax() << " )   ";
        }
        std::cout << std::endl;
    }
}




