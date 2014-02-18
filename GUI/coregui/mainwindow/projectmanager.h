#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#include <QObject>
#include <QString>
class MainWindow;
class ProjectDocument;

//! handles activity related to opening/save projects
class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow *parent);
    ~ProjectManager();

    void createNewProject();
    void openExistingProject();
    void closeProject();

private:

    QString getUntitledProjectName();
    QString getDefaultProjectPath();

    MainWindow *m_mainWindow;


    ProjectDocument *m_project_document;


};


#endif
