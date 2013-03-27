#include "IsGISAXS09.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorPyramid.h"
#include "MaterialManager.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Rotate3D.h"
#include "Utils.h"
#include "InterferenceFunction1DParaCrystal.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS09::IsGISAXS09()
    : m_name("IsGISAXS09")
    , m_description("Pyramids on top of substrate - Rotated pyramids on top of substrate")
    , m_path(Utils::FileSystem::GetHomePath()+
             "Tests/FunctionalTests/TestCore/IsGISAXS09/")
{
    m_results.resize(kNumberOfTests, 0);
}


FunctionalTests::IsGISAXS09::~IsGISAXS09()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it)
        delete (*it);
}


// IsGISAXS example #9: pyramid
void FunctionalTests::IsGISAXS09::runpyramidZ0()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration(
        new Particle(n_particle,
                     new FormFactorPyramid(5*Units::nanometer,
                                           5*Units::nanometer,
                                           Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(multi_layer);

    // running simulation
    simulation.runSimulation();
    m_results[kTest_Z0] = simulation.getOutputDataClone();
}


// IsGISAXS example #9: rotated pyramid
void FunctionalTests::IsGISAXS09::runpyramidZ45()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    complex_t n_particle(1.0-6e-4, 2e-8);
    const double angle_around_z = 45.*Units::degree;
    Particle *pyramid = new Particle(
        n_particle,
        new FormFactorPyramid(5*Units::nanometer,
                              5*Units::nanometer,
                              Units::deg2rad(54.73)) );

    Geometry::ITransform3D *transform =
        new Geometry::RotateZ_3D(angle_around_z);

    ParticleDecoration particle_decoration;

    particle_decoration.addParticle(pyramid, transform);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(multi_layer);

    // running simulation
    simulation.runSimulation();
    m_results[kTest_Z45] = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS09::analyseResults()
{
    const double threshold(1e-10);
    const char *reference_files[kNumberOfTests] =
        {"isgisaxs09_reference_pyramid_Z0.ima.gz",
         "isgisaxs09_reference_pyramid_Z45.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference =
            OutputDataIOFactory::getOutputData(m_path +
                                               reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        double diff(0);
        for(OutputData<double>::const_iterator it =
                result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff)) status_ok=false;
        delete reference;
    }

    std::cout << m_name << " " << m_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS09 test;
    test.runpyramidZ0();
    test.runpyramidZ45();
    return test.analyseResults();
}
#endif





