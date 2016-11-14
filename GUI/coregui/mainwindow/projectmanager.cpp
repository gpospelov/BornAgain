// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectmanager.cpp
//! @brief     Implements class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "projectmanager.h"
#include "AppSvc.h"
#include "ApplicationModels.h"
#include "GUIHelpers.h"
#include "ProjectLoadWarningDialog.h"
#include "WarningMessageService.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "newprojectdialog.h"
#include "projectdocument.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>

ProjectManager::ProjectManager(MainWindow *parent)
    : m_mainWindow(parent)
    , m_project_document(0)
    , m_messageService(new WarningMessageService)

{
    createNewProject();
    AppSvc::subscribe(this);
}


ProjectManager::~ProjectManager()
{
    AppSvc::unsubscribe(this);
    delete m_project_document;
    delete m_messageService;
}


//! Close current project. Call save/discard/cancel dialog, if necessary.
//! Returns false if saving was canceled.
bool ProjectManager::closeCurrentProject()
{
    bool projectWasClosed(true);

    if(m_project_document && m_project_document->isModified()) {
        QMessageBox msgBox;
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              if(!saveProject()) projectWasClosed = false;
              break;
          case QMessageBox::Discard:
              break;
          case QMessageBox::Cancel:
              projectWasClosed = false;
              break;
          default:
              break;
        }
    }

    if(projectWasClosed) deleteCurrentProject();

    return projectWasClosed;
}


//! call dialog window to define project path and name
void ProjectManager::createNewProject()
{
    if(m_project_document)
        throw GUIHelpers::Error("ProjectManager::createNewProject() -> Project already exists");

    m_messageService->clear();

    m_project_document = new ProjectDocument();
    connect(m_project_document, SIGNAL(modified()), this, SLOT(onDocumentModified()));
    m_project_document->setProjectName("Untitled");
    m_project_document->setApplicationModels(m_mainWindow->models());
    m_project_document->setLogger(m_messageService);
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

    NewProjectDialog dialog(m_mainWindow, getDefaultWorkingDirectory(), getUntitledProjectName());

    if (dialog.exec() == QDialog::Accepted) {
        createNewProject();
        m_defaultWorkingDirectory = dialog.getWorkingDirectory();
        m_project_document->setProjectFileName(dialog.getProjectFileName());
        saveProject();
        emit modified();
    }
}


bool ProjectManager::saveProject()
{
    Q_ASSERT(m_project_document);
    qDebug() << "ProjectManager::saveProject()";

    if(!m_project_document->hasValidNameAndPath()) {
        NewProjectDialog dialog(m_mainWindow, getDefaultWorkingDirectory(), getUntitledProjectName());

        if (dialog.exec() == QDialog::Accepted) {
            m_defaultWorkingDirectory = dialog.getWorkingDirectory();
            m_project_document->setProjectFileName(dialog.getProjectFileName());
        } else {
           return false;
        }
    }

    bool success = m_project_document->save();
    if(success == false) {
        QMessageBox::warning(m_mainWindow, "Error while saving project",
                             QString("Failed to save project under '%1'.")
                             .arg(m_project_document->getProjectDir()));
        return false;

     }

    addToRecentProjects();
    modified();

    return true;
}

bool ProjectManager::saveProjectAs()
{
    NewProjectDialog dialog(m_mainWindow, getDefaultWorkingDirectory(), getUntitledProjectName());

    if (dialog.exec() == QDialog::Accepted) {
        m_defaultWorkingDirectory = dialog.getWorkingDirectory();
        m_project_document->setProjectFileName(dialog.getProjectFileName());
        m_project_document->save();
        addToRecentProjects();
    } else {
        return false;
    }

    modified();
    return true;
}

//! Opens existing project. If fileName is empty, will popup file selection dialog
void ProjectManager::openProject(QString fileName)
{
    qDebug() << "ProjectManager::openProject()" << fileName;
    if( !closeCurrentProject()) return;

    if(fileName.isEmpty()) {
        fileName = QFileDialog::getOpenFileName(m_mainWindow, "Open project file",
                                                    getDefaultWorkingDirectory(),
                                         "BornAgain project Files (*.pro)");

        if(fileName.isEmpty()) return;

    }

    createNewProject();

    m_project_document->load(fileName);

    if(m_project_document->isReady()) {
        addToRecentProjects();

    } else if (m_project_document->hasErrors()) {
        riseProjectLoadFailedDialog();
        deleteCurrentProject();
        createNewProject();

    } else if(m_project_document->hasWarnings()) {
        riseProjectLoadWarningDialog();
        addToRecentProjects();
    }

    emit projectOpened();
    emit modified();
}

