#include "actionmanager.h"
#include "hostosinfo.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include "stringutils.h"
#include <QMenuBar>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <iostream>

ActionManager::ActionManager(MainWindow *parent)
    : m_mainWindow(parent)
    , m_newAction(0)
    , m_openAction(0)
    , m_saveAction(0)
    , m_menuBar(0)
    , m_fileMenu(0)
    , m_helpMenu(0)

{
    setParent(parent);
    createActions();
    createMenus();
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
    m_saveAction->setShortcuts(QKeySequence::Open);
    m_saveAction->setStatusTip(tr("Save project"));
    connect(m_saveAction, SIGNAL(triggered()), projectManager, SLOT(saveProject()) );

    // exit application action
    icon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_exitAction = new QAction(icon, tr("E&xit Application"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), m_mainWindow, SLOT(close()));

}


void ActionManager::createMenus()
{
    m_menuBar = new QMenuBar; // No parent (System menu bar on Mac OS X)

    if (!Utils::HostOsInfo::isMacHost()) // System menu bar on Mac
        m_mainWindow->setMenuBar(m_menuBar);

    // File Menu
    m_fileMenu = m_menuBar->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    connect(m_fileMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowRecentProjects()));

    m_recentProjectsMenu = m_fileMenu->addMenu("&Recent Projects");

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_saveAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Help Menu
    m_helpMenu = m_menuBar->addMenu(tr("&Help"));
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



