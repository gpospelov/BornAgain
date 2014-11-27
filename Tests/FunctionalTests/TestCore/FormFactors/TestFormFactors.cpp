#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "FileSystem.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactors.h"
#include "InterferenceFunctionNone.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cmath>


OutputData<double> *run_simulation(IFormFactor *form_factor)
{
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    MultiLayer multi_layer;
    Layer air_layer;
    air_layer.setMaterial(air_material);

    Particle particle(particle_material, *form_factor);
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());
    air_layer.addLayout(particle_layout);
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
    return simulation.getIntensityData();
}


int run_tests()
{
    const double threshold(2e-10);

    std::map<IFormFactor *, std::string> test_map;

    test_map[new FormFactorCylinder(5.0, 5.0)] = "ffba_cylinder_reference.int.gz";
    test_map[new FormFactorBox(10.0, 20.0, 5.0)] = "ffba_box_reference.int.gz";
    test_map[new FormFactorCone(5.0, 5.0, Units::deg2rad(54.73 ))] = "ffba_cone_reference.int.gz";
    test_map[new FormFactorCone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73))] = "ffba_cone6_reference.int.gz";
    test_map[new FormFactorFullSphere(5.0)] = "ffba_fullsphere_reference.int.gz";
    test_map[new FormFactorPrism3(10.0, 5.0)] = "ffba_prism3_reference.int.gz";
    test_map[new FormFactorPrism6(2./sqrt(3.)*5.0, 5.0)] = "ffba_prism6_reference.int.gz";
    test_map[new FormFactorPyramid(10.0, 5.0, Units::deg2rad(54.73 ))] = "ffba_pyramid_reference.int.gz";
    test_map[new FormFactorTruncatedSphere(5.0, 5.0)] = "ffba_sphere_reference.int.gz";
    test_map[new FormFactorTetrahedron(10.0, 4.0, Units::deg2rad(54.73 ))] = "ffba_tetrahedron_reference.int.gz";
    test_map[new FormFactorCuboctahedron(10.0, 5.0, 1.0, Units::deg2rad(54.73 ))] = "ffba_cuboctahedron_reference.int.gz";
    test_map[new FormFactorAnisoPyramid(10.0, 20.0, 5.0, Units::deg2rad(54.73 ))] = "ffba_anisopyramid_reference.int.gz";
    test_map[new FormFactorEllipsoidalCylinder(5.0, 10.0, 5.0)] = "ffba_ellipscylinder_reference.int.gz";
    test_map[new FormFactorFullSpheroid(5.0, 5.0)] = "ffba_fullspheroid_reference.int.gz";
    test_map[new FormFactorTruncatedSpheroid(5.0, 5.0, 1.0)] = "ffba_spheroid_reference.int.gz";
    test_map[new FormFactorHemiEllipsoid(5.0, 10.0, 5.0)] = "ffba_hemiellipsoid_reference.int.gz";

    bool success(true);
    for(std::map<IFormFactor *, std::string>::iterator it = test_map.begin(); it!= test_map.end(); ++it) {
        OutputData<double> *result = run_simulation(it->first);
        OutputData<double> *reference = IntensityDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir() + it->second);

        double diff = IntensityDataFunctions::getRelativeDifference(*result, *reference);
        std::ostringstream sdiff;
        sdiff << std::setprecision(4) << diff;

        std::string status("OK");
        if(diff > threshold) {
            status = "FAILED";
            success = false;
        }

        std::cout << Utils::AdjustStringLength(it->first->getName(), 30)
                  << " " << Utils::AdjustStringLength(it->second, 40)
                  << " " << Utils::AdjustStringLength(sdiff.str(), 10)
                  << "   " << status
                  << std::endl;

        delete result;
        delete reference;
    }

    return (success ? 0 : 1);
}


int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);
    return run_tests();
}
