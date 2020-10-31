// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/LayoutStrategyBuilder.cpp
//! @brief     Implements class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/LayoutStrategyBuilder.h"
#include "Base/Types/Exceptions.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Interference/DecouplingApproximationStrategy.h"
#include "Sample/Interference/SSCApproximationStrategy.h"

LayoutStrategyBuilder::LayoutStrategyBuilder(const ProcessedLayout* p_layout,
                                             const SimulationOptions& sim_params, bool polarized)
    : m_layout(p_layout), m_sim_params(sim_params), m_polarized(polarized)
{
    createStrategy();
}

// needs class definitions => don't move to .h
LayoutStrategyBuilder::~LayoutStrategyBuilder() = default;

IInterferenceFunctionStrategy* LayoutStrategyBuilder::releaseStrategy()
{
    return m_strategy.release();
}

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
void LayoutStrategyBuilder::createStrategy()
{
    const IInterferenceFunction* p_iff = m_layout->interferenceFunction();
    if (p_iff && m_layout->numberOfSlices() > 1 && !p_iff->supportsMultilayer())
        throw std::runtime_error("LayoutStrategyBuilder::checkInterferenceFunction: "
                                 "interference function does not support multiple layers");

    auto p_radial_para = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(p_iff);
    if (p_radial_para && p_radial_para->kappa() > 0.0) {
        double kappa = p_radial_para->kappa();
        m_strategy = std::make_unique<SSCApproximationStrategy>(m_sim_params, kappa, m_polarized);
    } else {
        m_strategy = std::make_unique<DecouplingApproximationStrategy>(m_sim_params, m_polarized);
    }
    if (!m_strategy)
        throw Exceptions::ClassInitializationException("Could not create appropriate strategy");
    m_strategy->init(m_layout->formFactorList(), p_iff);
}
