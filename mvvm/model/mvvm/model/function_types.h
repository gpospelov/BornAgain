//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/function_types.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_FUNCTION_TYPES_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_FUNCTION_TYPES_H

#include <functional>
#include <memory>

namespace ModelView {

class SessionItem;

//! Definition for item factory funciton.
using item_factory_func_t = std::function<std::unique_ptr<SessionItem>()>;

//! Creates factory function for item of specific type.
template <typename T> item_factory_func_t ItemFactoryFunction() {
    return []() { return std::make_unique<T>(); };
}

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_FUNCTION_TYPES_H
