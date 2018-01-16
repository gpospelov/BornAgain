// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.cpp
//! @brief     Implements ExportToPython namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ExportToPython.h"
#include "SimulationToPython.h"
#include "GISASSimulation.h"

namespace {
std::string simulationCode(const GISASSimulation& simulation,
                           SimulationToPython::EMainType mainFunctionType)
{
    std::unique_ptr<GISASSimulation> sim(simulation.clone());
    sim->prepareSimulation();

    SimulationToPython generator;
    return generator.generateSimulationCode(*sim, mainFunctionType);
}
}

std::string ExportToPython::generateSampleCode(const MultiLayer& multilayer)
{
    SimulationToPython generator;
    return generator.generateSampleCode(multilayer);
}

std::string ExportToPython::generateSimulationCode(const GISASSimulation& simulation)
{
    return simulationCode(simulation, SimulationToPython::RUN_SIMULATION);
}

std::string ExportToPython::generatePyExportTest(const GISASSimulation& simulation)
{
    return simulationCode(simulation, SimulationToPython::SAVE_DATA);
}
