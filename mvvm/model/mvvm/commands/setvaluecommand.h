//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/setvaluecommand.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_SETVALUECOMMAND_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_SETVALUECOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"
#include "mvvm/core/variant.h"

namespace ModelView {

class SessionItem;

//! Command for unddo/redo framework to set the data of SessionItem.

class MVVM_MODEL_EXPORT SetValueCommand : public AbstractItemCommand {
public:
    SetValueCommand(SessionItem* item, Variant value, int role);
    ~SetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    std::unique_ptr<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_SETVALUECOMMAND_H
