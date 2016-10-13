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

class BA_CORE_API_ DecouplingApproximationStrategy : public virtual IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy() {}
    virtual ~DecouplingApproximationStrategy() {}
};

//!

class BA_CORE_API_ DecouplingApproximationStrategy1
    : public DecouplingApproximationStrategy
    , public IInterferenceFunctionStrategy1
{
public:
    DecouplingApproximationStrategy1(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy1(sim_params) {}
    ~DecouplingApproximationStrategy1() final {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;
};

//!

class BA_CORE_API_ DecouplingApproximationStrategy2
    : public DecouplingApproximationStrategy
    , public IInterferenceFunctionStrategy2
{
public:
    DecouplingApproximationStrategy2(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy2(sim_params) {}
    ~DecouplingApproximationStrategy2() final {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;
};

#endif // DECOUPLINGAPPROXIMATIONSTRATEGY_H
