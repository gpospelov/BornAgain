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

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
#define BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H

#include <string>

class ISimulation;

//! Write a Python script that allows to run the current simulation.

class SimulationToPython {
public:
    //! Returns a Python script that runs a simulation and plots the result
    std::string simulationPlotCode(const ISimulation& simulation);
    //! Returns a Python script that runs a simulation and saves the result to a file
    std::string simulationSaveCode(const ISimulation& simulation, const std::string& fname);
};

#endif // BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
#endif // USER_API
