// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H

#include <variant>

namespace ModelView {

class SessionItem;

//! Results of command execution.
using CommandResult = std::variant<bool, ModelView::SessionItem*>;

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDRESULT_H
