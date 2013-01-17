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
#include "FitSuiteHelper.h"
#include "ResolutionFunction2DSimple.h"
#include "MathFunctions.h"
#include "ROOTMinimizer.h"
#include "OutputDataFunctions.h"
#include "ExperimentConstants.h"
#include "OutputDataIOFactory.h"

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


TestIsGISAXS5::TestIsGISAXS5()
    : IFunctionalTest("TestIsGISAXS5")
    , m_experiment(0)
    , m_sample_builder(0)

{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-5/");
}


void TestIsGISAXS5::execute()
{
    // initializing experiment and sample builder
    initialiseExperiment();

    // run our standard isgisaxs comparison
    run_isgisaxs_comparison();

}


void TestIsGISAXS5::finalise()
{

}


/* ************************************************************************* */
// standard ixgisaxs comparison
/* ************************************************************************* */
void TestIsGISAXS5::run_isgisaxs_comparison()
{
    // run simulation for default sample parameters
    m_experiment->runSimulation();
    OutputDataIOFactory::writeOutputData(*(m_experiment->getOutputData()), getOutputPath()+"this_fitexample.ima");

    // plotting results of comparison we/isgisaxs for the sample with default parameters
    std::string isgi_file(getOutputPath()+"isgi_fitexample.ima.gz");
    std::string this_file(getOutputPath()+"this_fitexample.ima");

    // -------------
    // plot results
    // -------------
    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data,"TestIsGISAXS5_c1", "ex-5: cylinders with size distribution and 1D paracrystal inderference function");

    delete isgi_data;
    delete our_data;
}


/* ************************************************************************* */
// initialize experiment
/* ************************************************************************* */
void TestIsGISAXS5::initialiseExperiment()
{
    delete m_sample_builder;
    m_sample_builder = new SampleBuilder();
    delete m_experiment;
    m_experiment = new GISASExperiment(mp_options);
    m_experiment->setSampleBuilder(m_sample_builder);
    m_experiment->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_experiment->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
}


/* ************************************************************************* */
// IsGISAXS ex-5 sample builder
/* ************************************************************************* */
TestIsGISAXS5::SampleBuilder::SampleBuilder()
    : m_particle_radius(4.0*Units::nanometer)
    , m_dispersion_radius(0.2)
    , m_height_aspect_ratio(0.8)
    , m_interf_distance(12*Units::nanometer)
    , m_interf_width(6.0*Units::nanometer)
{
      init_parameters();
}

void TestIsGISAXS5::SampleBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("particle_radius", &m_particle_radius);
    getParameterPool()->registerParameter("dispersion_radius", &m_dispersion_radius);
    getParameterPool()->registerParameter("height_aspect_ratio", &m_height_aspect_ratio);
    getParameterPool()->registerParameter("interf_distance", &m_interf_distance);
    getParameterPool()->registerParameter("interf_width", &m_interf_width);
}

ISample *TestIsGISAXS5::SampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);

    Layer air_layer(air_material);
    double height = m_height_aspect_ratio*m_particle_radius;
    FormFactorCylinder *ff_cylinder = new FormFactorCylinder(height, m_particle_radius);
    Particle cylinder(n_particle, ff_cylinder );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=20;
    double sigma = m_particle_radius*m_dispersion_radius;
    int nfwhm(2); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticSampledParameter stochastic_parameter(StochasticDoubleGaussian(m_particle_radius, sigma), nbins, nfwhm);

    ParticleDecoration particle_decoration;
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(m_interf_distance, m_interf_width, 1e4*Units::nanometer); // peak_distance, width, corr_length
    particle_decoration.addInterferenceFunction(p_interference_function);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder,"/Particle/FormFactorCylinder/radius", stochastic_parameter);
    builder.plantParticles(particle_decoration);

    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

    Layer substrate_layer;
    substrate_layer.setMaterial(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}
