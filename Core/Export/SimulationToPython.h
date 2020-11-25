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

class SimulationToPython {
public:
    enum EMainType {
        RUN_SIMULATION, //!< main function runs simulation
        SAVE_DATA       //!< main function saves intensity data
    };

    std::string generateSimulationCode(const ISimulation& simulation, EMainType mainType);
};

#endif // BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
