// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.h
//! @brief     Defines class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SSCAPPROXIMATIONSTRATEGY_H
#define SSCAPPROXIMATIONSTRATEGY_H

#include "Core/Multilayer/IInterferenceFunctionStrategy.h"
#include "Core/Multilayer/SSCAHelper.h"

class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the size-spacing correlation approximation.
//! @ingroup algorithms_internal

class SSCApproximationStrategy final : public IInterferenceFunctionStrategy
{
public:
    SSCApproximationStrategy(SimulationOptions sim_params, double kappa, bool polarized);

private:
    void strategy_specific_post_init() override;
    double scalarCalculation(const SimulationElement& sim_element) const override;
    double polarizedCalculation(const SimulationElement& sim_element) const override;
    SSCAHelper m_helper;
};

#endif // SSCAPPROXIMATIONSTRATEGY_H
