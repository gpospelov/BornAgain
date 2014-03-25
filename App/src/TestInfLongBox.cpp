// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestRipple2.cpp
//! @brief     Implements class TestRipple2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestInfLongBox.h"
#include "DrawHelper.h"
#include "Simulation.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSData.h"
#include "IsGISAXSTools.h"
#include "Layer.h"
#include "MaterialManager.h"
#include "MathFunctions.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "OutputDataIOFactory.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleLayout.h"
#include "ResolutionFunction2DSimple.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "Utils.h"
#include "OffSpecSimulation.h"

#define protected public // needed to access the protected evaluate_for_q method
#include "FormFactorInfLongBox.h"
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


TestInfLongBox::TestInfLongBox()
: IApplicationTest("TestInfLongBox")
, mp_simulation(0)
, mp_sample_builder(new TestSampleBuilder())
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/BornAgain/" ));
}

void TestInfLongBox::execute()
{
    // initializing simulation and sample builder
    initializeSimulation();
    mp_simulation->runSimulation();
//    save_results();
    plot_results();

    // plot the pure formfactor
    //drawff();
}

/* ************************************************************************* */
// save results of simulation to file
/* ************************************************************************* */
void TestInfLongBox::save_results()
{
    // run simulation for default sample parameters
    //mp_simulation->runSimulation();
    std::string filename(getOutputPath()+"test_inflongbox.ima");
    OutputDataIOFactory::writeIntensityData(*(mp_simulation->getIntensityData()),
                                         filename);
}

/* ************************************************************************* */
// plot the pure formfactor
/* ************************************************************************* */
void TestInfLongBox::drawff()
{
    FormFactorInfLongBox *ff = new FormFactorInfLongBox(100.0*Units::nanometer, 50.0*Units::nanometer);
    size_t pfbins = 400;
    size_t afbins = 400;
	
    double afmin = -2.0;
    double afmax = 2.0;
    double pfmin = -2.0;
    double pfmax = 2.0;
    double stepaf = (afmax - afmin)/afbins;
    double steppf = (pfmax - pfmin)/pfbins;

    double lambda = 1.0;
    double alpha_i = 0.2*M_PI/180.0;
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);

    TH2D *hist = new TH2D("InfLongBox", "InfLongBox",
                          (int)pfbins, -2.0, 2.0,
                          (int)afbins, -2.0, 2.0);

    hist->GetXaxis()->SetTitle( "phi_f" );
    hist->GetYaxis()->SetTitle( "alpha_f" );

    double af0 = afmin;
    cvector_t k_f0;
    k_f0.setLambdaAlphaPhi(lambda, M_PI*afmin/180.0, M_PI*pfmin/180.0);

    for (size_t iaf=0; iaf < afbins; iaf++) {
        for (size_t ipf=0; ipf < pfbins; ipf++) {
            double pf = pfmin + ipf*steppf + steppf/2.;
            double af = afmin + iaf*stepaf + stepaf/2.;

            cvector_t k_f;
            k_f.setLambdaAlphaPhi(lambda, M_PI*af/180.0, M_PI*pf/180.0);

            Bin1D alpha_f_bin = {M_PI*af0/180.0, M_PI*af/180.0};
            Bin1DCVector k_f_bin(k_f0, k_f);

            af0 = af;
            k_f0.setLambdaAlphaPhi(lambda, M_PI*af/180.0, M_PI*pf/180.0);

            double value = std::pow(std::abs(ff->evaluate(k_i, k_f_bin, alpha_f_bin)),2);

            hist->Fill(pf, af, value + 1);
			//std::cout << "qy=" << qy << " qz=" << qz << " I=" << value*value << std::endl;
		}
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(111111);

    TCanvas *c1 = new TCanvas("InfLongBox", "InfLongBox", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();
}


/* ************************************************************************* */
// initialize simulation
/* ************************************************************************* */
void TestInfLongBox::initializeSimulation()
{
  //  mp_sample_builder = new SampleBuilder();
    
	delete mp_simulation;
//    mp_simulation = new Simulation(mp_options);
//    mp_simulation->setSampleBuilder(mp_sample_builder);
//    mp_simulation->setDetectorParameters(400, -1.0*Units::degree, 1.0*Units::degree, 400, 0.0*Units::degree, 5.2*Units::degree, true);
//    mp_simulation->setBeamParameters(12.0*Units::angstrom, 0.3*Units::degree, 0.0*Units::degree);

    mp_simulation = new OffSpecSimulation(mp_options);
    mp_simulation->setSampleBuilder(mp_sample_builder);
    mp_simulation->setDetectorParameters(20, -1.0*Units::degree, 1.0*Units::degree, 200, 0.0*Units::degree, 5.2*Units::degree);
    AxisDouble *alpha_i_axis = new AxisDouble("alpha_i", 200, 0.0*Units::degree, 5.2*Units::degree);
    mp_simulation->setBeamParameters(12.0*Units::angstrom, *alpha_i_axis, 0.0*Units::degree);
    mp_simulation->setBeamIntensity(1e9);

}

/* ************************************************************************* */
// sample builder
/* ************************************************************************* */
TestInfLongBox::TestSampleBuilder::TestSampleBuilder()
    : m_w(520.0*Units::nanometer)
    , m_h(15.0*Units::nanometer)
    , m_lattice_length(945.0*Units::nanometer)
    , m_xi(0.0*Units::degree)
{
      init_parameters();
}

void TestInfLongBox::TestSampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_w);
    registerParameter("height", &m_h);
    registerParameter("lattice_length", &m_lattice_length);
    registerParameter("xi_angle", &m_xi);
}

