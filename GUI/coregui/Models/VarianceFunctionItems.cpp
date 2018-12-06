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

VarianceDefaultFunctionItem::VarianceDefaultFunctionItem()
    : IVarianceFunctionItem(Constants::VarianceDefaultFunctionType)
{
    setToolTip("Provides default residual normalization (i.e. leaves unnormalized)");

}

std::unique_ptr<IVarianceFunction> VarianceDefaultFunctionItem::createVarianceFunction() const
{
    return std::make_unique<VarianceDefaultFunction>();
}

const QString VarianceSimFunctionItem::P_EPSILON = "epsilon";

VarianceSimFunctionItem::VarianceSimFunctionItem()
    : IVarianceFunctionItem(Constants::VarianceSimFunctionType)
{
    setToolTip("Normalizes residual on max(sim, epsilon)");
    addProperty(P_EPSILON, 1.0)
        ->setToolTip(QStringLiteral("Defines threshold on simulated amplitude max(sim, epsilon)"));

}

std::unique_ptr<IVarianceFunction> VarianceSimFunctionItem::createVarianceFunction() const
{
    return std::make_unique<VarianceSimFunction>(getItemValue(P_EPSILON).toDouble());
}
