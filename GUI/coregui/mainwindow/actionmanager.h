// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/actionmanager.h
//! @brief     Defines class ActionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "WinDllMacros.h"
#include <QObject>

class QMenu;
class QAction;
class QMenuBar;
class MainWindow;
class QShortcut;

//! Class to handle MainWindow's menu and corresponding actions

class BA_CORE_API_ ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(MainWindow* parent);

private slots:
    void aboutToShowFileMenu();
    void aboutToShowSettings();
    void toggleCheckForUpdates(bool status);
    void setSessionModelViewActive(bool status);
    void onImportFromPythonScript();

private:
    MainWindow* m_mainWindow;

    QAction* m_newAction;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_exitAction;
    QAction* m_aboutAction;

    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QMenu* m_settingsMenu;
    QMenu* m_recentProjectsMenu;
    QMenu* m_helpMenu;
    QMenu* m_importMenu;

    QShortcut* m_runSimulationShortcut;

    void createActions();
    void createMenus();
    void createGlobalShortcuts();
};

#endif // ACTIONMANAGER_H

