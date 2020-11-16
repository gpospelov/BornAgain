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

#include "Core/Computation/ParticleLayoutComputation.h"
#include "Base/Pixel/SimulationElement.h"
#include "Base/Types/Exceptions.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Interference/DecouplingApproximationStrategy.h"
#include "Sample/Interference/SSCApproximationStrategy.h"

namespace
{

std::unique_ptr<IInterferenceFunctionStrategy>
processedInterferenceFunction(const ProcessedLayout& layout, const SimulationOptions& sim_params,
                              bool polarized)
{
    const IInterferenceFunction* p_iff = layout.interferenceFunction();
    if (p_iff && layout.numberOfSlices() > 1 && !p_iff->supportsMultilayer())
        throw std::runtime_error("LayoutStrategyBuilder::checkInterferenceFunction: "
                                 "interference function does not support multiple layers");

    auto p_radial_para = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(p_iff);

    const std::vector<FormFactorCoherentSum>& weighted_formfactors = layout.formFactorList();

    std::unique_ptr<IInterferenceFunctionStrategy> result;

    if (p_radial_para && p_radial_para->kappa() > 0.0) {
        double kappa = p_radial_para->kappa();
        return std::make_unique<SSCApproximationStrategy>(weighted_formfactors, p_iff, sim_params,
                                                          polarized, kappa);
    }
    return std::make_unique<DecouplingApproximationStrategy>(weighted_formfactors, p_iff,
                                                             sim_params, polarized);
}

} // namespace

ParticleLayoutComputation::ParticleLayoutComputation(const ProcessedLayout& layout,
                                                     const SimulationOptions& options,
                                                     bool polarized)
    : m_layout(layout)
    , m_region_map(layout.regionMap())
    , m_interference_function_strategy(processedInterferenceFunction(layout, options, polarized))
{
}

ParticleLayoutComputation::~ParticleLayoutComputation() = default;

void ParticleLayoutComputation::compute(SimulationElement& elem) const
{
    const double alpha_f = elem.getAlphaMean();
    const size_t n_layers = m_layout.numberOfSlices();
    if (n_layers > 1 && alpha_f < 0)
        return; // zero for transmission with multilayers (n>1) # TODO: support transmission GISAS

    elem.addIntensity(m_interference_function_strategy->evaluate(elem) * m_layout.surfaceDensity());
}

void ParticleLayoutComputation::mergeRegionMap(
    std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const
{
    for (auto& entry : m_region_map) {
        size_t i = entry.first;
        auto& regions = entry.second;
        region_map[i].insert(region_map[i].begin(), regions.begin(), regions.end());
    }
}
