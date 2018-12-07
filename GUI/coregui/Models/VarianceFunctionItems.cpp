// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/VarianceFunctionItems.cpp
//! @brief     Implements classes VarianceFunctionItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "VarianceFunctionItems.h"
#include "item_constants.h"
#include "VarianceFunctions.h"

IVarianceFunctionItem::IVarianceFunctionItem(const QString& model_type)
    : SessionItem(model_type)
{

}

VarianceConstantFunctionItem::VarianceConstantFunctionItem()
    : IVarianceFunctionItem(Constants::VarianceConstantFunctionType)
{
    setToolTip("Leaves residual value unnormalized");

}

std::unique_ptr<IVarianceFunction> VarianceConstantFunctionItem::createVarianceFunction() const
{
    return std::make_unique<VarianceConstantFunction>();
}

const QString VarianceSimFunctionItem::P_EPSILON = "epsilon";

VarianceSimFunctionItem::VarianceSimFunctionItem()
    : IVarianceFunctionItem(Constants::VarianceSimFunctionType)
{
    setToolTip("Normalizes residual on max(sim, epsilon)");
    addProperty(P_EPSILON, 1.0)->setToolTip(QStringLiteral(
            "Defines threshold on simulated amplitude in max(sim, epsilon)"));
}

std::unique_ptr<IVarianceFunction> VarianceSimFunctionItem::createVarianceFunction() const
{
    return std::make_unique<VarianceSimFunction>(getItemValue(P_EPSILON).toDouble());
}
