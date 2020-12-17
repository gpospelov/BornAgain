//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/insertnewitemcommand.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"
#include "mvvm/model/function_types.h"

namespace ModelView {

class SessionItem;
class TagRow;

//! Command for unddo/redo to insert new item.

class MVVM_MODEL_EXPORT InsertNewItemCommand : public AbstractItemCommand {
public:
    InsertNewItemCommand(item_factory_func_t func, SessionItem* parent, const TagRow& tagrow);
    ~InsertNewItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandImpl;
    std::unique_ptr<InsertNewItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H
