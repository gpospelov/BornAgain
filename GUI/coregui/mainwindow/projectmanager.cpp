#include "projectmanager.h"
#include "newprojectdialog.h"
#include "mainwindow.h"
#include <QDir>
#include <iostream>

ProjectManager::ProjectManager(MainWindow *parent)
    : m_mainWindow(parent)
    , m_project_path(QDir::homePath())

{
    setParent(parent);
}



void ProjectManager::newProject()
{
    NewProjectDialog dialog(m_mainWindow);
    dialog.setProjectPath(getProjectPath());
    dialog.setProjectName(getUntitledProjectName());
    dialog.exec();

}


// will return 'Untitled' if it doesn't exist in the project_path (i.e. /home/username),
// otherwise Untitled1, Untitled2 etc...
QString ProjectManager::getUntitledProjectName()
{
    QString result = "Untitled";
    QDir projectDir = getProjectPath() + "/" + result;
    if(projectDir.exists()) {
        std::cout << "ProjectManager::getUntitledProjectName() -> exists " << result.toStdString() << std::endl;
        for(size_t i=1; i<99; ++i) {
            result = QString("Untitled")+QString::number(i);
            projectDir = getProjectPath() + "/" + result;
            if(!projectDir.exists()) break;
            std::cout << "ProjectManager::getUntitledProjectName() -> exists " << result.toStdString() << std::endl;
        }
    }
    return result;
}



