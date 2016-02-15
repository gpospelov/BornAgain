// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS5.cpp
//! @brief     Implements class TestIsGISAXS5.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS5.h"
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

TestIsGISAXS5::TestIsGISAXS5()
    : IApplicationTest("TestIsGISAXS5"), mp_simulation(0), mp_sample_builder(new SampleBuilder()),
      mp_fitSuite(0)
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-5/"));
}

void TestIsGISAXS5::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();

    // run our standard isgisaxs comparison
    // run_isgisaxs_comparison();

    // plot IsGISAXS data and IsGISAXS fit results
    // plot_isgisaxs_fit_results();

    // run isgisaxs ex-5 style fit
    run_isgisaxs_fit();
}

/* ************************************************************************* */
// standard ixgisaxs comparison
/* ************************************************************************* */
void TestIsGISAXS5::run_isgisaxs_comparison()
{
    // run simulation for default sample parameters
    mp_simulation->runSimulation();
    IntensityDataIOFactory::writeOutputData(*(mp_simulation->getOutputData()),
                                               "this_fitexample.ima");

    // plotting results of comparison we/isgisaxs for the sample with default parameters
    std::string isgi_file(getOutputPath() + "isgi_fitexample.ima.gz");
    std::string this_file("this_fitexample.ima");

    // -------------
    // plot results
    // -------------
    OutputData<double> *isgi_data = IntensityDataIOFactory::readOutputData(isgi_file);
    OutputData<double> *our_data = IntensityDataIOFactory::readOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(
        *our_data, *isgi_data, "TestIsGISAXS5_c1",
        "ex-5: cylinders with size distribution and radial paracrystal inderference function");

    delete isgi_data;
    delete our_data;
}

/* ************************************************************************* */
// plot IsGISAXS data (*.dat file) and IsGISAXS fit results (*.out file)
/* ************************************************************************* */
void TestIsGISAXS5::plot_isgisaxs_fit_results()
{
    // reading isgisaxs scans which actually have been used for a fit together with fit results (100
    // points/scan)
    IsGISAXSData::DataSet_t isgi_scans_smoothed;
    IsGISAXSData::read_outfile(getOutputPath() + "isgi_fitexample.out", isgi_scans_smoothed,
                               IsGISAXSData::DATA_TO_FIT);
    IsGISAXSData::DataSet_t isgi_results;
    IsGISAXSData::read_outfile(getOutputPath() + "isgi_fitexample.out", isgi_results,
                               IsGISAXSData::SIM_RESULT);

    TCanvas *c1 = DrawHelper::createAndRegisterCanvas(
        "c1_isgisaxs_data", "Looking on IsGISAXS data and fit results", 800, 500);
    c1->Divide(2, 2);

    // drawing isgsaxs fit results on top of isgisaxs real data
    TLegend *leg2 = new TLegend(0.5, 0.6, 0.85, 0.85);
    leg2->SetBorderSize(1);
    leg2->SetFillStyle(0);
    for (int i_set = 0; i_set < (int)isgi_scans_smoothed.size(); ++i_set) {
        c1->cd(1 + i_set);
        gPad->SetLogy();
        TH1D *hdata = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "data");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        if (i_set == 0)
            leg2->AddEntry(hdata, "isgisaxs results", "lp");
        TH1D *hdata_smoothed
            = IsGISAXSTools::getOutputDataScanHist(*isgi_scans_smoothed[i_set], "data_smoothed");
        hdata_smoothed->SetLineColor(kBlue);
        hdata_smoothed->DrawCopy("same");
        if (i_set == 0)
            leg2->AddEntry(hdata_smoothed, "isgisaxs data", "lp");
    }
    c1->cd(1);
    leg2->Draw();
    c1->cd(2);
    leg2->Draw();

    // drawing ratio of isgisaxs data/results
    TLegend *leg3 = new TLegend(0.5, 0.6, 0.85, 0.85);
    leg3->SetBorderSize(1);
    leg3->SetFillStyle(0);
    for (int i_set = 0; i_set < (int)isgi_scans_smoothed.size(); ++i_set) {
        c1->cd(3 + i_set);
        *isgi_results[i_set] /= *isgi_scans_smoothed[i_set];
        TH1D *hdata
            = IsGISAXSTools::getOutputDataScanHist(*isgi_results[i_set], "isgisaxs_results_data");
        hdata->SetLineColor(kRed);
        hdata->DrawCopy();
        if (i_set == 0)
            leg3->AddEntry(hdata, "isgisaxs results/data", "lp");
    }
    c1->cd(3);
    leg3->Draw();
    c1->cd(4);
    leg3->Draw();

    c1->Update();
}

