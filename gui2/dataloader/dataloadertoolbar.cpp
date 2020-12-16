// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/dataloader/dataloadertoolbar.h"
#include "gui2/mainwindow/styleutils.h"
#include <QAction>

namespace DaRefl {

DataLoaderToolBar::DataLoaderToolBar(QWidget* parent) : QToolBar(parent) {
    StyleUtils::SetToolBarStyleTextBesides(this);

    // add files
    auto action = new QAction("Add files", this);
    action->setIcon(QIcon(":/icons/import.svg"));
    action->setToolTip("Adds more files to the list.\n "
                       "All of them will be parsed in the same way.");
    connect(action, &QAction::triggered, [this]() { this->addFilesRequest(); });
    addAction(action);

    // remove files
    action = new QAction("Remove files", this);
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Remove selected files from the list.");
    connect(action, &QAction::triggered, [this]() { this->removeFilesRequest(); });
    addAction(action);
}

} // namespace DaRefl
