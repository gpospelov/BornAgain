//  ************************************************************************************************
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
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
#define BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H

#include <memory>
#include <string>

class Beam;
class IFootprintFactor;
class GISASSimulation;
class OffSpecSimulation;
class ISimulation;
class SpecularSimulation;

//! Write a Python script that allows to run the current simulation.

class SimulationToPython
{
public:
    enum EMainType {
        RUN_SIMULATION, //!< main function runs simulation
        SAVE_DATA       //!< main function saves intensity data
    };

    std::string generateSimulationCode(const ISimulation& simulation, EMainType mainType);

private:
    std::string definePreamble() const;
    std::string defineGetSimulation(const ISimulation* simulation) const;
    std::string defineGISASSimulation(const GISASSimulation* simulation) const;
    std::string defineOffSpecSimulation(const OffSpecSimulation* simulation) const;
    std::string defineSpecularSimulation(const SpecularSimulation* simulation) const;
    std::string defineDetector(const ISimulation* simulation) const;
    std::string defineDetectorResolutionFunction(const ISimulation* simulation) const;
    std::string defineDetectorPolarizationAnalysis(const ISimulation* simulation) const;

    std::string defineGISASBeam(const GISASSimulation& simulation) const;
    std::string defineOffSpecBeam(const OffSpecSimulation& simulation) const;
    std::string defineSpecularScan(const SpecularSimulation& simulation) const;

    std::string defineBeamPolarization(const Beam& beam) const;
    std::string defineBeamIntensity(const Beam& beam) const;

    std::string defineParameterDistributions(const ISimulation* simulation) const;
    std::string defineMasks(const ISimulation* simulation) const;
    std::string defineSimulationOptions(const ISimulation* simulation) const;
    std::string defineBackground(const ISimulation* simulation) const;
    std::string defineMain(EMainType mainType = RUN_SIMULATION);
};

#endif // BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
