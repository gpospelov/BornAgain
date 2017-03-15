// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.h
//! @brief     Defines classes DecouplingApproximationStrategy1 and
//!              DecouplingApproximationStrategy2
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

//! Strategy class to compute the total scalar scattering from a decorated layer
//! in decoupling approximation.
//! @ingroup algorithms_internal

class DecouplingApproximationStrategy1 final : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy1(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy(sim_params) {}

protected:
    double evaluateForList(const SimulationElement& sim_element) const override;
};

//! Strategy class to compute the total polarized scattering from a decorated layer
//! in decoupling approximation.
//! @ingroup algorithms_internal

class DecouplingApproximationStrategy2 final : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy2(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy(sim_params) {}

protected:
    double evaluateForList(const SimulationElement& sim_element) const override;
};

#endif // DECOUPLINGAPPROXIMATIONSTRATEGY_H
