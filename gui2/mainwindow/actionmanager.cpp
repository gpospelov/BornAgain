// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/mainwindow/actionmanager.h"
#include "mvvm/widgets/widgetutils.h"
#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>

namespace DaRefl {

ActionManager::ActionManager(QMainWindow* mainwindow)
    : QObject(mainwindow), m_mainWindow(mainwindow) {
    createActions();
    setupMenus(m_mainWindow->menuBar());
}

void ActionManager::aboutToShowFileMenu() {
    m_recentProjectMenu->clear();
    m_recentProjectMenu->setEnabled(!m_recentProjects.isEmpty());

    for (auto project_dir : m_recentProjects) {
        auto trimmed_project_dir = ModelView::Utils::WithTildeHomePath(project_dir);
        auto action = m_recentProjectMenu->addAction(trimmed_project_dir);
        action->setData(QVariant::fromValue(project_dir));
        auto on_project_selected = [this, project_dir]() {
            openExistingProjectRequest(project_dir);
        };
        connect(action, &QAction::triggered, on_project_selected);
    }

    if (!m_recentProjects.empty()) {
        m_recentProjectMenu->addSeparator();
        auto action = m_recentProjectMenu->addAction("Clear Menu");
        connect(action, &QAction::triggered, [this]() { clearResentProjectListRequest(); });
    }
}

void ActionManager::setRecentProjectsList(const QStringList& projects) {
    m_recentProjects = projects;
}

//! Creates application-wise actions to create, open, save, and save-as projects.

void ActionManager::createActions() {
    m_createNewProjectAction = new QAction("&New Project", this);
    m_createNewProjectAction->setShortcuts(QKeySequence::New);
    m_createNewProjectAction->setStatusTip("Create a new project");
    connect(m_createNewProjectAction, &QAction::triggered, this,
            &ActionManager::createNewProjectRequest);

    m_openExistingProjectAction = new QAction("&Open Project", this);
    m_openExistingProjectAction->setShortcuts(QKeySequence::Open);
    m_openExistingProjectAction->setStatusTip("Open an existing project");
    connect(m_openExistingProjectAction, &QAction::triggered,
            [this]() { openExistingProjectRequest({}); });

    m_saveCurrentProjectAction = new QAction("&Save Project", this);
    m_saveCurrentProjectAction->setShortcuts(QKeySequence::Save);
    m_saveCurrentProjectAction->setStatusTip("Save project");
    m_saveCurrentProjectAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveCurrentProjectAction, &QAction::triggered, this,
            &ActionManager::saveCurrentProjectRequest);

    m_saveProjectAsAction = new QAction("Save &As...", this);
    m_saveProjectAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveProjectAsAction->setStatusTip("Save project under different name");
    connect(m_saveProjectAsAction, &QAction::triggered, this, &ActionManager::saveProjectAsRequest);

    m_exitAction = new QAction("E&xit Application", this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    connect(m_exitAction, &QAction::triggered, m_mainWindow, &QMainWindow::close);
}

//! Equips menu with actions.

void ActionManager::setupMenus(QMenuBar* menubar) {
    auto fileMenu = menubar->addMenu("&File");
    connect(fileMenu, &QMenu::aboutToShow, this, &ActionManager::aboutToShowFileMenu);
    fileMenu->addAction(m_createNewProjectAction);
    fileMenu->addAction(m_openExistingProjectAction);
    m_recentProjectMenu = fileMenu->addMenu("Recent Projects");

    fileMenu->addSeparator();
    fileMenu->addAction(m_saveCurrentProjectAction);
    fileMenu->addAction(m_saveProjectAsAction);

    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);
}

} // namespace DaRefl
