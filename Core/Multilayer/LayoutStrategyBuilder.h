// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayoutStrategyBuilder.h
//! @brief     Defines class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LAYOUTSTRATEGYBUILDER_H
#define LAYOUTSTRATEGYBUILDER_H

#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include "HomogeneousRegion.h"
#include <map>
#include <memory>

class FormFactorCoherentSum;
class IFormFactor;
class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class ILayout;
class IParticle;
class IMultiLayerFresnelMap;
class MultiLayer;
class ProcessedSample;

//! Methods to generate a simulation strategy for a ParticleLayoutComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayoutStrategyBuilder
{
public:
    LayoutStrategyBuilder(
        const MultiLayer* p_multilayer, const ProcessedSample* p_sample, const ILayout* p_layout,
        const IMultiLayerFresnelMap* p_fresnel_map, bool polarized,
        const SimulationOptions& sim_params, size_t layer_index);

    ~LayoutStrategyBuilder();

    IInterferenceFunctionStrategy* releaseStrategy();

    std::map<size_t, std::vector<HomogeneousRegion>> regionMap() const;

private:
    void createStrategy();
    SafePointerVector<class FormFactorCoherentSum> collectFormFactorList();
    FormFactorCoherentSum* createFormFactorCoherentSum(const IParticle* particle);
    void mergeRegionMap(const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
    void checkInterferenceFunction(const IInterferenceFunction* p_iff);

    const MultiLayer* mp_multilayer;
    const ProcessedSample* mp_sample;
    const ILayout* mp_layout;
    //! R and T coefficients for DWBA
    const IMultiLayerFresnelMap* mp_fresnel_map;
    bool m_polarized;  //!< polarized computation required?
    SimulationOptions m_sim_params;
    size_t m_layer_index;
    std::unique_ptr<IInterferenceFunctionStrategy> mP_strategy;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor);

#endif // LAYOUTSTRATEGYBUILDER_H
