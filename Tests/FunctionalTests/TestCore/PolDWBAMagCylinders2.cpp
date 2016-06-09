#include "FileSystem.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "SimulationRegistry.h"
#include <memory>

int main(int, char **)
{
    const std::unique_ptr<OutputData<double> > P_reference00(IntensityDataIOFactory::readOutputData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_00.int.gz"));
    const std::unique_ptr<OutputData<double> > P_reference01(IntensityDataIOFactory::readOutputData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_01.int.gz"));
    const std::unique_ptr<OutputData<double> > P_reference10(IntensityDataIOFactory::readOutputData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_10.int.gz"));
    const std::unique_ptr<OutputData<double> > P_reference11(IntensityDataIOFactory::readOutputData(
        Utils::FileSystem::GetReferenceDataDir()+ "polmagcylinders2_reference_11.int.gz"));

    SimulationRegistry sim_registry;
    GISASSimulation* simulation = sim_registry.createSimulation("polmagcylinders2");
    kvector_t zplus(0.0, 0.0, 1.0);
    kvector_t zmin(0.0, 0.0, -1.0);

    simulation->setBeamPolarization(zplus);
    simulation->setAnalyzerProperties(zplus, 1.0, 0.5);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_data00(simulation->getDetectorIntensity());

    simulation->setBeamPolarization(zplus);
    simulation->setAnalyzerProperties(zplus, -1.0, 0.5);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_data01(simulation->getDetectorIntensity());

    simulation->setBeamPolarization(zmin);
    simulation->setAnalyzerProperties(zplus, 1.0, 0.5);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_data10(simulation->getDetectorIntensity());

    simulation->setBeamPolarization(zmin);
    simulation->setAnalyzerProperties(zplus, -1.0, 0.5);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_data11(simulation->getDetectorIntensity());

    const double threshold(2e-10);
    double diff(0);
    diff += IntensityDataFunctions::getRelativeDifference(*P_data00, *P_reference00);
    diff += IntensityDataFunctions::getRelativeDifference(*P_data01, *P_reference01);
    diff += IntensityDataFunctions::getRelativeDifference(*P_data10, *P_reference10);
    diff += IntensityDataFunctions::getRelativeDifference(*P_data11, *P_reference11);
    diff /= 4.;

    delete simulation;

    // Assess result.
    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << "polmagcylinders2" << " " << "Magnetic cylinders with non-zero magnetic field" << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}
