// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.cpp
//! @brief     Implements class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleLayoutComputation.h"
#include "DelayedProgressCounter.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "IFresnelMap.h"
#include "ILayout.h"
#include "LayoutStrategyBuilder.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(
        const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map, const ILayout* p_layout,
        size_t layer_index, const SimulationOptions& options, bool polarized)
    : IComputationTerm(p_multilayer, p_fresnel_map)
{
    LayoutStrategyBuilder builder(mp_multilayer, p_layout, mp_fresnel_map,
                                  polarized, options, layer_index);
    mP_strategy.reset(builder.releaseStrategy());
    m_region_map = builder.regionMap();
    m_surface_density = p_layout->totalParticleSurfaceDensity();
}

void ParticleLayoutComputation::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

//! Computes scattering intensity for given range of simulation elements.
void ParticleLayoutComputation::eval(ProgressHandler* progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        double alpha_f = it->getAlphaMean();
        size_t n_layers = mp_multilayer->numberOfLayers();
        if (n_layers > 1 && alpha_f < 0) {
            continue; // zero for transmission with multilayers (n>1)
        } else {
            it->addIntensity(mP_strategy->evaluate(*it) * m_surface_density);
        }
        if (mP_progress_counter) {
            mP_progress_counter->stepProgress();
        }
    }
}

void ParticleLayoutComputation::operator()(SimulationElement& elem) const
{
    double alpha_f = elem.getAlphaMean();
    size_t n_layers = mp_multilayer->numberOfLayers();
    if (n_layers > 1 && alpha_f < 0) {
        return; // zero for transmission with multilayers (n>1)
    } else {
        elem.addIntensity(mP_strategy->evaluate(elem) * m_surface_density);
    }
    if (mP_progress_counter) {
        mP_progress_counter->stepProgress();
    }
}
