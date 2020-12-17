//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/commandadapter.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/commands/commandadapter.h"
#include "mvvm/commands/abstractitemcommand.h"

using namespace ModelView;

CommandAdapter::CommandAdapter(std::shared_ptr<AbstractItemCommand> command)
    : m_command(std::move(command)) {}

CommandAdapter::~CommandAdapter() = default;

void CommandAdapter::undo() {
    m_command->undo();
}

void CommandAdapter::redo() {
    m_command->execute();
    setObsolete(m_command->isObsolete());
    setText(QString::fromStdString(m_command->description()));
}