//! Add name of the current project to the name of recent projects
void ProjectManager::addToRecentProjects()
{
    QString fileName = m_project_document->getProjectFileName();
    m_recentProjects.removeAll(fileName);
    m_recentProjects.prepend(fileName);
    while (m_recentProjects.size() > Constants::MAX_RECENT_PROJECTS)
        m_recentProjects.removeLast();
}

//! read settings of ProjectManager from global settings
void ProjectManager::readSettings()
{
    QSettings settings;
    m_defaultWorkingDirectory = QDir::homePath();
    if(settings.childGroups().contains(Constants::S_PROJECTMANAGER)) {
        settings.beginGroup(Constants::S_PROJECTMANAGER);
        m_defaultWorkingDirectory = settings.value(Constants::S_DEFAULTPROJECTPATH).toString();
        m_recentProjects = settings.value(Constants::S_RECENTPROJECTS).toStringList();
        settings.endGroup();
    }
}

//! saves settings of ProjectManager in global settings
void ProjectManager::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_PROJECTMANAGER);
    settings.setValue(Constants::S_DEFAULTPROJECTPATH, m_defaultWorkingDirectory);
    settings.setValue(Constants::S_RECENTPROJECTS, m_recentProjects);
    settings.endGroup();
}

//! returns list of recent projects, validates if projects still exists on disk
QStringList ProjectManager::getRecentProjects()
{
    QStringList updatedList;
    foreach(QString fileName, m_recentProjects) {
        QFile fin(fileName);
        if(fin.exists()) updatedList.append(fileName);
    }
    m_recentProjects = updatedList;
    return m_recentProjects;
}

//!returns name of the current project directory
QString ProjectManager::getProjectDir() const
{
    if(m_project_document && m_project_document->hasValidNameAndPath()) {
        return m_project_document->getProjectDir();
    }
    return QString();
}

//! Returns directory name suitable for saving plots
QString ProjectManager::userExportDir() const
{
    QString result = getProjectDir();
    if(result.isEmpty()) {
        result = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    }
    return result;
}

//! Returns directory name which was used by the user to import files.
QString ProjectManager::userImportDir() const
{
    QString result;
    QSettings settings;
    if(settings.childGroups().contains(Constants::S_PROJECTMANAGER)) {
        settings.beginGroup(Constants::S_PROJECTMANAGER);
        result = settings.value(Constants::S_LASTUSEDIMPORTDIR, QString()).toString();
        settings.endGroup();
    }
    if(result.isEmpty())
        result = userExportDir();

    return result;
}

//! Set user import directory in system settings
void ProjectManager::setImportDir(const QString &dirname)
{
    QSettings settings;
    if(settings.childGroups().contains(Constants::S_PROJECTMANAGER)) {
        settings.beginGroup(Constants::S_PROJECTMANAGER);
        settings.setValue(Constants::S_LASTUSEDIMPORTDIR, dirname);
        settings.endGroup();
    }
}

//! clear list of recent projects
void ProjectManager::clearRecentProjects()
{
    m_recentProjects.clear();
    modified();
}

//! returns default project path
QString ProjectManager::getDefaultWorkingDirectory()
{
    return m_defaultWorkingDirectory;
}

//! Will return 'Untitled' if the directory with such name doesn't exist in project
//! path. Otherwise will return Untitled1, Untitled2 etc.
QString ProjectManager::getUntitledProjectName()
{
    QString result = "Untitled";
    QDir projectDir = getDefaultWorkingDirectory() + "/" + result;
    if(projectDir.exists()) {
        for(size_t i=1; i<99; ++i) {
            result = QString("Untitled")+QString::number(i);
            projectDir = getDefaultWorkingDirectory() + "/" + result;
            if(!projectDir.exists()) break;
        }
    }
    return result;
}

void ProjectManager::riseProjectLoadFailedDialog()
{
    QString message = QString("Failed to load the project '%1' \n\n")
            .arg(m_project_document->getProjectFileName());

    QString details = m_messageService->getMessages(m_project_document);
    message.append(details);

    QMessageBox::warning(m_mainWindow, "Error while opening project file", message);
}

void ProjectManager::riseProjectLoadWarningDialog()
{
    Q_ASSERT(m_project_document);
    ProjectLoadWarningDialog *warningDialog
            = new ProjectLoadWarningDialog(m_mainWindow, m_messageService,
                                           m_project_document->getDocumentVersion());

    warningDialog->show();
    warningDialog->raise();
}

void ProjectManager::deleteCurrentProject()
{
    delete m_project_document;
    m_project_document = 0;
    m_mainWindow->models()->resetModels();
}


