//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/commandadapter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDADAPTER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDADAPTER_H

#include "mvvm/model_export.h"
#include <QUndoCommand>
#include <memory>

namespace ModelView {

class AbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class MVVM_MODEL_EXPORT CommandAdapter : public QUndoCommand {
public:
    CommandAdapter(std::shared_ptr<AbstractItemCommand> command);
    ~CommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<AbstractItemCommand> m_command;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_COMMANDADAPTER_H