/* ************************************************************************* */
// run isgisaxs ex-12 style fit
/* ************************************************************************* */
void TestIsGISAXS5::run_isgisaxs_fit()
{
    throw NotImplementedException("Obsolete code");

//    // creating fit suite
//    mp_fitSuite = new FitSuite();

//    mp_fitSuite->setMinimizer(MinimizerFactory::createMinimizer("Minuit2", "Migrad"));
//    mp_fitSuite->attachObserver(FitSuiteObserverFactory::createPrintObserver(10));
//    mp_fitSuite->attachObserver(FitSuiteObserverFactory::createDrawObserver(10));

//    mp_fitSuite->addFitParameter("*Normalizer/scale", 1e5, 1, AttLimits::limited(1e4, 2e5));
//    mp_fitSuite->addFitParameter("*Normalizer/shift", 10, 0.01, AttLimits::limited(1., 20.));
//    mp_fitSuite->addFitParameter("*SampleBuilder/particle_radius", 4 * Units::nanometer,
//                                 0.01 * Units::nanometer, AttLimits::limited(1., 10.));
//    mp_fitSuite->addFitParameter("*SampleBuilder/dispersion_radius", 0.2, 0.01,
//                                 AttLimits::limited(0.01, 1.));
//    mp_fitSuite->addFitParameter("*SampleBuilder/height_aspect_ratio", 0.8, 0.01,
//                                 AttLimits::limited(0.01, 10.));
//    mp_fitSuite->addFitParameter("*SampleBuilder/interf_distance", 12 * Units::nanometer,
//                                 0.01 * Units::nanometer, AttLimits::limited(0.01, 50.0));
//    mp_fitSuite->addFitParameter("*SampleBuilder/interf_width", 6 * Units::nanometer,
//                                 0.01 * Units::nanometer, AttLimits::limited(0.01, 10.));

//    // reading 1D data scans defined in isgisaxs example
//    IsGISAXSData::DataSet_t isgi_scans;
//    IsGISAXSData::read_datfile(getOutputPath() + "isgi_fitexample.dat", isgi_scans);

//    // setting up fitSuite
//    ChiSquaredModule chiModule;
//    // chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError(0.08) );
//    chiModule.setChiSquaredFunction(new SquaredFunctionDefault()); // isgisaxs uses epsion=0, which
//                                                                   // correspond to our
//                                                                   // SquaredFunctionDefault
//    chiModule.setIntensityNormalizer(IntensityNormalizer());
//    chiModule.setIntensityFunction(IntensityFunctionSqrt());

//    for (IsGISAXSData::DataSet_t::iterator it = isgi_scans.begin(); it != isgi_scans.end(); ++it) {
//        mp_fitSuite->addSimulationAndRealData(*mp_simulation, *(*it), chiModule);
//    }

//    mp_fitSuite->runFit();

//    // drawing results
//    TCanvas *c2 = new TCanvas("c2", "BornAgain fit results", 800, 600);
//    c2->Divide(2, 2);
//    TLegend *leg1 = new TLegend(0.5, 0.6, 0.85, 0.85);
//    leg1->SetBorderSize(1);
//    leg1->SetFillStyle(0);
//    for (size_t i_set = 0; i_set < mp_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd((int)i_set + 1);
//        const FitObject *obj = mp_fitSuite->getFitObjects()->getObject(i_set);
//        TH1D *hreal = IsGISAXSTools::getOutputDataScanHist(
//            *obj->getChiSquaredModule()->getRealData(), "BornAgain_real");
//        TH1D *hsimul = IsGISAXSTools::getOutputDataScanHist(
//            *obj->getChiSquaredModule()->getSimulationData(), "BornAgain_simul");
//        hreal->SetLineColor(kBlue);
//        gPad->SetLogy();
//        hreal->DrawCopy();
//        hsimul->DrawCopy("same");
//        if (i_set == 0) {
//            leg1->AddEntry(hreal, "BornAgain data", "lp");
//            leg1->AddEntry(hsimul, "BornAgain simul", "lp");
//        }
//    }
//    c2->cd(1);
//    leg1->Draw();
//    c2->cd(2);
//    leg1->Draw();

//    // drawing ratio
//    TLegend *leg2 = new TLegend(0.5, 0.6, 0.85, 0.85);
//    leg2->SetBorderSize(1);
//    leg2->SetFillStyle(0);
//    for (size_t i_set = 0; i_set < mp_fitSuite->getFitObjects()->size(); ++i_set) {
//        c2->cd(3 + 1);
//        const FitObject *obj = mp_fitSuite->getFitObjects()->getObject(i_set);
//        OutputData<double> *real = obj->getChiSquaredModule()->getRealData()->clone();
//        OutputData<double> *simul = obj->getChiSquaredModule()->getSimulationData()->clone();

//        c2->cd((int)(i_set + 3));
//        *simul /= *real;
//        TH1D *hratio = IsGISAXSTools::getOutputDataScanHist(*simul, "BornAgain_real_simul_ratio");
//        hratio->DrawCopy();
//        if (i_set == 0) {
//            leg2->AddEntry(hratio, "BornAgain simul/real", "lp");
//        }
//        delete real;
//        delete simul;
//    }
//    c2->cd(3);
//    leg2->Draw();
//    c2->cd(4);
//    leg2->Draw();

//    c2->Update();
}

