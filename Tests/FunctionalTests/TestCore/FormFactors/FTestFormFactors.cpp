#include "FTestFormFactors.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "FileSystem.h"
#include "MathFunctions.h"
#include <iostream>
#include <cmath>

#include "OutputDataIOFactory.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactors.h"
#include "InterferenceFunctionNone.h"

FunctionalTests::FTestFormFactors::FTestFormFactors()
    : m_name("FTestFormFactors")
    , m_description("Test of form factors implemented in BornAgain")
    , mp_form_factor(0)
{
    m_results.resize(kNumberOfTests, 0);
}

FunctionalTests::FTestFormFactors::~FTestFormFactors()
{
   for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) delete (*it);
}

// FormFactors functional test: particles in the air
// (different shapes but only one at a time)
void FunctionalTests::FTestFormFactors::run(IFormFactor *p_form_factor)
{
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    //building sample
    MultiLayer multi_layer;
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    mp_form_factor=p_form_factor;
    ParticleDecoration particle_decoration( new Particle(particle_material,
                                                         mp_form_factor));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    air_layer.setDecoration(particle_decoration);
    multi_layer.addLayer(air_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree,
                                     true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();

    if (mp_form_factor->getName().substr(10) == "Cylinder")
    m_results[kTest_Cylinder] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Box")
    m_results[kTest_Box] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Cone")
    m_results[kTest_Cone] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Cone6")
    m_results[kTest_Cone6] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "FullSphere")
    m_results[kTest_FullSphere] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Parallelepiped")
    m_results[kTest_Parallelepiped] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Prism3")
    m_results[kTest_Prism3] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Prism6")
    m_results[kTest_Prism6] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Pyramid")
    m_results[kTest_Pyramid] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Sphere")
    m_results[kTest_Sphere] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Tetrahedron")
    m_results[kTest_Tetrahedron] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Cuboctahedron")
    m_results[kTest_Cuboctahedron] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "AnisoPyramid")
    m_results[kTest_AnisoPyramid] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "EllipsoidalCylinder")
    m_results[kTest_Ellipscyl] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "FullSpheroid")
    m_results[kTest_FullSpheroid] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "Spheroid")
    m_results[kTest_Spheroid] = simulation.getIntensityData();

    if (mp_form_factor->getName().substr(10) == "HemiEllipsoid")
    m_results[kTest_HemiEllipsoid] = simulation.getIntensityData();

}

