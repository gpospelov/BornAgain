//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Export/ExportToPython.cpp
//! @brief     Implements ExportToPython namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/ExportToPython.h"
#include "Core/Export/SampleToPython.h"
#include "Core/Export/SimulationToPython.h"
#include "Core/Simulation/ISimulation.h"

std::string ExportToPython::sampleCode(const MultiLayer& multilayer) {
    return SampleToPython().sampleCode(multilayer);
}

std::string ExportToPython::simulationPlotCode(const ISimulation& simulation) {
    return SimulationToPython().simulationPlotCode(simulation);
}

std::string ExportToPython::simulationSaveCode(const ISimulation& simulation,
                                               const std::string& fname) {
    return SimulationToPython().simulationSaveCode(simulation, fname);
}
