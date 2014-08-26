#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QList>

class QMenu;
class QAction;
class QMenuBar;
class MainWindow;


//! Class to handle MainWindow's menu and corresponding actions

class BA_CORE_API_ ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(MainWindow *parent);

public slots:
    void aboutToShowRecentProjects();

private:
    MainWindow *m_mainWindow;

    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_exitAction;
    QList<QAction *> m_recentProjectActions;

    QMenuBar *m_menuBar;
    QMenu *m_fileMenu;
    QMenu *m_recentProjectsMenu;
    QMenu *m_helpMenu;

    void createActions();
    void createMenus();

};


#endif // ACTIONMANAGER_H

