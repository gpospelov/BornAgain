//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/undostack.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_UNDOSTACK_H
#define BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_UNDOSTACK_H

#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/model_export.h"
#include <memory>

class QUndoStack;

namespace ModelView {

//! Default undo stack implementation. Internally relies on QUndoStack.
//! It serves two goals: a) hides Qt usage b) simplifies future refactoring toward Qt-independent
//! libmvvm_model library.

class MVVM_MODEL_EXPORT UndoStack : public UndoStackInterface {
public:
    UndoStack();
    ~UndoStack() override;

    //! Executes the command, then pushes it in the stack for possible undo.
    void execute(std::shared_ptr<AbstractItemCommand> command) override;

    bool isActive() const override;
    bool canUndo() const override;
    bool canRedo() const override;
    int index() const override;
    int count() const override;
    void undo() override;
    void redo() override;
    void clear() override;
    void setUndoLimit(int limit) override;

    static QUndoStack* qtUndoStack(UndoStackInterface* stack_interface);

    void beginMacro(const std::string& name) override;
    void endMacro() override;

private:
    struct UndoStackImpl;
    std::unique_ptr<UndoStackImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_COMMANDS_UNDOSTACK_H
