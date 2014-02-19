#include "projectmanager.h"
#include "newprojectdialog.h"
#include "mainwindow.h"
#include "projectdocument.h"
#include "actionmanager.h"
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
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


void ProjectManager::closeCurrentProject()
{
    if(m_project_document) {
        std::cout << "ProjectManager::closeProject() -> XXX" << m_project_document->getProjectFileName().toStdString() << std::endl;
        QString fileName = m_project_document->getProjectFileName();

        m_recentProjects.removeAll(fileName);
        m_recentProjects.prepend(fileName);
        while (m_recentProjects.size() > Constants::MAX_RECENT_PROJECTS)
            m_recentProjects.removeLast();

    }

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

    if (dialog.exec() == QDialog::Accepted) {
        closeCurrentProject();
        m_defaultProjectPath = dialog.getProjectPath();
        m_project_document = new ProjectDocument(dialog.getProjectPath(), dialog.getProjectName());
        m_project_document->save();
        m_mainWindow->setWindowTitle(m_project_document->getProjectName());
    }

}


//! Opens existing project. If fileName is empty, will popup file selection dialog
void ProjectManager::openProject(QString fileName)
{

    if(fileName.isEmpty()) {
        fileName = QFileDialog::getOpenFileName(m_mainWindow, tr("Open project file"),
                                                    getDefaultProjectPath(),
                                         tr("BornAgain project Files (*.pro)"));
    }

    if(!fileName.isEmpty()) {
        ProjectDocument *newdocument = ProjectDocument::openExistingDocument(fileName);
        if(newdocument) {
            closeCurrentProject();
            m_project_document = newdocument;
            m_mainWindow->setWindowTitle(m_project_document->getProjectName());
        }
    }
}




//! read settings of ProjectManager from global settings
void ProjectManager::readSettings(QSettings *settings)
{
    m_defaultProjectPath = QDir::homePath();
    if(settings->childGroups().contains(Constants::S_PROJECTMANAGER)) {
        settings->beginGroup(Constants::S_PROJECTMANAGER);
        m_defaultProjectPath = settings->value("DefaultProjectPath").toString();
        m_recentProjects = settings->value("RecentProjects").toStringList();
        settings->endGroup();
    }
    qDebug() << "ProjectManager::readSettings() -> " << this->objectName() << m_defaultProjectPath << m_recentProjects;
}


//! saves settings of ProjectManager in global settings
void ProjectManager::writeSettings(QSettings *settings)
{
    qDebug() << "ProjectManager::writeSettings() -> Writing " << m_defaultProjectPath << m_recentProjects;
    settings->beginGroup(Constants::S_PROJECTMANAGER);
    settings->setValue("DefaultProjectPath", m_defaultProjectPath);
    settings->setValue("RecentProjects", m_recentProjects);
    settings->endGroup();
}


//! returns list of recent projects
QStringList ProjectManager::getRecentProjects()
{
    return m_recentProjects;
}


//! clear list of recent projects
void ProjectManager::clearRecentProjects()
{
    m_recentProjects.clear();
}


//! returns default project path
QString ProjectManager::getDefaultProjectPath()
{
    return m_defaultProjectPath;
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


