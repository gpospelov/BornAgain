#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#include <QObject>
#include <QString>
#include <QStringList>
class MainWindow;
class ProjectDocument;
class QSettings;

//! handles activity related to opening/save projects
class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);
    ~ProjectManager();

    void createNewProject();
    void openProject(QString fileName = QString());
    void closeCurrentProject();

    void readSettings(QSettings *settings);
    void writeSettings(QSettings *settings);

    QStringList getRecentProjects();

public slots:
    void clearRecentProjects();

private:

    QString getDefaultProjectPath();
    QString getUntitledProjectName();

    MainWindow *m_mainWindow;

    ProjectDocument *m_project_document;

    QString m_defaultProjectPath;
    QStringList m_recentProjects;

};


#endif
