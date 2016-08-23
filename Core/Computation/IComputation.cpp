// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/IComputation/IComputation.cpp
//! @brief     Implements class IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific IComputing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IComputation.h"
#include "Simulation.h"

IComputation::IComputation()
    : mp_simulation(nullptr)
{}

IComputation::~IComputation()
{
    delete mp_simulation;
}

void IComputation::init(
    const SimulationOptions& options,
    const Simulation& simulation,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
{
    m_sim_options = options;
    if (mp_simulation != &simulation) {
        delete mp_simulation;
        mp_simulation = simulation.clone();
    }
    m_begin_it = begin_it;
    m_end_it = end_it;

    // initialising call backs
    mp_simulation->initProgressHandlerDWBA(&m_progress);
}
