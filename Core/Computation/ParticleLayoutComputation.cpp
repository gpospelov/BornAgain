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
#include "ILayout.h"
#include "LayerStrategyBuilder.h"
#include "Logger.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(const Layer* p_layer, const ILayout* p_layout)
    : mp_layer(p_layer)
    , mp_layout(p_layout)
    , mp_specular_info(nullptr)
{
}

void ParticleLayoutComputation::setSpecularInfo(const ILayerSpecularInfo* p_specular_info)
{
    mp_specular_info = p_specular_info;
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
        LayerStrategyBuilder(mp_layer, mp_layout, mp_specular_info,
                             polarized, options).createStrategy() };
    double total_surface_density = mp_layout->getTotalParticleSurfaceDensity();

    DelayedProgressCounter counter(100);
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0)  // skip transmission for multilayers (n>1)
            continue;
        it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
        counter.stepProgress(progress);
    }
}
