#include "TestIsGISAXS9.h"
#include "IsGISAXSTools.h"
#include "InterferenceFunctionNone.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "NanoParticleDecoration.h"
#include "NanoParticle.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"
#include "FormFactors.h"
#include "BasicVector3D.h"
#include "Transform3D.h"
#include "ICompositeIterator.h"
#include "SampleFactory.h"

#include "TCanvas.h"
#include "TRandom.h"




TestIsGISAXS9::TestIsGISAXS9()
    : m_sample(0)
{
}

TestIsGISAXS9::~TestIsGISAXS9()
{
    clear();
}


void TestIsGISAXS9::clear()
{
    delete m_sample; m_sample = 0;
    for(std::vector<OutputData<double> *>::iterator it=m_results.begin(); it!=m_results.end(); it++) {
        delete (*it);
    }
    m_results.clear();
}



void TestIsGISAXS9::execute()
{
    clear();

    // setting experiment
    GISASExperiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // pyramid
    initializeSample_Pyramid();
    experiment.setSample(m_sample);
    experiment.runSimulation();
    m_results.push_back( experiment.getOutputDataClone() );
    IsGISAXSTools::writeOutputDataToFile(*m_results.back(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z0.ima");

    // rotated pyramid
    initializeSample_RotatedPyramid();
    experiment.setSample(m_sample);
    experiment.runSimulation();
    m_results.push_back( experiment.getOutputDataClone() );
    IsGISAXSTools::writeOutputDataToFile(*m_results.back(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z45.ima");

}


void TestIsGISAXS9::finalise()
{
    std::vector<std::string > isgi_files;
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/isgi_pyramid_Z0.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/isgi_pyramid_Z45.ima");

    int ncomparison = m_results.size();

    TCanvas *canvaces[2];
    canvaces[0] = new TCanvas("TestIsGISAXS9_c1", "Pyramid DWBA formfactor", 1024, 768);
    canvaces[1] = new TCanvas("TestIsGISAXS9_c2", "Rotated pyramid DWBA formfactor", 1024, 768);

    for(int i_comparison=0; i_comparison<ncomparison; i_comparison++) {
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_files[i_comparison]);
        OutputData<double> *our_data = m_results[i_comparison];

        TCanvas *c1 = canvaces[i_comparison];
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Calculated pyramid FF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs pyramid FF");

        //IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
        IsGISAXSTools::setMinimum(-0.0001);
        IsGISAXSTools::setMaximum(0.0001);

        // difference
        c1->cd(3);
        IsGISAXSTools::drawOutputDataDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

        // difference
        c1->cd(4);
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

        delete isgi_data;

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
    }

}


/* ************************************************************************* */
// pyramids on top of substrate (no interference)
/* ************************************************************************* */
void TestIsGISAXS9::initializeSample_Pyramid()
{
    if(m_sample) delete m_sample;
    m_sample = 0;

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
                new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
}


/* ************************************************************************* */
// rotated pyramids on top of substrate (no interference)
/* ************************************************************************* */
void TestIsGISAXS9::initializeSample_RotatedPyramid()
{
    const double angle_around_z = 45.*Units::degree;

    if(m_sample) delete m_sample;
    m_sample = 0;

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

    NanoParticle *pyramid = new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

    Geometry::Transform3D *transform = new Geometry::Transform3D();
    *transform = Geometry::RotateZ3D(angle_around_z);

    NanoParticleDecoration particle_decoration;

    particle_decoration.addNanoParticle(pyramid, transform);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    m_sample = p_multi_layer;
}
