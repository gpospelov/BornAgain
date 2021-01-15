//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/commandutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDUTILS_H

//! @file mvvm/model/mvvm/commands/commandutils.h
//! Collection of various utility functions for command service.

#include "mvvm/interfaces/itembackupstrategy.h"
#include "mvvm/interfaces/itemcopystrategy.h"
#include <memory>

namespace ModelView {

class SessionModel;

//! Creates strategy suitable for item saving/restoring. Restored item will have same identifiers
//! as original.

MVVM_MODEL_EXPORT std::unique_ptr<ItemBackupStrategy>
CreateItemBackupStrategy(const SessionModel* model);

//! Returns strategy for item copying. Identifiers of the copy will be different from identifiers
//! of the original.

MVVM_MODEL_EXPORT std::unique_ptr<ItemCopyStrategy>
CreateItemCopyStrategy(const SessionModel* model);

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDUTILS_H
