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

class FormFactorCoherentSum;
class IInterferenceFunctionStrategy;
class ILayout;
class IMaterial;
class IParticle;
class Layer;
class ILayerSpecularInfo;
class MultiLayer;

//! Methods to generate a simulation strategy for a ParticleLayoutComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer* p_layer, const ILayout* p_layout, const ILayerSpecularInfo* p_specular_info,
        bool polarized, const SimulationOptions& sim_params);

    ~LayerStrategyBuilder();

    IInterferenceFunctionStrategy* createStrategy() const;

private:
    SafePointerVector<class FormFactorCoherentSum> collectFormFactorList() const;
    FormFactorCoherentSum* createFormFactorCoherentSum(
        const IParticle* particle, const IMaterial* p_ambient_material) const;

    const Layer* mp_layer;                     //!< decorated layer
    const ILayout* mp_layout;                   //!< layout
    const ILayerSpecularInfo* mp_specular_info; //!< R and T coefficients for DWBA
    bool m_polarized;                           //!< polarized computation required?
    SimulationOptions m_sim_params;                            //!< simulation parameters
};

#endif // LAYERSTRATEGYBUILDER_H
