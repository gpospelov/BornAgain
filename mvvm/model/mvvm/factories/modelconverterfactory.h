//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/factories/modelconverterfactory.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELCONVERTERFACTORY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELCONVERTERFACTORY_H

//! @file mvvm/model/mvvm/factories/modelconverterfactory.h
//! Collection of factory functions to create SessionModel converters to/from serialized content.

#include "mvvm/serialization/jsonmodelconverterinterface.h"
#include <memory>

namespace ModelView {

//! Creates a JSON model converter intended for model cloning.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelCloneConverter();

//! Creates a JSON model converter intended for model copying.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
MVVM_MODEL_EXPORT std::unique_ptr<JsonModelConverterInterface> CreateModelProjectConverter();

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELCONVERTERFACTORY_H
