// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectmanager.h
//! @brief     Declares class ProjectManager
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

//! handles activity related to opening/save projects
class BA_CORE_API_ ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);
    virtual ~ProjectManager();

    void createNewProject();
    bool closeCurrentProject();

    void readSettings();
    void writeSettings();

    QStringList getRecentProjects();

    ProjectDocument *getDocument() { return m_project_document; }

    QString getProjectDir() const;

    QString userExportDir() const;
    QString userImportDir() const;
    void setImportDir(const QString &dirname);

signals:
    void modified();
    void projectOpened();

public slots:
    void clearRecentProjects();
    void onDocumentModified();
    bool saveProject();
    bool saveProjectAs();
    void openProject(QString fileName = QString());
    void newProject();

private:
//    ProjectDocument *createNewProject();
    void addToRecentProjects();

    QString getDefaultWorkingDirectory();
    QString getUntitledProjectName();

    void riseProjectLoadFailedDialog();
    void riseProjectLoadWarningDialog();

    void deleteCurrentProject();

    MainWindow *m_mainWindow;

    ProjectDocument *m_project_document;

    QString m_defaultWorkingDirectory;
    QStringList m_recentProjects;
    WarningMessageService *m_messageService;
};

#endif // PROJECTMANAGER_H
