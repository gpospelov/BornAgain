#include "IsGISAXS09.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorPyramid.h"
#include "MaterialManager.h"
#include "Experiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Transform3D.h"
#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS09::IsGISAXS09()
    : m_name("IsGISAXS09")
    , m_description("Pyramids on top of substrate - Rotated pyramids on top of substrate")
    , m_result(0)
{ }

void FunctionalTests::IsGISAXS09::run()
{
    // ---------------------
    // building sample
    // ---------------------
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        complex_t n_particle(1.0-6e-4, 2e-8);

    //  Pyramid
        MultiLayer multi_layer_pyramid;
        ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
        particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer_pyramid.addLayer(air_layer_decorator);
        multi_layer_pyramid.addLayer(substrate_layer);

    //  Rotated Pyramid

        const double angle_around_z = 45.*Units::degree;
        MultiLayer multi_layer_rotated_pyramid;

        Particle *pyramid = new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

        Geometry::Transform3D *transform = new Geometry::RotateZ3D(angle_around_z);

        ParticleDecoration particle_decoration_rotated;

        particle_decoration_rotated.addParticle(pyramid, transform);
        particle_decoration_rotated.addInterferenceFunction(new InterferenceFunctionNone());

        LayerDecorator air_layer_decorator_rotated(air_layer, particle_decoration_rotated);

        multi_layer_rotated_pyramid.addLayer(air_layer_decorator_rotated);
        multi_layer_rotated_pyramid.addLayer(substrate_layer);

    // ---------------------
    // building experiment
    // ---------------------
    Experiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment
    // ---------------------
    experiment.setSample(multi_layer_pyramid);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_pyramid_Z0.ima");

    experiment.setSample(multi_layer_rotated_pyramid);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_pyramid_Z45.ima");

}

int FunctionalTests::IsGISAXS09::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data and generated examples
    std::vector< CompareStruct > tocompare;
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS09/";

    tocompare.push_back( CompareStruct("isgi_pyramid_Z0.ima.gz", "this_pyramid_Z0.ima",
            "Pyramid DWBA formfactor") );
    tocompare.push_back( CompareStruct("isgi_pyramid_Z45.ima.gz", "this_pyramid_Z45.ima",
            "Pyramid DWBA formfactor rotated") );

    bool status_ok(true);

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
        OutputData<double> *m_result = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);
        std::string descript  = tocompare[i].descr;

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();
    if( diff > threshold ) status_ok=false;

    std::cout << descript << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS09 test;
    test.run();

    return test.analyseResults();
}
#endif





