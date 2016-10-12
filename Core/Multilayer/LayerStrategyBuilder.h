// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerStrategyBuilder.h
//! @brief     Defines class LayerStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSTRATEGYBUILDER_H
#define LAYERSTRATEGYBUILDER_H

#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include <memory>

class WeightedFormFactor;
class IInterferenceFunctionStrategy;
class IMaterial;
class IParticle;
class Layer;
class LayerSpecularInfo;
class MultiLayer;

//! Methods to generate a simulation strategy for DecoratedLayerComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer& decorated_layer, const MultiLayer& sample,
        const SimulationOptions& sim_params, size_t layout_index);

    virtual ~LayerStrategyBuilder();

    void setRTInfo(const LayerSpecularInfo& specular_info);
    virtual IInterferenceFunctionStrategy* createStrategy();

protected:
    std::unique_ptr<class Layer> mP_layer;                     //!< decorated layer
    std::unique_ptr<class MultiLayer> mP_sample;               //!< sample
    SimulationOptions m_sim_params;                            //!< simulation parameters
    std::unique_ptr<class LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
    size_t m_layout_index; //!< index for the layout to be used in the layer

private:
    bool requiresMatrixFFs() const;
    void collectWeightedFormFactors();
    void collectInterferenceFunction();
    WeightedFormFactor* createWeightedFormFactor(
        const IParticle* particle, const IMaterial* p_ambient_material) const;

    SafePointerVector<class WeightedFormFactor> m_weighted_ffs;
    std::unique_ptr<class IInterferenceFunction> mP_interference_function;
};

#endif // LAYERSTRATEGYBUILDER_H
