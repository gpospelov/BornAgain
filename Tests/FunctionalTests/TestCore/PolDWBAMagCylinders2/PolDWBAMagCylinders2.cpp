#include "FunctionalTestRegistry.h"
#include "FileSystem.h"
#include "OutputDataFunctions.h"
#include "OutputDataIOFactory.h"
#include "SimulationRegistry.h"

int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);

    SimulationRegistry sim_registry;
    Simulation* simulation = sim_registry.createSimulation("magcyl2");
    simulation->runSimulation();
    simulation->normalize();

    OutputData<double> *reference00 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_00.txt.gz");
    OutputData<double> *reference01 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_01.txt.gz");
    OutputData<double> *reference10 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_10.txt.gz");
    OutputData<double> *reference11 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_11.txt.gz");

    const double threshold(2e-10);
    double diff(0);
    diff += OutputDataFunctions::GetDifference(*simulation->getPolarizedIntensityData(0,0),*reference00);
    diff += OutputDataFunctions::GetDifference(*simulation->getPolarizedIntensityData(0,1),*reference01);
    diff += OutputDataFunctions::GetDifference(*simulation->getPolarizedIntensityData(1,0),*reference10);
    diff += OutputDataFunctions::GetDifference(*simulation->getPolarizedIntensityData(1,1),*reference11);
    diff /= 4.;

    delete simulation;
    delete reference00;
    delete reference01;
    delete reference10;
    delete reference11;

    // Assess result.
    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << "magcyl2" << " " << "Magnetic cylinders with non-zero magnetic field" << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}
