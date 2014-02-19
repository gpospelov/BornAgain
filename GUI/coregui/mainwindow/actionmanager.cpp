#include "actionmanager.h"
#include "hostosinfo.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include <QMenuBar>
#include <iostream>

ActionManager::ActionManager(MainWindow *parent)
    : m_mainWindow(parent)
    , m_newAction(0)
    , m_openAction(0)
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

    QIcon icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(QLatin1String(Constants::ICON_NEWFILE)));
    m_newAction = new QAction(icon, tr("&New Project"), m_mainWindow);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new project"));
    connect(m_newAction, SIGNAL(triggered()), m_mainWindow, SLOT(newProject()) );

    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
    m_openAction = new QAction(icon, tr("&Open Project"), m_mainWindow);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing file"));
    connect(m_openAction, SIGNAL(triggered()), m_mainWindow, SLOT(openProject()) );

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

    m_fileMenu = m_menuBar->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_helpMenu = m_menuBar->addMenu(tr("&Help"));
}

