// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRipple1.cpp
//! @brief     Implements class TestRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestRipple1.h"
#include "DrawHelper.h"
#include "Simulation.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "Materials.h"
#include "MathFunctions.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DGaussian.h"
#include "Units.h"
#include "Utils.h"

#define protected public // needed to acess the protected evaluate_for_q mathod
#include "FormFactorRipple1.h"
#undef protected
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
#include "TStyle.h"
#include "FileSystem.h"


TestRipple1::TestRipple1()
: IApplicationTest("TestRipple1")
, mp_simulation(0)
, mp_sample_builder(new TestSampleBuilder())
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/BornAgain/" ));
}

void TestRipple1::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();
    mp_simulation->runSimulation();

    //save_results();
    plot_results();

    // plot the pure formfactor
    //drawff();
}

/* ************************************************************************* */
// save results of simulation to file
/* ************************************************************************* */
void TestRipple1::save_results()
{
    std::string filename(getOutputPath()+"test_ripple1.ima");
    IntensityDataIOFactory::writeOutputData(*(mp_simulation->getDetectorIntensity()),
                                         filename);
    std::cout << "Data saved to " << filename << std::endl;
}

/* ************************************************************************* */
// plot the pure formfactor
// evaluate_for_q mathod must be turned to public to use this function
/* ************************************************************************* */
void TestRipple1::drawff()
{
    FormFactorRipple1 *ff = new FormFactorRipple1(100.0*Units::nanometer, 20.0*Units::nanometer, 4.0*Units::nanometer);
    size_t qybins = 200;
    size_t qzbins = 200;

    double qymin = -2.0;
    double qymax = 2.0;
    double qzmin = -2.0;
    double qzmax = 2.0;
    double stepqy = (qymax - qymin)/qybins;
    double stepqz = (qzmax - qzmin)/qzbins;

    TH2D *hist = new TH2D("Ripple1", "Ripple1",
                          (int)qybins, -2.0, 2.0,
                          (int)qzbins, -2.0, 2.0);

    hist->GetXaxis()->SetTitle( "Qy" );
    hist->GetYaxis()->SetTitle( "Qz" );

    cvector_t qq;
    for (size_t iqz=0; iqz < qzbins; iqz++) {
        for (size_t iqy=0; iqy < qybins; iqy++) {
            double qy = qymin + iqy*stepqy + stepqy/2.;
            double qz = qzmin + iqz*stepqz + stepqz/2.;
            qq.setXYZ(0.0, qy, qz);
            double value = std::abs(ff->evaluate_for_q(qq));
            hist->Fill(qy, qz, value*value + 1);
            //std::cout << "qy=" << qy << " qz=" << qz << " I=" << value*value << std::endl;
        }
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(111111);

    TCanvas *c1 = new TCanvas("Ripple1", "Ripple1", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();
}


/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestRipple1::initializeSimulation()
{
  //  mp_sample_builder = new SampleBuilder();

    delete mp_simulation;
    mp_simulation = new GISASSimulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(100, -1.5*Units::degree, 1.5*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree);
    mp_simulation->setBeamParameters(1.6*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);
}

/* ************************************************************************* */
// sample builder
/* ************************************************************************* */
TestRipple1::TestSampleBuilder::TestSampleBuilder()
    : m_w(20.0*Units::nanometer)
    , m_h(4.0*Units::nanometer)
    , m_l(100.0*Units::nanometer)
    , m_interf_distance(20.0*Units::nanometer)
    , m_interf_width(4.0*Units::nanometer)
{
      init_parameters();
}

void TestRipple1::TestSampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_w);
    registerParameter("height", &m_h);
    registerParameter("length", &m_l);
    registerParameter("interf_distance", &m_interf_distance);
    registerParameter("interf_width", &m_interf_width);
}

ISample *TestRipple1::TestSampleBuilder::buildSample() const
{
//    MultiLayer *p_multi_layer = new MultiLayer();

//    complex_t n_particle(1.0-6e-4, 2e-8);
//    HomogeneousMaterial air_material("Air", 0.0, 0.0);
//    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
//    HomogeneousMaterial particle_material("Particle", n_particle);

//    Layer air_layer(air_material);
//    FormFactorRipple1 ff_ripple1(m_l, m_w, m_h);
//    Particle ripple(particle_material, ff_ripple1);


//    ParticleLayout particle_layout;
//    particle_layout.addParticle(ripple, 1.0);
//    InterferenceFunctionRadialParaCrystal *p_interference_function =
//            new InterferenceFunctionRadialParaCrystal(m_interf_distance,
//                    1e7*Units::nanometer); // peak_distance, corr_length
//    FTDistribution1DGauss pdf(m_interf_width);
//    p_interference_function->setProbabilityDistribution(pdf);
//    particle_layout.addInterferenceFunction(p_interference_function);

//    // making layer holding all whose nano particles
//    air_layer.addLayout(particle_layout);

//    p_multi_layer->addLayer(air_layer);

//    Layer substrate_layer;
//    substrate_layer.setMaterial(substrate_material);
//    p_multi_layer->addLayer(substrate_layer);

//    return p_multi_layer;
    throw Exceptions::NotImplementedException("Cleanup the code!");


}

void TestRipple1::plot_results()
{
    OutputData<double> *m_result = mp_simulation->getDetectorIntensity();
    const IAxis *axisPhi = m_result->getAxis(0);
    const IAxis *axisAlpha = m_result->getAxis(1);

    size_t nPhibins = axisPhi->getSize();
    size_t nAlphabins = axisAlpha->getSize();

    TH2D *hist = new TH2D("Ripple1", "Ripple1",
                          (int)nPhibins, axisPhi->getMin()/Units::degree, axisPhi->getMax()/Units::degree,
                          (int)nAlphabins, axisAlpha->getMin()/Units::degree, axisAlpha->getMax()/Units::degree);

    hist->GetXaxis()->SetTitle( axisPhi->getName().c_str() );
    hist->GetYaxis()->SetTitle( axisAlpha->getName().c_str() );

    OutputData<double>::const_iterator it = m_result->begin();
    while (it != m_result->end())
    {
        double x = m_result->getAxisValue(it.getIndex(), axisPhi->getName());
        double y = m_result->getAxisValue(it.getIndex(),axisAlpha->getName());
        double value = *it++;
        hist->Fill(x/Units::degree, y/Units::degree, value);
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("Ripple1", "Ripple1", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();

    delete axisPhi;
    delete axisAlpha;
    delete hist;
}


