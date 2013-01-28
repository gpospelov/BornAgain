#include "IsGISAXS011.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "LayerDecorator.h"
#include "OutputDataIOFactory.h"
#include "GISASExperiment.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorParallelepiped.h"
#include "MaterialManager.h"
#include "Units.h" //kvector_t
#include "Utils.h"

/*#include "Particle.h"
#include "FormFactors.h"
#include "Transform3D.h"
#include "LayerDecorator.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Crystal.h"
#include "MesoCrystal.h"
#include "FormFactorWeighted.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "StochasticSampledParameter.h"
#include "IsGISAXSMorphologyFileDecoration.h"*/


#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS011::IsGISAXS011()
    : m_name("IsGISAXS011")
    , m_description("Core shell nanoparticles")
    , m_result(0)
{ }

void FunctionalTests::IsGISAXS011::run()
{
    // ---------------------
    // building sample
    // ---------------------
     MultiLayer multi_layer;

     const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
     Layer air_layer;
     air_layer.setMaterial(p_air_material);

     complex_t n_particle_shell(1.0-1e-4, 2e-8);
     complex_t n_particle_core(1.0-6e-5, 2e-8);
     Particle shell_particle(n_particle_shell, new FormFactorParallelepiped(8*Units::nanometer, 8*Units::nanometer));
     Particle core_particle(n_particle_core, new FormFactorParallelepiped(7*Units::nanometer, 6*Units::nanometer));
     kvector_t core_position(0.0, 0.0, 0.0);
     ParticleCoreShell particle(shell_particle, core_particle, core_position);
     ParticleDecoration particle_decoration(particle.clone());
     particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
     LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    // ---------------------
    // building experiment
    // ---------------------
     GISASExperiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment
    // ---------------------
    experiment.setSample(multi_layer);
    experiment.runSimulation();
    // ---------------------
    // copying data
    // ---------------------
    m_result = experiment.getOutputDataClone();

}

int FunctionalTests::IsGISAXS011::analyseResults()
{
   const double threshold(1e-10);

   // retrieving reference data
     std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS011/isgisaxs011_reference.ima.gz";
     OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

   // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}

#ifdef STANDALONE

int main()
{
    FunctionalTests::IsGISAXS011 test;
    test.run();

    return test.analyseResults();
}
#endif

