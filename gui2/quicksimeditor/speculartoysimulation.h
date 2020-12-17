//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/quicksimeditor/speculartoysimulation.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"
#include "mvvm/utils/progresshandler.h"
#include <memory>
#include <vector>

class SpecularScalarTanhStrategy;

namespace gui2 {

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class DAREFLCORE_EXPORT SpecularToySimulation {
public:
    ~SpecularToySimulation();

    SpecularToySimulation(const SimulationInput& input_data);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    SimulationResult simulationResult() const;

    static SLDProfile sld_profile(const multislice_t& multislice, int n_points);

private:
    size_t scanPointsCount() const;

    ModelView::ProgressHandler m_progressHandler;
    SimulationInput m_inputData;
    SimulationResult m_specularResult;

    std::unique_ptr<SpecularScalarTanhStrategy> m_strategy;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
