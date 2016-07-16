// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/DecoratedLayerDWBASimulation.cpp
//! @brief     Implements class DecoratedLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecoratedLayerDWBASimulation.h"
#include "Layer.h"
#include "LayerStrategyBuilder.h"
#include "MessageService.h"
#include "IInterferenceFunctionStrategy.h"

DecoratedLayerDWBASimulation::DecoratedLayerDWBASimulation(
    const Layer* p_layer, size_t layout_index)
    : LayerDWBASimulation(p_layer), m_layout_index(layout_index)
{
}

DecoratedLayerDWBASimulation::~DecoratedLayerDWBASimulation()
{
}

void DecoratedLayerDWBASimulation::run()
{
    setStatus(RUNNING);
    try {
        runProtected();
        setStatus(COMPLETED);
    } catch (const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(FAILED);
        throw Exceptions::RuntimeErrorException(
            "DecoratedLayerDWBASimulation::run() -> Exception was caught \n\n" + getRunMessage());
    }
}

void DecoratedLayerDWBASimulation::runProtected()
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::runProtected()";
    const std::unique_ptr<const IInterferenceFunctionStrategy> P_strategy(createAndInitStrategy());

    calculateCoherentIntensity(P_strategy.get());
}

IInterferenceFunctionStrategy* DecoratedLayerDWBASimulation::createAndInitStrategy() const
{
    LayerStrategyBuilder builder(*mp_layer, *mp_simulation, m_sim_options, m_layout_index);
    assert(mp_specular_info);
    builder.setRTInfo(*mp_specular_info);
    IInterferenceFunctionStrategy* p_strategy = builder.createStrategy();
    return p_strategy;
}

void DecoratedLayerDWBASimulation::calculateCoherentIntensity(
    const IInterferenceFunctionStrategy* p_strategy)
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::calculateCoh...()";
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    bool polarization_present = checkPolarizationPresent();

    std::vector<SimulationElement>::iterator it = m_begin_it;
    while (it != m_end_it) {
        if (!m_progress.update())
            break;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0) {
            ++it;
            continue;
        }
        // each ffdwba: 1 call to getOutCoeffs
        if (polarization_present) {
            // matrix dwba calculation
            it->setIntensity(p_strategy->evaluatePol(*it) * total_surface_density);
        } else {
            // scalar dwba calculation
            it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
        }
        ++it;
    }
    m_progress.finished();
}
