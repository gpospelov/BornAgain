//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/commandresult.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H

#include <variant>

namespace ModelView {

class SessionItem;

//! Results of command execution.
using CommandResult = std::variant<bool, ModelView::SessionItem*>;

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H
