#include "IsGISAXS03.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorCylinder.h"
#include "Experiment.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS03::IsGISAXS03()
    : m_name("IsGISAXS03")
    , m_description("Cylinder formfactor in BA and DWBA")
    , m_result(0)
{ }

void FunctionalTests::IsGISAXS03::run()
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
        ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        MultiLayer multi_layer_CylinderDWBA;
        multi_layer_CylinderDWBA.addLayer(air_layer_decorator);
        multi_layer_CylinderDWBA.addLayer(substrate_layer);

    // IsGISAXS3 functional test: cylinder in the air

        MultiLayer multi_layer_CylinderBA;
        multi_layer_CylinderBA.addLayer(air_layer_decorator);

    // IsGISAXS3 functional test: cylinder in the air with size distribution

        MultiLayer multi_layer_CylinderBA_size;
        ParticleDecoration particle_decoration_CylinderBA_size;

        // preparing prototype of nano particle
        double radius = 5*Units::nanometer;
        double sigma = 0.2*radius;
        FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
        Particle nano_particle(n_particle, p_ff_cylinder);

        // radius of nanoparticles will be sampled with gaussian probability
        int nbins(100), nfwhm(2);
        StochasticSampledParameter par(StochasticDoubleGaussian(radius, sigma), nbins, nfwhm);

        ParticleBuilder builder;
        builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
        builder.plantParticles(particle_decoration_CylinderBA_size);

        particle_decoration_CylinderBA_size.addInterferenceFunction(new InterferenceFunctionNone());

        LayerDecorator air_layer_decorator_CylinderBA_size(air_layer, particle_decoration_CylinderBA_size);
        multi_layer_CylinderBA_size.addLayer(air_layer_decorator_CylinderBA_size);

    // ---------------------
    // building experiment
    // ---------------------
    Experiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment and copying data
    // ---------------------
    // cylinder DWBA
    experiment.setSample(multi_layer_CylinderDWBA);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_DWBA.ima");

    // cylinder in the air
    experiment.setSample(multi_layer_CylinderBA);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_BA.ima");

    // cylinder in BA with size distribution
    experiment.setSample(multi_layer_CylinderBA_size);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_BA_size.ima");

}
int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);

    std::vector< CompareStruct > tocompare;
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS03/";

    tocompare.push_back( CompareStruct("isgi_cylinder_BA.ima.gz",      "this_cylinder_BA.ima",
            "Cylinder BA Formfactor") );
    tocompare.push_back( CompareStruct("isgi_cylinder_BA_size.ima.gz", "this_cylinder_BA_size.ima",
            "Cylinder BA Formfactor with size distribution") );
    tocompare.push_back( CompareStruct("isgi_cylinder_DWBA.ima.gz",    "this_cylinder_DWBA.ima",
            "Cylinder DWBA Formfactor") );

    bool status_ok(true);

    // retrieving reference data and generated examples
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
    FunctionalTests::IsGISAXS03 test;
    test.run();

    return test.analyseResults();
}
#endif


