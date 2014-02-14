#include "actionmanager.h"
#include "hostosinfo.h"
#include "mainwindow.h"
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

    //QIcon icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
    m_newAction = new QAction(tr("&New"), m_mainWindow);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new project"));
    connect(m_newAction, SIGNAL(triggered()), m_mainWindow, SLOT(newProject()) );

    m_openAction = new QAction(tr("&Open..."), m_mainWindow);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing file"));
    connect(m_openAction, SIGNAL(triggered()), m_mainWindow, SLOT(openProject()) );


}


void ActionManager::createMenus()
{
    //m_menuBar = new QMenuBar; // No parent (System menu bar on Mac OS X)


    m_menuBar = m_mainWindow->menuBar();
    m_fileMenu = m_menuBar->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);

    m_helpMenu = m_menuBar->addMenu(tr("&Help"));


//    if (!Utils::HostOsInfo::isMacHost()) // System menu bar on Mac
//    {
//        std::cout << "XXXXX " << std::endl;
//        m_mainWindow->setMenuBar(m_menuBar);
//    }

}
