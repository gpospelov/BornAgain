// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayoutStrategyBuilder.h
//! @brief     Defines class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYOUTSTRATEGYBUILDER_H
#define LAYOUTSTRATEGYBUILDER_H

#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include <memory>

class FormFactorCoherentSum;
class IInterferenceFunctionStrategy;
class ILayout;
class IMaterial;
class IParticle;
class IFresnelMap;
class MultiLayer;

//! Methods to generate a simulation strategy for a ParticleLayoutComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayoutStrategyBuilder
{
public:
    LayoutStrategyBuilder(
        const MultiLayer* p_multilayer, const ILayout* p_layout,
        const IFresnelMap* p_fresnel_map, bool polarized,
        const SimulationOptions& sim_params, size_t layer_index);

    ~LayoutStrategyBuilder();

    IInterferenceFunctionStrategy* createStrategy() const;

private:
    SafePointerVector<class FormFactorCoherentSum> collectFormFactorList() const;
    FormFactorCoherentSum* createFormFactorCoherentSum(const IParticle* particle) const;

    const MultiLayer* mp_multilayer;
    const ILayout* mp_layout;
    //! R and T coefficients for DWBA
    const IFresnelMap* mp_fresnel_map;
    bool m_polarized;  //!< polarized computation required?
    SimulationOptions m_sim_params;
    size_t m_layer_index;
};

#endif // LAYOUTSTRATEGYBUILDER_H
