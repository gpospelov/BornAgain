// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/projectmanager.cpp
//! @brief     Implements class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "projectmanager.h"
#include "newprojectdialog.h"
#include "mainwindow.h"
#include "projectdocument.h"
#include "actionmanager.h"
#include "mainwindow_constants.h"
#include "GUIHelpers.h"
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
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


//! Close current project. Call save/discard/cancel dialog, if necessary.
//! Returns false if saving was canceled.
bool ProjectManager::closeCurrentProject()
{
    bool returnVal = true;
    if(m_project_document && m_project_document->isModified()) {
        QMessageBox msgBox;
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              qDebug() << "QMessageBox::Save";
              returnVal = saveModifiedProject();
              break;
          case QMessageBox::Discard:
            qDebug() << "QMessageBox::Discard";
              break;
          case QMessageBox::Cancel:
            qDebug() << "QMessageBox::Cancel";
            returnVal = false;
              break;
          default:
              break;
        }
    }

    if(returnVal)
    {
        delete m_project_document;
        m_project_document = 0;
    }

    return returnVal;
}


//! call dialog window to define project path and name
void ProjectManager::createNewProject()
{
    if(m_project_document)
        throw GUIHelpers::Error("ProjectManager::createNewProject() -> Project already exists");

    m_project_document = new ProjectDocument();
    connect(m_project_document, SIGNAL(modified()), this, SLOT(onDocumentModified()));
    m_project_document->setProjectName("Untitled");
    m_project_document->setMaterialModel(m_mainWindow->getMaterialModel());
    m_project_document->setInstrumentModel(m_mainWindow->getInstrumentModel());
    m_project_document->setSampleModel(m_mainWindow->getSampleModel());
//    m_project_document->setJobQueueModel(m_mainWindow->getJobQueueModel());
    m_project_document->setJobModel(m_mainWindow->getJobModel());
}


void ProjectManager::onDocumentModified()
{
    Q_ASSERT(m_project_document);
    if(m_project_document->isModified()) {
        m_mainWindow->setWindowTitle("*"+m_project_document->getProjectName());
    } else {
        m_mainWindow->setWindowTitle(m_project_document->getProjectName());
    }
}


void ProjectManager::newProject()
{
    if( !closeCurrentProject()) return;

    NewProjectDialog dialog(m_mainWindow);
    // give projectDialog something to start with
    dialog.setProjectPath(getDefaultProjectPath());
    dialog.setProjectName(getUntitledProjectName());

    if (dialog.exec() == QDialog::Accepted) {

        createNewProject();

        m_defaultProjectPath = dialog.getProjectPath();
        m_project_document->setProjectName(dialog.getProjectName());
        m_project_document->setProjectPath(dialog.getProjectPath());
        emit modified();
    }

}


void ProjectManager::saveProject()
{
    Q_ASSERT(m_project_document);
    qDebug() << "ProjectManager::saveProject()";

    if(m_project_document->hasValidNameAndPath()) {
        m_project_document->save();
        addToRecentProjects();
    } else {
        NewProjectDialog dialog(m_mainWindow);
        // give projectDialog something to start with
        dialog.setProjectPath(getDefaultProjectPath());
        dialog.setProjectName(getUntitledProjectName());

        if (dialog.exec() == QDialog::Accepted) {
            m_defaultProjectPath = dialog.getProjectPath();
            m_project_document->setProjectName(dialog.getProjectName());
            m_project_document->setProjectPath(dialog.getProjectPath());
            m_project_document->save();
            addToRecentProjects();
        }
    }
}

bool ProjectManager::saveModifiedProject()
{
    Q_ASSERT(m_project_document);
    qDebug() << "ProjectManager::saveProject()";

    if(m_project_document->hasValidNameAndPath()) {
        m_project_document->save();
        addToRecentProjects();
    } else {
        NewProjectDialog dialog(m_mainWindow);
        // give projectDialog something to start with
        dialog.setProjectPath(getDefaultProjectPath());
        dialog.setProjectName(getUntitledProjectName());

        if (dialog.exec() == QDialog::Accepted) {
            m_defaultProjectPath = dialog.getProjectPath();
            m_project_document->setProjectName(dialog.getProjectName());
            m_project_document->setProjectPath(dialog.getProjectPath());
            m_project_document->save();
            addToRecentProjects();
        }
        else
        {
            return false;
        }
    }

    return true;
}


//! Opens existing project. If fileName is empty, will popup file selection dialog
void ProjectManager::openProject(QString fileName)
{
    qDebug() << "ProjectManager::openProject()" << fileName;
    if( !closeCurrentProject()) return;

//    if(fileName.isEmpty()) {
//        fileName = QFileDialog::getOpenFileName(m_mainWindow, tr("Open project file"),
//                                                    getDefaultProjectPath(),
//                                         tr("BornAgain project Files (*.pro)"));
//    }

    if(fileName.isEmpty()) {
        QMessageBox::warning(m_mainWindow, tr("Error while opening project file"),
                             tr("File name is empty."));
        return;
    }

    QFile fin(fileName);
    if(!fin.exists()) {
        QMessageBox::warning(m_mainWindow, tr("Error while opening project file"),
                             QString("File '%1' doesn't exist").arg(fileName));
        return;
    }

    if(!fileName.isEmpty()) {
        createNewProject();
        bool success_read = m_project_document->load(fileName);
        if(!success_read) {
            QMessageBox::warning(m_mainWindow, tr("Error while opening project file"),
                                 QString("Failed to load the project '%1' \n\n%2").arg(fileName).arg(m_project_document->getErrorMessage()));
            delete m_project_document;
            m_project_document = 0;
            m_mainWindow->resetModels();
            createNewProject();
        }
        emit modified();
    }
}


void ProjectManager::addToRecentProjects()
{
    Q_ASSERT(m_project_document);

    std::cout << "ProjectManager::closeProject() -> XXX" << m_project_document->getProjectFileName().toStdString() << std::endl;
    QString fileName = m_project_document->getProjectFileName();

    m_recentProjects.removeAll(fileName);
    m_recentProjects.prepend(fileName);
    while (m_recentProjects.size() > Constants::MAX_RECENT_PROJECTS)
        m_recentProjects.removeLast();
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


