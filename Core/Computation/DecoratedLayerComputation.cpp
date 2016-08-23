// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DecoratedLayerComputation.cpp
//! @brief     Implements class DecoratedLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecoratedLayerComputation.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "LayerStrategyBuilder.h"
#include "Logger.h"
#include "Simulation.h"
#include "SimulationElement.h"

DecoratedLayerComputation::DecoratedLayerComputation(const Layer* p_layer, size_t layout_index)
    : mp_specular_info(nullptr), m_layout_index(layout_index)
{
    mp_layer = p_layer->clone();
}

DecoratedLayerComputation::~DecoratedLayerComputation()
{
    delete mp_layer;
    delete mp_specular_info;
}

void DecoratedLayerComputation::run()
{
    try {
        msglog(MSG::DEBUG2) << "LayerDecoratorComputation::runProtected()";
        const std::unique_ptr<const IInterferenceFunctionStrategy>
            P_strategy(createAndInitStrategy());
        calculateCoherentIntensity(P_strategy.get());
    } catch (const std::exception& ex) {
        throw Exceptions::RuntimeErrorException(
            "DecoratedLayerComputation::run() -> Exception was caught:\n" +
            std::string(ex.what()));
    }
}

IInterferenceFunctionStrategy* DecoratedLayerComputation::createAndInitStrategy() const
{
    LayerStrategyBuilder builder(*mp_layer, *mp_simulation->getSample(),
                                 m_sim_options, m_layout_index);
    assert(mp_specular_info);
    builder.setRTInfo(*mp_specular_info);
    IInterferenceFunctionStrategy* p_strategy = builder.createStrategy();
    return p_strategy;
}

void DecoratedLayerComputation::calculateCoherentIntensity(
    const IInterferenceFunctionStrategy* p_strategy)
{
    msglog(MSG::DEBUG2) << "LayerDecoratorComputation::calculateCoh...()";
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    bool polarization_present = checkPolarizationPresent();

    for (std::vector<SimulationElement>::iterator it = m_begin_it; it != m_end_it; ++it) {
        if (!m_progress.update())
            break;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0)
            continue;
        // each ffdwba: one call to getOutCoeffs
        if (polarization_present)
            it->setIntensity(p_strategy->evaluatePol(*it) * total_surface_density);
        else
            it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
    }
    m_progress.finished();
}

void DecoratedLayerComputation::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    if (mp_specular_info != &specular_info) {
        delete mp_specular_info;
        mp_specular_info = specular_info.clone();
    }
}
