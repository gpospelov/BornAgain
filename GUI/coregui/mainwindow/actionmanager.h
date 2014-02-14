#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H


#include <QObject>


class QMenu;
class QAction;
class QMenuBar;
class MainWindow;


//! Class to handle MainWindow's menu and corresponding actions

class ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(MainWindow *parent);

private:
    MainWindow *m_mainWindow;

    QAction *m_newAction;
    QAction *m_openAction;

    QMenuBar *m_menuBar;
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;

    void createActions();
    void createMenus();

};


#endif // ACTIONMANAGER_H