int FunctionalTests::FTestFormFactors::analyseResults(const std::string &path_to_data)
{         
    const double threshold(2e-10);
    const char *reference_files[kNumberOfTests] =
    {"isgi_reference_cylinder_BA.ima.gz",
     "isgi_reference_box_BA.ima.gz",
     "isgi_reference_cone_BA.ima.gz",
     "isgi_reference_cone6_BA.ima.gz",
     "isgi_reference_full_sphere_BA.ima.gz",
     "isgi_reference_parallelepiped_BA.ima.gz",
     "isgi_reference_prism3_BA.ima.gz",
     "isgi_reference_prism6_BA.ima.gz",
     "isgi_reference_pyramid_BA.ima.gz",
     "isgi_reference_sphere_BA.ima.gz",
     "isgi_reference_tetrahedron_BA.ima.gz",
     "isgi_reference_cuboctahedron_BA.ima.gz",
     "isgi_reference_anisopyramid_BA.ima.gz",
     "isgi_reference_ellipscylinder_BA.ima.gz",
     "isgi_reference_full_spheroid_BA.ima.gz",
     "isgi_reference_spheroid_BA.ima.gz",
     "isgi_reference_hemiellipsoid_BA.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
       OutputData<double> *reference = OutputDataIOFactory::readIntensityData(
                   path_to_data + reference_files[i_test]);
       OutputData<double> *result = m_results[i_test];

       // calculating average relative difference
       *result -= *reference;
       *result /= *reference;
       delete reference;

       double diff(0);
       for(OutputData<double>::const_iterator it=result->begin();
           it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
     diff /= result->getAllocatedSize();
     if( diff > threshold || MathFunctions::isnan(diff)) status_ok=false;

    }

   /* std::cout << m_name << " " << m_description << " "
              << (status_ok ? "[OK]" : "[FAILED]") << std::endl;*/
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
   return Utils::FileSystem::GetPathToData("../../../ReferenceData/BornAgain/",
                                           argv[0]);
}

int main(int argc, char **argv)
{
    FunctionalTests::FTestFormFactors test;
    //Cylinder
    FormFactorCylinder ff_cyl(5.0, 5.0);
    IFormFactor* p_ff_cyl =& ff_cyl;
    test.run(p_ff_cyl->clone());

    //Box
    FormFactorBox ff_box(10.0, 20.0, 5.0);
    IFormFactor* p_ff_box =& ff_box;
    test.run(p_ff_box->clone());

    //Cone
    FormFactorCone ff_cone(5.0, 5.0, Units::deg2rad(54.73 ));
    IFormFactor* p_ff_cone =& ff_cone;
    test.run(p_ff_cone->clone());

    //Cone6
    FormFactorCone6 ff_cone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73));
    IFormFactor* p_ff_cone6 =& ff_cone6;
    test.run(p_ff_cone6->clone());

    //FullSphere
    FormFactorFullSphere ff_fsph(5.0);
    IFormFactor* p_ff_fsph =& ff_fsph;
    test.run(p_ff_fsph->clone());

    //Parallelepiped
    FormFactorParallelepiped ff_par(10.0, 5.0);
    IFormFactor* p_ff_par =& ff_par;
    test.run(p_ff_par->clone());

    //Prism3
    FormFactorPrism3 ff_pr3(10.0, 5.0);
    IFormFactor* p_ff_pr3 =& ff_pr3;
    test.run(p_ff_pr3->clone());

    //Prism6
    FormFactorPrism6 ff_pr6(2./sqrt(3.)*5.0, 5.0);
    IFormFactor* p_ff_pr6 =& ff_pr6;
    test.run(p_ff_pr6->clone());

    //Pyramid
    FormFactorPyramid ff_pyr(10.0, 5.0, Units::deg2rad(54.73 ));//(5.0, 5.0, Units::deg2rad(54.73 ));
    IFormFactor* p_ff_pyr =& ff_pyr;
    test.run(p_ff_pyr->clone());

    //Sphere
    FormFactorSphere ff_sph(5.0, 5.0);
    IFormFactor* p_ff_sph =& ff_sph;
    test.run(p_ff_sph->clone());

    // Tetrahedron
    FormFactorTetrahedron ff_tetr(10.0, 4.0, Units::deg2rad(54.73 ));
    IFormFactor* p_ff_tetr =& ff_tetr;
    test.run(p_ff_tetr->clone());

    // Cuboctahedron
    FormFactorCuboctahedron ff_cuboc(10.0, 5.0, 1.0, Units::deg2rad(54.73 ));
    IFormFactor* p_ff_cuboc =& ff_cuboc;
    test.run(p_ff_cuboc->clone());

    // Anisotropic Pyramid
    FormFactorAnisoPyramid  ff_anipyr(10.0, 20.0, 5.0, Units::deg2rad(54.73 ));
    IFormFactor* p_ff_anipyr =& ff_anipyr;
    test.run(p_ff_anipyr->clone());

    // Ellipsoidal Cylinder
    FormFactorEllipsoidalCylinder ff_ellipscyl(5.0, 10.0, 5.0);
    IFormFactor* p_ff_ellipscyl =& ff_ellipscyl;
    test.run(p_ff_ellipscyl->clone());

    // Full spheroid
    FormFactorFullSpheroid ff_fspheroid(5.0, 5.0);
    IFormFactor* p_ff_fspheroid =& ff_fspheroid;
    test.run(p_ff_fspheroid ->clone());

    // Spheroid
    FormFactorSpheroid  ff_spheroid(5.0, 5.0, 1.0);
    IFormFactor* p_ff_spheroid =& ff_spheroid;
    test.run(p_ff_spheroid->clone());

    // HemiEllipsoid
    FormFactorHemiEllipsoid  ff_hemiellipsoid(5.0, 10.0, 5.0);
    IFormFactor* p_ff_hemiellipsoid=& ff_hemiellipsoid;
    test.run(p_ff_hemiellipsoid->clone());

    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