ISample *TestInfLongBox::TestSampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

   // defining materials
    const IMaterial *air_material = MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *substrate_material = MaterialManager::getHomogeneousMaterial("GaAs", 7.04e-5, 1.0233e-8);
    const IMaterial *silver_material = MaterialManager::getHomogeneousMaterial("Ag", 7.948e-5, 2.36e-7);
    const IMaterial *iron_material = MaterialManager::getHomogeneousMaterial("Fe", 1.839e-4, 1.38e-8);
    //const IMaterial *cr_material = MaterialManager.getHomogeneousMaterial("Cr", 6.94e-5, 1.62e-8);
    const IMaterial *cr_material = MaterialManager::getHomogeneousMaterial("Cr", 6.94e-5, 1.62e-8);


    Layer air_layer(*air_material);
    FormFactorInfLongBox *ff = new FormFactorInfLongBox(m_w, m_h);
    Particle ibox(iron_material, ff );

    Geometry::Transform3D transform =
            Geometry::Transform3D::createRotateZ(90*Units::degree);

    ParticleLayout particle_layout;
    particle_layout.addParticle(ibox,transform);
    Lattice1DIFParameters lattice_params;
    lattice_params.m_length=m_lattice_length;
    lattice_params.m_xi = m_xi;
    InterferenceFunction1DLattice *p_interference_function = new InterferenceFunction1DLattice(lattice_params);
    FTDistribution1DCauchy pdf(10e6*Units::nanometer);
    p_interference_function->setProbabilityDistribution(pdf);

    //IInterferenceFunction *p_interference_function = new InterferenceFunctionNone();
    particle_layout.addInterferenceFunction(p_interference_function);
    //particle_layout.printParameters();

    // making layer holding all whose nano particles
    air_layer.setLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);
    Layer iron_layer;
    iron_layer.setMaterialAndThickness(*iron_material, 15.0*Units::nanometer);
    Layer cr_layer;
    cr_layer.setMaterialAndThickness(*cr_material, 1.1*Units::nanometer) ;
    Layer silver_layer;
    silver_layer.setMaterialAndThickness(*silver_material, 150.0*Units::nanometer);
    //Layer iron_layer = Layer(iron_material, 15.0*nanometer);
    //Layer cr_layer = Layer(cr_material, 1.1*nanometer);
    //Layer silver_layer = Layer(silver_material, 150.0*nanometer);

    Layer substrate_layer;
    substrate_layer.setMaterial(*substrate_material);
    for (int i=0; i<10; i++) {
        p_multi_layer->addLayer(cr_layer);
        p_multi_layer->addLayer(iron_layer);
    }

    p_multi_layer->addLayer(silver_layer);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

void TestInfLongBox::plot_results()
{
	OutputData<double> *m_result = mp_simulation->getIntensityData();
    const IAxis *axisPhi = m_result->getAxis(0);
    const IAxis *axisAlpha = m_result->getAxis(1);

    size_t nPhibins = axisPhi->getSize();
    size_t nAlphabins = axisAlpha->getSize();

    TH2D *hist = new TH2D("Ibox", "Ibox",
                          (int)nPhibins, axisPhi->getMin()/Units::degree, axisPhi->getMax()/Units::degree,
                          (int)nAlphabins, axisAlpha->getMin()/Units::degree, axisAlpha->getMax()/Units::degree);

    hist->GetXaxis()->SetTitle( axisPhi->getName().c_str() );
    hist->GetYaxis()->SetTitle( axisAlpha->getName().c_str() );

    OutputData<double>::const_iterator it = m_result->begin();
    while (it != m_result->end())
    {
        double x = m_result->getValueOfAxis( axisPhi->getName(), it.getIndex() );
        double y = m_result->getValueOfAxis( axisAlpha->getName(), it.getIndex() );
        double value = *it++;
        hist->Fill(x/Units::degree, y/Units::degree, value);
    }

    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("Ibox", "Ibox", 980, 800);
    c1->cd();
    c1->SetLogz();
    hist->SetMinimum(1.0);
    hist->DrawCopy("colz");
    c1->Update();

    delete axisPhi;
    delete axisAlpha;
    delete hist;
}


