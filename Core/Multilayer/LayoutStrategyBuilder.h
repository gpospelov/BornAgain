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

#include "Core/Parametrization/SimulationOptions.h"
#include <memory>

class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class ProcessedLayout;

//! Methods to generate a simulation strategy for a ParticleLayoutComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayoutStrategyBuilder
{
public:
    LayoutStrategyBuilder(const ProcessedLayout* p_layout, const SimulationOptions& sim_params,
                          bool polarized);

    ~LayoutStrategyBuilder();

    IInterferenceFunctionStrategy* releaseStrategy();

private:
    void createStrategy();
    void checkInterferenceFunction(const IInterferenceFunction* p_iff);

    const ProcessedLayout* mp_layout;
    SimulationOptions m_sim_params;
    bool m_polarized; //!< polarized computation required?
    std::unique_ptr<IInterferenceFunctionStrategy> mP_strategy;
};

#endif // LAYOUTSTRATEGYBUILDER_H
