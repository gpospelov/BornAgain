#include "projectmanager.h"
#include "newprojectdialog.h"
#include "mainwindow.h"
#include "projectdocument.h"
#include <QDir>
#include <QFileDialog>
#include <iostream>

ProjectManager::ProjectManager(MainWindow *parent)
    : m_mainWindow(parent)
    , m_project_document(0)

{
    setParent(parent);
}


ProjectManager::~ProjectManager()
{
    delete m_project_document;
}


void ProjectManager::closeProject()
{
    delete m_project_document;
    m_project_document = 0;

}


//! call dialog window to define project path and name
void ProjectManager::createNewProject()
{
    NewProjectDialog dialog(m_mainWindow);
    // give projectDialog something to start with
    dialog.setProjectPath(getDefaultProjectPath());
    dialog.setProjectName(getUntitledProjectName());

    dialog.exec();

    closeProject();
    m_project_document = new ProjectDocument(dialog.getProjectPath(), dialog.getProjectName());
    m_project_document->save();
    m_mainWindow->setWindowTitle(m_project_document->getProjectName());

}



void ProjectManager::openExistingProject()
{
    QString fileName = QFileDialog::getOpenFileName(m_mainWindow, tr("Open project file"),
                                                    getDefaultProjectPath(),
                                         tr("BornAgain project Files (*.pro)"));

    if(!fileName.isEmpty()) {
        ProjectDocument *newdocument = ProjectDocument::openExistingDocument(fileName);
        if(newdocument) {
            closeProject();
            m_project_document = newdocument;
            m_mainWindow->setWindowTitle(m_project_document->getProjectName());
        }
    }
}


//! Will return 'Untitled' if the directory with such name doesn't exist in project
//! path. Otherwise will return Untitled1, Untitled2 etc.
QString ProjectManager::getUntitledProjectName()
{
    QString result = "Untitled";
    QDir projectDir = getDefaultProjectPath() + "/" + result;
    if(projectDir.exists()) {
        for(size_t i=1; i<99; ++i) {
            result = QString("Untitled")+QString::number(i);
            projectDir = getDefaultProjectPath() + "/" + result;
            if(!projectDir.exists()) break;
        }
    }
    return result;
}


//! return default project path
QString ProjectManager::getDefaultProjectPath()
{
    return QDir::homePath();
}

