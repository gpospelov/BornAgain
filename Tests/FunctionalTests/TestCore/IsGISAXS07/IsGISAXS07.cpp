#include "IsGISAXS07.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "IsGISAXSMorphologyFileDecoration.h"
#include "FormFactorBox.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"
#include "OutputDataIOFactory.h"
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
    // ---------------------
    // building sample
    // ---------------------
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    complex_t n_particle(1.0-6e-4, 2e-8);
    IsGISAXSMorphologyFileDecoration particle_decoration;
    // add particle number 1:
    FormFactorBox ff1(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos1(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    particle_decoration.addParticle(new Particle(n_particle, ff1), 0, pos1, 0.5); 
    // add particle number 2:
    FormFactorBox ff2(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot2(10*Units::degree);
    Particle particle2(n_particle, ff2);
    particle_decoration.addParticle(particle2, rot2, pos2, 0.5);
    // add particle number 3:
    FormFactorBox ff3(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos3(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot3(20*Units::degree);
    Particle particle3(n_particle, ff3);
    particle_decoration.addParticle(particle3, rot3, pos3, 0.5);
    // add particle number 4:
    FormFactorBox ff4(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos4(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot4(30*Units::degree);
    Particle particle4(n_particle, ff4);
    particle_decoration.addParticle(particle4, rot4, pos4, 0.5);
    // add particle number 5:   
    FormFactorBox ff5(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos5(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot5(40*Units::degree);
    Particle particle5(n_particle, ff5);
    particle_decoration.addParticle(particle5, rot5, pos5, 0.5);
    // add particle number 6:
    FormFactorBox ff6(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos6(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot6(50*Units::degree);
    Particle particle6(n_particle, ff6);
    particle_decoration.addParticle(particle6, rot6, pos6, 0.5); 
    // add particle number 7:
    FormFactorBox ff7(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos7(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot7(60*Units::degree);
    Particle particle7(n_particle, ff7);
    particle_decoration.addParticle(particle7, rot7, pos7, 0.5);
    // add particle number 8:
    FormFactorBox ff8(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos8(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot8(70*Units::degree);
    Particle particle8(n_particle, ff8);
    particle_decoration.addParticle(particle8, rot8, pos8, 0.5);
    // add particle number 9:
    FormFactorBox ff9(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos9(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot9(80*Units::degree);
    Particle particle9(n_particle, ff9);
    particle_decoration.addParticle(particle9, rot9, pos9, 0.5);
    // add particle number 10:
    FormFactorBox ff10(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos10(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot10(90*Units::degree);
    Particle particle10(n_particle, ff10);
    particle_decoration.addParticle(particle10, rot10, pos10, 0.5);

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);
    // ---------------------
    // building experiment
    // ---------------------
    GISASExperiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 1.0*Units::degree,
                100, 0.0*Units::degree, 1.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, 0.0*Units::degree, 0.0*Units::degree);

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

int FunctionalTests::IsGISAXS07::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data
    std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS07/isgisaxs07_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    /*
     std::vector< CompareStruct > tocompare;
     tocompare.push_back( CompareStruct("isgi_morphology.ima.gz") );

     for(size_t i=0; i<tocompare.size(); ++i) {
         OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
         OutputData<double> *our_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);

         std::ostringstream os;
         os<<i;
         std::string cname = getName()+"_c"+os.str();
        }
*/

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
    FunctionalTests::IsGISAXS07 test;
    test.run();

    return test.analyseResults();
}
#endif