/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestIsGISAXS5::initializeSimulation()
{
    delete mp_simulation;
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(100, 0.0 * Units::degree, 2.0 * Units::degree, 100,
                                         0.0 * Units::degree, 2.0 * Units::degree);
    mp_simulation->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree,
                                     0.0 * Units::degree);
}

/* ************************************************************************* */
// IsGISAXS ex-5 sample builder
/* ************************************************************************* */
TestIsGISAXS5::SampleBuilder::SampleBuilder()
    : m_particle_radius(4.0 * Units::nanometer), m_dispersion_radius(0.2),
      m_height_aspect_ratio(0.8), m_interf_distance(12 * Units::nanometer),
      m_interf_width(6.0 * Units::nanometer)
{
    init_parameters();
}

void TestIsGISAXS5::SampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("particle_radius", &m_particle_radius);
    registerParameter("dispersion_radius", &m_dispersion_radius);
    registerParameter("height_aspect_ratio", &m_height_aspect_ratio);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}

ISample *TestIsGISAXS5::SampleBuilder::buildSample() const
{
//    MultiLayer *p_multi_layer = new MultiLayer();

//    complex_t n_particle(1.0 - 6e-4, 2e-8);
//    HomogeneousMaterial air_material("Air", 0.0, 0.0);
//    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
//    HomogeneousMaterial particle_material("Particle", n_particle);

//    Layer air_layer(air_material);
//    double height = m_height_aspect_ratio * m_particle_radius;
//    FormFactorCylinder ff_cylinder(m_particle_radius, height);
//    Particle cylinder(particle_material, ff_cylinder);

//    // radius of nanoparticles will be sampled with gaussian probability
//    int nbins = 20;
//    double sigma = m_particle_radius * m_dispersion_radius;
//    int nfwhm(2); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where
//                  // xR is what is defined in isgisaxs *.inp file)
//    DistributionGaussian gauss(m_particle_radius, sigma);

//    ParticleLayout particle_layout;
//    InterferenceFunctionRadialParaCrystal *p_interference_function
//        = new InterferenceFunctionRadialParaCrystal(
//            m_interf_distance, 1e7 * Units::nanometer); // peak_distance, corr_length
//    FTDistribution1DGauss pdf(m_interf_width);
//    p_interference_function->setProbabilityDistribution(pdf);
//    particle_layout.addInterferenceFunction(p_interference_function);

//    // building nano particles
//    ParameterDistribution par_distr("*/radius", gauss, nbins, nfwhm);
//    ParticleDistribution particle_collection(cylinder, par_distr);
//    particle_layout.addParticle(particle_collection);

//    // add layout to layer
//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);

//    Layer substrate_layer;
//    substrate_layer.setMaterial(substrate_material);
//    p_multi_layer->addLayer(substrate_layer);

//    return p_multi_layer;

    throw Exceptions::NotImplementedException("Cleanup the code!");

}
