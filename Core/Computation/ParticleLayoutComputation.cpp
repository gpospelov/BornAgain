// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.cpp
//! @brief     Implements class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayoutComputation.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "Layer.h"
#include "ILayerSpecularInfo.h"
#include "LayerStrategyBuilder.h"
#include "Logger.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(const Layer* p_layer, size_t layout_index)
    : mp_layer(p_layer), m_layout_index(layout_index)
{}

void ParticleLayoutComputation::setSpecularInfo(const ILayerSpecularInfo& specular_info)
{
    if (&specular_info != mP_specular_info.get())
        mP_specular_info.reset(specular_info.clone());
}

//! Computes scattering intensity for given range of simulation elements.
void ParticleLayoutComputation::eval(
    const SimulationOptions& options,
    ProgressHandler* progress,
    bool polarized,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    const std::unique_ptr<const IInterferenceFunctionStrategy> p_strategy {
        LayerStrategyBuilder(*mp_layer, mp_layer->getLayout(m_layout_index), polarized, options,
                             mP_specular_info.get()).createStrategy() };
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    DelayedProgressCounter counter(100);
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0)
            continue;
        // each ffdwba: one call to getOutCoeffs
        it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
        counter.stepProgress(progress);
    }
}
