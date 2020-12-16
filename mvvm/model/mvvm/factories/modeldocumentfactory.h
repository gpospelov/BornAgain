// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELDOCUMENTFACTORY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELDOCUMENTFACTORY_H

#include "mvvm/interfaces/modeldocumentinterface.h"
#include <memory>
#include <vector>

namespace ModelView {

class SessionModel;

//! Creates JsonDocument to save and load models.
MVVM_MODEL_EXPORT std::unique_ptr<ModelDocumentInterface>
CreateJsonDocument(const std::vector<SessionModel*>& models);

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_MODELDOCUMENTFACTORY_H
