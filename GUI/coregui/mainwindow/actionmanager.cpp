// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/actionmanager.cpp
//! @brief     Implements class ActionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "actionmanager.h"
#include "hostosinfo.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include "stringutils.h"
#include <QMenuBar>
#include <QShortcut>
#include <QSettings>
#include <QFileInfo>
#include <QKeySequence>
#include <QDebug>
#include <QDir>
#include <iostream>

ActionManager::ActionManager(MainWindow *parent)
    : QObject(parent)
    , m_mainWindow(parent)
    , m_newAction(0)
    , m_openAction(0)
    , m_saveAction(0)
    , m_saveAsAction(0)
    , m_menuBar(0)
    , m_fileMenu(0)
    , m_settingsMenu(0)
    , m_helpMenu(0)
    , m_runSimulationShortcut(0)
{
    setParent(parent);
    createActions();
    createMenus();
    createGlobalShortcuts();
}



void ActionManager::createActions()
{
    ProjectManager *projectManager = m_mainWindow->getProjectManager();
    Q_ASSERT(projectManager);

    // new project action
    QIcon icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(QLatin1String(Constants::ICON_NEWFILE)));
    m_newAction = new QAction(icon, tr("&New Project"), m_mainWindow);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new project"));
    connect(m_newAction, SIGNAL(triggered()), projectManager, SLOT(newProject()) );

    // open project action
    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
    m_openAction = new QAction(icon, tr("&Open Project"), m_mainWindow);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing project"));
    connect(m_openAction, SIGNAL(triggered()), projectManager, SLOT(openProject()) );

    // save project action
    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(QLatin1String(Constants::ICON_SAVEFILE)));
    m_saveAction = new QAction(icon, tr("&Save Project"), m_mainWindow);
    m_saveAction->setShortcuts(QKeySequence::Save);
    m_saveAction->setStatusTip(tr("Save project"));
    m_saveAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveAction, SIGNAL(triggered()), projectManager, SLOT(saveProject()) );

    // save-as project action
    icon = QIcon::fromTheme(QLatin1String("document-save-as"));
    m_saveAsAction = new QAction(icon, tr("Save &As..."), m_mainWindow);
    m_saveAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip(tr("Save project under different name"));
    connect(m_saveAsAction, SIGNAL(triggered()), projectManager, SLOT(saveProjectAs()) );

    // exit application action
    icon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_exitAction = new QAction(icon, tr("E&xit Application"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), m_mainWindow, SLOT(close()));

    // about application action
    icon = QIcon::fromTheme(QLatin1String("help-about"));
    m_aboutAction = new QAction(icon, tr("About &BornAgain"), this);
    //m_aboutAction->setShortcuts(QKeySequence::HelpContents);
    m_aboutAction->setStatusTip(tr("About the application"));
    connect(m_aboutAction, SIGNAL(triggered()), m_mainWindow, SLOT(onAboutApplication()));

}


void ActionManager::createMenus()
{
    m_menuBar = new QMenuBar; // No parent (System menu bar on Mac OS X)

    if (!Utils::HostOsInfo::isMacHost())
        m_mainWindow->setMenuBar(m_menuBar);

    // File Menu
    m_fileMenu = m_menuBar->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    connect(m_fileMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowRecentProjects()));

    m_recentProjectsMenu = m_fileMenu->addMenu("Recent Projects");

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Settings Menu
    m_settingsMenu = m_menuBar->addMenu(tr("&Settings"));
    connect(m_settingsMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowSettings()));


    // Help Menu
    m_helpMenu = m_menuBar->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAction);
}


void ActionManager::createGlobalShortcuts()
{
    m_runSimulationShortcut =  new QShortcut(QKeySequence(tr("Ctrl+r")), m_mainWindow);
    m_runSimulationShortcut->setContext((Qt::ApplicationShortcut));
    connect(m_runSimulationShortcut, SIGNAL(activated()), m_mainWindow, SLOT(onRunSimulationShortcut()));
}


void ActionManager::aboutToShowRecentProjects()
{
    qDebug() << "ActionManager::aboutToShowRecentProjects() ->" << m_mainWindow->getProjectManager()->getRecentProjects();
    m_recentProjectsMenu->clear();

    bool hasRecentProjects = false;
    foreach(QString file, m_mainWindow->getProjectManager()->getRecentProjects() ) {
        hasRecentProjects = true;
        qDebug() << file << QDir::toNativeSeparators(Utils::withTildeHomePath(file));
        QAction *action = m_recentProjectsMenu->addAction(QDir::toNativeSeparators(Utils::withTildeHomePath(file)));
        action->setData(qVariantFromValue(file));
        connect(action, SIGNAL(triggered()), m_mainWindow, SLOT(openRecentProject()));

    }

    m_recentProjectsMenu->setEnabled(hasRecentProjects);

    if (hasRecentProjects) {
        m_recentProjectsMenu->addSeparator();
        QAction *action = m_recentProjectsMenu->addAction("Clear Menu");
        connect(action, SIGNAL(triggered()), m_mainWindow->getProjectManager(), SLOT(clearRecentProjects()));
    }

}

void ActionManager::aboutToShowSettings()
{
    m_settingsMenu->clear();
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_UPDATES)) {
        settings.beginGroup(Constants::S_UPDATES);
        QAction *action = m_settingsMenu->addAction(tr("Check for Updates"));
        action->setCheckable(true);
        action->setChecked(settings.value(Constants::S_CHECKFORUPDATES, false).toBool());
        connect(action, SIGNAL(toggled(bool)), this, SLOT(toggleCheckForUpdates(bool)));
        settings.endGroup();
    }

}

void ActionManager::toggleCheckForUpdates(bool status)
{
    QSettings settings;
    settings.beginGroup(Constants::S_UPDATES);
    settings.setValue(Constants::S_CHECKFORUPDATES, status);
    settings.endGroup();
}


