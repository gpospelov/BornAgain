#include "TestIsGISAXS3.h"
#include "IsGISAXSTools.h"
#include "InterferenceFunctionNone.h"
#include "Types.h"
#include "Units.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "NanoParticleDecoration.h"
#include "NanoParticle.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <cmath>
#include <iostream>
#include <fstream>


TestIsGISAXS3::TestIsGISAXS3()
    : m_dwba_ff(new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer))
{
	complex_t n_substrate(1.0-6e-6, 2e-8);
    m_dwba_ff.setReflectionFunction(new ReflectionFresnelFunctionWrapper(n_substrate));
    m_dwba_ff.setTransmissionFunction(new DoubleToComplexFunctionWrapper(transmission_fresnel));
    mp_intensity_output = new OutputData<double>();
    NamedVector<double> *p_y_axis = new NamedVector<double>(std::string("phi_f"));
    initialize_angles_sine(p_y_axis, 0.0, 2.0, 100);
    NamedVector<double> *p_z_axis = new NamedVector<double>(std::string("alpha_f"));
    initialize_angles_sine(p_z_axis, 0.0, 2.0, 100);
    mp_intensity_output->addAxis(p_y_axis);
    mp_intensity_output->addAxis(p_z_axis);
}

TestIsGISAXS3::~TestIsGISAXS3()
{
    delete mp_intensity_output;
    delete mp_sample;
}

void TestIsGISAXS3::execute()
{
    initializeSample();
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100
            , 0.0*Units::degree, 2.0*Units::degree, 100, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_intensity_output = experiment.getOutputData();
    draw();
    write();
}

void TestIsGISAXS3::draw()
{
    // creation of 2D histogram from calculated intensities
    TCanvas *c1 = new TCanvas("c1_test_dwba_formfactor", "Cylinder Formfactor", 0, 0, 1024, 768);
    (void)c1;

    MultiIndex& index = mp_intensity_output->getIndex();
    index.reset();
    NamedVector<double> *p_y_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("phi_f"));
    NamedVector<double> *p_z_axis = dynamic_cast<NamedVector<double>*>(mp_intensity_output->getAxis("alpha_f"));
    size_t y_size = p_y_axis->getSize();
    size_t z_size = p_z_axis->getSize();
    double y_start = (*p_y_axis)[0];
    double y_end = (*p_y_axis)[y_size-1];
    double z_start = (*p_z_axis)[0];
    double z_end = (*p_z_axis)[z_size-1];
    TH2D *p_hist2D = new TH2D("p_hist2D", "Cylinder DWBA Formfactor", y_size, y_start, y_end, z_size, z_start, z_end);
    //p_hist2D->UseCurrentStyle();
    p_hist2D->GetXaxis()->SetTitle("phi_f");
    p_hist2D->GetYaxis()->SetTitle("alpha_f");

    while (!index.endPassed())
    {
        size_t index_y = index.getCurrentIndexOfAxis("phi_f");
        size_t index_z = index.getCurrentIndexOfAxis("alpha_f");
        double x_value = (*p_y_axis)[index_y];
        double y_value = (*p_z_axis)[index_z];
        double z_value = mp_intensity_output->currentValue();
        p_hist2D->Fill(x_value, y_value, z_value);
        ++index;
    }
    p_hist2D->SetContour(50);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    gPad->SetLogz();
    gPad->SetRightMargin(0.12);
    p_hist2D->SetMinimum(1.0);
    p_hist2D->Draw("CONT4 Z");
}

void TestIsGISAXS3::write()
{
    std::ofstream file;
    file.open("./IsGISAXS_examples/ex-3/dwbacyl.ima", std::ios::out);
    mp_intensity_output->resetIndex();
    size_t row_length = mp_intensity_output->getAxes()[0]->getSize();
    int counter = 1;
    while(mp_intensity_output->hasNext()) {
        double z_value = mp_intensity_output->next();
        file << z_value << "    ";
        if(counter%row_length==0) {
            file << std::endl;
        }
        ++counter;
    }
}

void TestIsGISAXS3::initializeSample()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
                0.0, new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}

void TestIsGISAXS3::initializeSample2()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
                7*Units::nanometer, new InterferenceFunctionNone());
    LayerDecorator substrate_layer_decorator(substrate_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer_decorator);
    mp_sample = p_multi_layer;
}
