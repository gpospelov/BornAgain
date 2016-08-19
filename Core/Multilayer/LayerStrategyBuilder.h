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

class FormFactorInfo;
class IInterferenceFunctionStrategy;
class IMaterial;
class IParticle;
class Layer;
class LayerSpecularInfo;
class MultiLayer;

//! Methods to generate a simulation strategy for decorated Layer SimulationParameters.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer& decorated_layer, const MultiLayer& sample,
        const SimulationOptions& sim_params, size_t layout_index);

    virtual ~LayerStrategyBuilder();

    //! Sets reflection/transmission map for DWBA calculation
    void setRTInfo(const LayerSpecularInfo& specular_info);

    //! Creates a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy* createStrategy();

protected:
    std::unique_ptr<class Layer> mP_layer;                     //!< decorated layer
    std::unique_ptr<class MultiLayer> mP_sample;               //!< sample
    SimulationOptions m_sim_params;                            //!< simulation parameters
    std::unique_ptr<class LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
    size_t m_layout_index; //!< index for the layout to be used in the layer

private:
    //! determines if the form factors need to be matrix valued
    bool requiresMatrixFFs() const;
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference function
    void collectInterferenceFunction();
    //! Creates formfactor info for single particle
    FormFactorInfo* createFormFactorInfo(
        const IParticle* particle, const IMaterial* p_ambient_material) const;

    //! Info about form factors
    SafePointerVector<class FormFactorInfo> m_ff_infos;

    //! Interference function
    std::unique_ptr<class IInterferenceFunction> mP_interference_function;
};

#endif // LAYERSTRATEGYBUILDER_H
