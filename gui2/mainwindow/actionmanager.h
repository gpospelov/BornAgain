//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/mainwindow/actionmanager.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MAINWINDOW_ACTIONMANAGER_H
#define BORNAGAIN_GUI2_MAINWINDOW_ACTIONMANAGER_H

#include "darefl_export.h"
#include <QObject>

class QMainWindow;
class QAction;
class QMenuBar;
class QMenu;

namespace gui2 {

//! Actions for MainWindow. Equips toolbar and menubar with actions to create, open, save,
//! and save-as projects. It doesn't have logic and simply forwards requests further.

class DAREFLCORE_EXPORT ActionManager : public QObject {
    Q_OBJECT

public:
    ActionManager(QMainWindow* mainwindow = nullptr);

signals:
    void createNewProjectRequest();
    void openExistingProjectRequest(const QString& dirname);
    void saveCurrentProjectRequest();
    void saveProjectAsRequest();
    void clearResentProjectListRequest();

public slots:
    void setRecentProjectsList(const QStringList& projects);

private slots:
    void aboutToShowFileMenu();

private:
    void createActions();
    void setupMenus(QMenuBar* menubar);

    QMainWindow* m_mainWindow{nullptr};

    QAction* m_createNewProjectAction{nullptr};
    QAction* m_openExistingProjectAction{nullptr};
    QAction* m_saveCurrentProjectAction{nullptr};
    QAction* m_saveProjectAsAction{nullptr};
    QAction* m_exitAction{nullptr};

    QMenu* m_recentProjectMenu{nullptr};

    QStringList m_recentProjects;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MAINWINDOW_ACTIONMANAGER_H
