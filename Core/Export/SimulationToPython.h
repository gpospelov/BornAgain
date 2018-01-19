// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SimulationToPython.h
//! @brief     Defines class SimulationToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONTOPYTHON_H
#define SIMULATIONTOPYTHON_H

#include "WinDllMacros.h"
#include <memory>
#include <string>

class Simulation;
class GISASSimulation;

//! Write a Python script that allows to run the current simulation.

class BA_CORE_API_ SimulationToPython
{
public:
    enum EMainType {
        RUN_SIMULATION, //!< main function runs simulation
        SAVE_DATA       //!< main function saves intensity data
    };

    std::string generateSimulationCode(const Simulation& simulation, EMainType mainType);

private:
    std::string definePreamble() const;
    std::string defineGetSimulation(const Simulation* simulation) const;
    std::string defineGISASSimulation(const GISASSimulation* simulation) const;
    std::string defineDetector(const Simulation* simulation) const;
    std::string defineDetectorResolutionFunction(const Simulation* simulation) const;
    std::string defineDetectorPolarizationAnalysis(const Simulation* simulation) const;
    std::string defineBeam(const Simulation* simulation) const;
    std::string defineParameterDistributions(const Simulation* simulation) const;
    std::string defineMasks(const Simulation* simulation) const;
    std::string defineSimulationOptions(const Simulation* simulation) const;
    std::string defineBackground(const Simulation* simulation) const;
    std::string defineMain(EMainType mainType = RUN_SIMULATION);

    std::string indent() const;
};

#endif // SIMULATIONTOPYTHON_H
