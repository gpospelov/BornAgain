// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.h
//! @brief     Defines class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECOUPLINGAPPROXIMATIONSTRATEGY_H
#define DECOUPLINGAPPROXIMATIONSTRATEGY_H

#include "IInterferenceFunctionStrategy.h"

class SimulationElement;

//! Strategy for implementing decoupling approximation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecouplingApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy(sim_params) {}
    ~DecouplingApproximationStrategy() final {}

    void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
              const IInterferenceFunction& iff) final;

private:
    double evaluateForList(const SimulationElement& sim_element,
                           const std::vector<complex_t>& ff_list) const final;

    double evaluateForMatrixList(const SimulationElement& sim_element,
                                 const matrixFFVector_t& ff_list) const final;
};

#endif // DECOUPLINGAPPROXIMATIONSTRATEGY_H
