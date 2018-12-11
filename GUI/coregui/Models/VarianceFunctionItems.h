// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/VarianceFunctionItems.h
//! @brief     Defines classes VarianceFunctionItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef VARIANTFUNCTIONITEMS_H
#define VARIANTFUNCTIONITEMS_H

#include "SessionItem.h"
#include <QString>
#include <memory>

class IVarianceFunction;

//! Base class for variance in Minimizer's residual settings.

class BA_CORE_API_ IVarianceFunctionItem : public SessionItem
{
public:
    virtual std::unique_ptr<IVarianceFunction> createVarianceFunction() const = 0;
protected:
    IVarianceFunctionItem(const QString& model_type);
};

class BA_CORE_API_ VarianceConstantFunctionItem : public IVarianceFunctionItem
{
public:
    VarianceConstantFunctionItem();

    std::unique_ptr<IVarianceFunction> createVarianceFunction() const;
};

class BA_CORE_API_ VarianceSimFunctionItem : public IVarianceFunctionItem
{
public:
    static const QString P_EPSILON;
    VarianceSimFunctionItem();

    std::unique_ptr<IVarianceFunction> createVarianceFunction() const;
};

#endif // VARIANTFUNCTIONITEMS_H
