// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/PolDWBAMagCylinders.cpp
//! @brief     Implements PolDWBAMagCylinders class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PolDWBAMagCylinders.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "SimulationFactory.h"
#include "FileSystemUtils.h"
#include <memory>


bool PolDWBAMagCylinders::runTest()
{
    const std::string trunc = FileSystemUtils::jointPath(CORE_SPECIAL_REF_DIR,
                                                             "/polmagcylinders2_reference_");
    const std::unique_ptr<OutputData<double> >
        P_reference00(IntensityDataIOFactory::readOutputData(trunc + "00.int.gz"));
    const std::unique_ptr<OutputData<double> >
        P_reference01(IntensityDataIOFactory::readOutputData(trunc + "01.int.gz"));
    const std::unique_ptr<OutputData<double> >
        P_reference10(IntensityDataIOFactory::readOutputData(trunc + "10.int.gz"));
    const std::unique_ptr<OutputData<double> >
        P_reference11(IntensityDataIOFactory::readOutputData(trunc + "11.int.gz"));

    SimulationFactory sim_registry;
    auto simulation = sim_registry.create("polmagcylinders2");
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

    // Assess result.
    bool status_ok(true);
    if( diff > threshold )
        status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << "polmagcylinders2" << " " << "Magnetic cylinders with non-zero magnetic field"
              << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return status_ok;
}
