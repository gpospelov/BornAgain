//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/factories/modeldocumentfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/factories/modeldocumentfactory.h"
#include "mvvm/serialization/jsondocument.h"

namespace ModelView {

std::unique_ptr<ModelDocumentInterface>
CreateJsonDocument(const std::vector<SessionModel*>& models) {
    return std::make_unique<JsonDocument>(models);
}

} // namespace ModelView
