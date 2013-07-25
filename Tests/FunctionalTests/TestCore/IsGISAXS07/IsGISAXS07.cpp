#include "IsGISAXS07.h"
#include "Rotate3D.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "FormFactorBox.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "OutputDataIOFactory.h"
#include "PositionParticleInfo.h"
#include "Utils.h"
#include "Units.h"
#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS07::IsGISAXS07()
    : m_name("IsGISAXS07")
    , m_description("Mixture of different particles defined in morphology file")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS07::run()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration;

    // add particle number 1:
    FormFactorBox ff1(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos1(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    PositionParticleInfo particle_info1(new Particle(n_particle, ff1), pos1, 0.5);
    particle_decoration.addParticleInfo(particle_info1);
    // add particle number 2:
    FormFactorBox ff2(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m2( new Geometry::RotateZ_3D(10*Units::degree));
    PositionParticleInfo particle_info2(new Particle(n_particle, ff2), m2, pos2, 0.5);
    particle_decoration.addParticleInfo(particle_info2);
    // add particle number 3:
    FormFactorBox ff3(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos3(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m3( new Geometry::RotateZ_3D(20*Units::degree));
    PositionParticleInfo particle_info3(new Particle(n_particle, ff3), m3, pos3, 0.5);
    particle_decoration.addParticleInfo(particle_info3);
    // add particle number 4:
    FormFactorBox ff4(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos4(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m4( new Geometry::RotateZ_3D(30*Units::degree));
    PositionParticleInfo particle_info4(new Particle(n_particle, ff4), m4, pos4, 0.5);
    particle_decoration.addParticleInfo(particle_info4);
    // add particle number 5:
    FormFactorBox ff5(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos5(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m5( new Geometry::RotateZ_3D(40*Units::degree));
    PositionParticleInfo particle_info5(new Particle(n_particle, ff5), m5, pos5, 0.5);
    particle_decoration.addParticleInfo(particle_info5);
    // add particle number 6:
    FormFactorBox ff6(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos6(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m6( new Geometry::RotateZ_3D(50*Units::degree));
    PositionParticleInfo particle_info6(new Particle(n_particle, ff6), m6, pos6, 0.5);
    particle_decoration.addParticleInfo(particle_info6);
    // add particle number 7:
    FormFactorBox ff7(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos7(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m7( new Geometry::RotateZ_3D(60*Units::degree));
    PositionParticleInfo particle_info7(new Particle(n_particle, ff7), m7, pos7, 0.5);
    particle_decoration.addParticleInfo(particle_info7);
    // add particle number 8:
    FormFactorBox ff8(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos8(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m8( new Geometry::RotateZ_3D(70*Units::degree));
    PositionParticleInfo particle_info8(new Particle(n_particle, ff8), m8, pos8, 0.5);
    particle_decoration.addParticleInfo(particle_info8);
    // add particle number 9:
    FormFactorBox ff9(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos9(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m9( new Geometry::RotateZ_3D(80*Units::degree));
    PositionParticleInfo particle_info9(new Particle(n_particle, ff9), m9, pos9, 0.5);
    particle_decoration.addParticleInfo(particle_info9);
    // add particle number 10:
    FormFactorBox ff10(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos10(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::PTransform3D m10( new Geometry::RotateZ_3D(90*Units::degree));
    PositionParticleInfo particle_info10(new Particle(n_particle, ff10), m10, pos10, 0.5);
    particle_decoration.addParticleInfo(particle_info10);

    air_layer.setDecoration(particle_decoration);
    multi_layer.addLayer(air_layer);

    // ---------------------
    // building simulation
    // ---------------------
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 1.0*Units::degree,
                100, 0.0*Units::degree, 1.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.0*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::ISGISAXSMOR;
    simulation.setSimulationParameters(sim_params);

    // ---------------------
    // running simulation
    // ---------------------
    simulation.setSample(multi_layer);
    simulation.runSimulation();

    // ---------------------
    // copying data
    // ---------------------
    m_result = simulation.getOutputDataClone();
}

int FunctionalTests::IsGISAXS07::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);

    // retrieving reference data
    std::string filename = path_to_data + "isgisaxs07_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    delete reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold || std::isnan(diff)) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}

#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToExecutable(argv[0]) + "../../../ReferenceData/BornAgain/";
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS07 test;
    test.run();

    return test.analyseResults(GetPathToData(argc, argv));
}
#endif
