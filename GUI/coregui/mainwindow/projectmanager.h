#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QString>
#include <QStringList>
class MainWindow;
class ProjectDocument;
class QSettings;

//! handles activity related to opening/save projects
class BA_CORE_API_ ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);
    ~ProjectManager();

    void createNewProject();
    bool closeCurrentProject();

    void readSettings(QSettings *settings);
    void writeSettings(QSettings *settings);

    QStringList getRecentProjects();

    ProjectDocument *getDocument() { return m_project_document; }

signals:
    void modified();

public slots:
    void clearRecentProjects();
    void onDocumentModified();
    void saveProject();
    void openProject(QString fileName = QString());
    void newProject();

    bool saveModifiedProject();

private:
//    ProjectDocument *createNewProject();
    void addToRecentProjects();

    QString getDefaultProjectPath();
    QString getUntitledProjectName();

    MainWindow *m_mainWindow;

    ProjectDocument *m_project_document;

    QString m_defaultProjectPath;
    QStringList m_recentProjects;

};


#endif
