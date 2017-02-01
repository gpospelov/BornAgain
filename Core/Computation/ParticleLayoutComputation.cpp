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
#include "DelayedProgressCounter.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "ILayerSpecularInfo.h"
#include "ILayout.h"
#include "LayerStrategyBuilder.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(const MultiLayer* p_multilayer,
                                                     const ILayout* p_layout, size_t layer_index)
    : IComputationTerm(p_multilayer)
    , mp_layout(p_layout)
    , m_layer_index(layer_index)
{}

//! Computes scattering intensity for given range of simulation elements.
bool ParticleLayoutComputation::eval(
    const SimulationOptions& options,
    ProgressHandler* progress,
    bool polarized,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    const std::unique_ptr<const IInterferenceFunctionStrategy> p_strategy {
        LayerStrategyBuilder(mp_multilayer, mp_layout, (*mp_specular_info_map)[m_layer_index],
                             polarized, options, m_layer_index).createStrategy() };
    double total_surface_density = mp_layout->getTotalParticleSurfaceDensity();

    DelayedProgressCounter counter(100);
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return false;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_multilayer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0) {
            it->setIntensity(0.0); // zero for transmission with multilayers (n>1)
        } else {
            it->setIntensity(p_strategy->evaluate(*it) * total_surface_density);
        }
        counter.stepProgress(progress);
    }
    return true;
}
