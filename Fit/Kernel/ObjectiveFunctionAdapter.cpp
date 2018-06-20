// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootObjectiveFuncAdapter.cpp
//! @brief     Implements class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ObjectiveFunctionAdapter.h"
#include "ResidualFunctionAdapter.h"
#include "RootObjectiveFunction.h"
#include "RootResidualFunction.h"
#include "ScalarFunctionAdapter.h"

using namespace Fit;

ObjectiveFunctionAdapter::ObjectiveFunctionAdapter() = default;

ObjectiveFunctionAdapter::~ObjectiveFunctionAdapter() = default;

const RootObjectiveFunction*
ObjectiveFunctionAdapter::rootObjectiveFunction(fcn_scalar_t fcn, const Parameters& parameters)
{
    std::unique_ptr<ScalarFunctionAdapter> temp_adapter(new ScalarFunctionAdapter(fcn, parameters));
    auto result = temp_adapter->rootObjectiveFunction();
    m_adapter.reset(temp_adapter.release());
    return result;
}

const RootResidualFunction*
ObjectiveFunctionAdapter::rootResidualFunction(fcn_residual_t fcn, const Parameters& parameters)
{
    std::unique_ptr<ResidualFunctionAdapter> temp_adapter(
        new ResidualFunctionAdapter(fcn, parameters));
    auto result = temp_adapter->rootResidualFunction();
    m_adapter.reset(temp_adapter.release());
    return result;
}

int ObjectiveFunctionAdapter::numberOfCalls() const
{
    return m_adapter ? m_adapter->numberOfCalls() : 0;
}

int ObjectiveFunctionAdapter::numberOfGradientCalls() const
{
    return m_adapter ? m_adapter->numberOfGradientCalls() : 0;
}
