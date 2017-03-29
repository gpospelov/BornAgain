// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectmanager.h
//! @brief     Defines class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QStringList>

class MainWindow;
class ProjectDocument;
class WarningMessageService;
class AutosaveService;

//! Handles activity related to opening/save projects.

class BA_CORE_API_ ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow* parent);
    virtual ~ProjectManager();

    void readSettings();
    void writeSettings();

    ProjectDocument* document();

    QStringList recentProjects();
    QString projectDir() const;
    QString userExportDir() const;
    QString userImportDir() const;
    void setImportDir(const QString& dirname);

signals:
    void modified();
    void projectOpened();

public slots:
    void onDocumentModified();
    void clearRecentProjects();
    void newProject();
    bool closeCurrentProject();
    bool saveProject(QString projectFileName = QString());
    bool saveProjectAs();
    void openProject(QString fileName = QString());

private:
    void createNewProject();
    void deleteCurrentProject();
    QString acquireProjectFileName();
    void addToRecentProjects();

    QString workingDirectory();
    QString untitledProjectName();

    void riseProjectLoadFailedDialog();
    void riseProjectLoadWarningDialog();

    MainWindow* m_mainWindow;
    ProjectDocument* m_project_document;

    //!< Name of directory where project directory was created.
    QString m_workingDirectory;

    //!< Name of directory from there user prefer to import files
    QString m_importDirectory;

    QStringList m_recentProjects;
    WarningMessageService* m_messageService;
    AutosaveService* m_autosaveService;
};

#endif // PROJECTMANAGER_H
