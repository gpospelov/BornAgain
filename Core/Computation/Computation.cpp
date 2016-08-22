// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Computation.cpp
//! @brief     Implements class Computation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Computation.h"
#include "MultiLayer.h"

Computation::Computation()
    : mp_simulation(nullptr)
{}

Computation::~Computation()
{
    delete mp_simulation;
}

void Computation::init(
    const SimulationOptions& options,
    const Simulation& simulation,
    std::vector<SimulationElement>::iterator begin_it,
    std::vector<SimulationElement>::iterator end_it)
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

bool Computation::checkPolarizationPresent() const
{
    if (!mp_simulation)
        throw Exceptions::ClassInitializationException("Computation::"
                "checkPolarizationPresent(): simulation not initialized");
    MultiLayer* p_sample = mp_simulation->getSample();
    if (!p_sample)
        throw Exceptions::ClassInitializationException("Computation::"
                "checkPolarizationPresent(): sample not initialized");
    return p_sample->containsMagneticMaterial();
}
