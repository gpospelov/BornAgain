// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/actionmanager.cpp
//! @brief     Implements class ActionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "actionmanager.h"
#include "UpdateNotifier.h"
#include "hostosinfo.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include "qstringutils.h"
#include <QDir>
#include <QMenuBar>
#include <QSettings>
#include <QShortcut>

ActionManager::ActionManager(MainWindow* parent)
    : QObject(parent)
    , m_mainWindow(parent)
    , m_newAction(nullptr)
    , m_openAction(nullptr)
    , m_saveAction(nullptr)
    , m_saveAsAction(nullptr)
    , m_exitAction(nullptr)
    , m_aboutAction(nullptr)
    , m_menuBar(nullptr)
    , m_fileMenu(nullptr)
    , m_settingsMenu(nullptr)
    , m_recentProjectsMenu(nullptr)
    , m_helpMenu(nullptr)
    , m_importMenu(nullptr)
    , m_runSimulationShortcut(nullptr)
{
    createActions();
    createMenus();
    createGlobalShortcuts();
}

void ActionManager::createActions()
{
    ProjectManager* projectManager = m_mainWindow->projectManager();
    Q_ASSERT(projectManager);

    // new project action
    m_newAction = new QAction("&New Project", m_mainWindow);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip("Create a new project");
    connect(m_newAction, &QAction::triggered, projectManager, &ProjectManager::newProject);

    // open project action
    m_openAction = new QAction("&Open Project", m_mainWindow);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip("Open an existing project");
    connect(m_openAction, &QAction::triggered,
            projectManager, [projectManager]() { projectManager->openProject(); });

    // save project action
    m_saveAction = new QAction("&Save Project", m_mainWindow);
    m_saveAction->setShortcuts(QKeySequence::Save);
    m_saveAction->setStatusTip("Save project");
    m_saveAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveAction, &QAction::triggered,
            projectManager, [projectManager]() { projectManager->saveProject(); });

    // save-as project action
    m_saveAsAction = new QAction("Save &As...", m_mainWindow);
    m_saveAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip("Save project under different name");
    connect(m_saveAsAction, &QAction::triggered, projectManager, &ProjectManager::saveProjectAs);

    // exit application action
    m_exitAction = new QAction("E&xit Application", this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    connect(m_exitAction, &QAction::triggered, m_mainWindow, &MainWindow::close);

    // about application action
    m_aboutAction = new QAction("About &BornAgain", this);
    m_aboutAction->setStatusTip("About the application");
    connect(m_aboutAction, &QAction::triggered, m_mainWindow, &MainWindow::onAboutApplication);
}

void ActionManager::createMenus()
{
    m_menuBar = new QMenuBar(0); // No parent (System menu bar on Mac OS X)

    if (!GUI_OS_Utils::HostOsInfo::isMacHost())
        m_mainWindow->setMenuBar(m_menuBar);

    // File Menu
    m_fileMenu = m_menuBar->addMenu("&File");
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    connect(m_fileMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowFileMenu()));

    m_recentProjectsMenu = m_fileMenu->addMenu("Recent Projects");

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);

    // Import submenu
    m_fileMenu->addSeparator();
    m_importMenu = m_fileMenu->addMenu("Import");
    m_importMenu->setToolTipsVisible(true);
    QAction* action = m_importMenu->addAction("Import from Python script");
    action->setToolTip("Import sample from Python script");
    connect(action, &QAction::triggered, this, &ActionManager::onImportFromPythonScript);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Settings Menu
    m_settingsMenu = new QMenu("Settings", m_mainWindow);
    aboutToShowSettings(); // MacOS feature: action should exist already, otherwise menuBar will not
                           // add menu
    connect(m_settingsMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowSettings()));
    m_menuBar->addMenu(m_settingsMenu);

    // Help Menu
    m_helpMenu = m_menuBar->addMenu("&Help");
    m_helpMenu->addAction(m_aboutAction);
}

void ActionManager::createGlobalShortcuts()
{
    m_runSimulationShortcut = new QShortcut(QKeySequence("Ctrl+r"), m_mainWindow);
    m_runSimulationShortcut->setContext((Qt::ApplicationShortcut));
    connect(m_runSimulationShortcut, SIGNAL(activated()), m_mainWindow,
            SLOT(onRunSimulationShortcut()));
}

void ActionManager::aboutToShowFileMenu()
{
    m_recentProjectsMenu->clear();

    bool hasRecentProjects = false;
    foreach (QString file, m_mainWindow->projectManager()->recentProjects()) {
        hasRecentProjects = true;
        QAction* action = m_recentProjectsMenu->addAction(
            QDir::toNativeSeparators(GUI_StringUtils::withTildeHomePath(file)));
        action->setData(qVariantFromValue(file));
        connect(action, SIGNAL(triggered()), m_mainWindow, SLOT(openRecentProject()));
    }

    m_recentProjectsMenu->setEnabled(hasRecentProjects);

    if (hasRecentProjects) {
        m_recentProjectsMenu->addSeparator();
        QAction* action = m_recentProjectsMenu->addAction("Clear Menu");
        connect(action, SIGNAL(triggered()), m_mainWindow->projectManager(),
                SLOT(clearRecentProjects()));
    }
}

void ActionManager::aboutToShowSettings()
{
    m_settingsMenu->clear();
    QSettings settings;

    settings.beginGroup(Constants::S_UPDATES);
    QAction* action = m_settingsMenu->addAction("Check for Updates");
    action->setToolTip("Checks for updates available on GUI startup.");
    action->setCheckable(true);
    action->setChecked(settings.value(Constants::S_CHECKFORUPDATES, false).toBool());
    connect(action, SIGNAL(toggled(bool)), this, SLOT(toggleCheckForUpdates(bool)));
    settings.endGroup();

    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    action = m_settingsMenu->addAction("Model tech view");
    action->setToolTip("Additional developer's view will appear in left control tab bar");
    action->setCheckable(true);
    action->setChecked(settings.value(Constants::S_VIEWISACTIVE, false).toBool());
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setSessionModelViewActive(bool)));
    settings.endGroup();

    action = m_settingsMenu->addAction("Enable autosave");
    action->setToolTip("Project will be saved periodically in project's autosave directory.\n"
                       "When opening project, recover option will be suggested, if possible.");
    action->setCheckable(true);
    action->setChecked(m_mainWindow->projectManager()->isAutosaveEnabled());
    connect(action, SIGNAL(toggled(bool)), m_mainWindow->projectManager(),
            SLOT(setAutosaveEnabled(bool)));

    m_settingsMenu->setToolTipsVisible(true);
}

void ActionManager::toggleCheckForUpdates(bool status)
{
    QSettings settings;
    settings.beginGroup(Constants::S_UPDATES);
    settings.setValue(Constants::S_CHECKFORUPDATES, status);
    settings.endGroup();
    m_mainWindow->getUpdateNotifier()->checkForUpdates();
}

void ActionManager::setSessionModelViewActive(bool status)
{
    QSettings settings;
    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    settings.setValue(Constants::S_VIEWISACTIVE, status);
    settings.endGroup();
    m_mainWindow->onSessionModelViewActive(status);
}

void ActionManager::onImportFromPythonScript()
{

}
