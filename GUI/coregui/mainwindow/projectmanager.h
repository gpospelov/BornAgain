#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#include <QObject>
#include <QString>
class MainWindow;

//! class responsible for opening and saving projects
class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);

    QString getProjectPath() const { return m_project_path; }
    QString getProjectName() const { return m_project_name; }

    //! call dialog window to define project path and name
    void newProject();

private:

    QString getUntitledProjectName();

    MainWindow *m_mainWindow;

    QString m_project_path;
    QString m_project_name;
};


#endif
