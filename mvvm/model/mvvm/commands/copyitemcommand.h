//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/copyitemcommand.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COPYITEMCOMMAND_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COPYITEMCOMMAND_H

#include "mvvm/commands/abstractitemcommand.h"

namespace ModelView {

class SessionItem;
class TagRow;

//! Command to copy an item.

class MVVM_MODEL_EXPORT CopyItemCommand : public AbstractItemCommand {
public:
    CopyItemCommand(const SessionItem* item, SessionItem* parent, TagRow tagrow);
    ~CopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    std::unique_ptr<CopyItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COPYITEMCOMMAND_H
