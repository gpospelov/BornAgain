// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveService.h
//! @brief     Implements class SaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SaveService.h"
#include "UpdateTimer.h"
#include "SaveThread.h"
#include "AutosaveController.h"
#include "projectdocument.h"
#include "ProjectUtils.h"
#include <QDebug>

SaveService::SaveService(QObject* parent)
    : QObject(parent)
    , m_is_saving(false)
    , m_autosave(nullptr)
    , m_document(nullptr)
{

}

void SaveService::setDocument(ProjectDocument* document)
{
    m_document = document;

    if (m_autosave)
        m_autosave->setDocument(document);

    m_save_queue.clear();
}

void SaveService::save(const QString& project_file_name)
{
    Q_ASSERT(m_document);
    qDebug() << "SaveService::save() -> Project saving. Putting in a queue:" << project_file_name;

    m_save_queue.enqueue(project_file_name);
    process_queue();
}

void SaveService::setAutosaveEnabled(bool value)
{
    if (value) {
        delete m_autosave;
        m_autosave = new AutosaveController(this);
        m_autosave->setDocument(m_document);
        connect(m_autosave, &AutosaveController::autosaveRequest,
                this, &SaveService::onAutosaveRequest);
    } else {
        delete m_autosave;
        m_autosave = 0;
    }
}

void SaveService::setAutosaveTime(int timerInterval)
{
    if(!m_autosave)
        setAutosaveEnabled(true);

    m_autosave->setAutosaveTime(timerInterval);
}

bool SaveService::isSaving() const
{
    return m_is_saving;
}

void SaveService::onAutosaveRequest()
{
    qDebug() << "SaveService::onAutosaveRequest() -> saving into " << m_autosave->autosaveName();
    save(m_autosave->autosaveName());
}

void SaveService::onProjectSaved()
{
    Q_ASSERT(m_document);
    Q_ASSERT(m_is_saving);

    qDebug() << "SaveService::onProjectSaved() -> Project was saved.";

    m_is_saving = false;
    emit projectSaved();

    // processing possible consequent saves
    process_queue();
}

void SaveService::process_queue()
{
    Q_ASSERT(m_document);

    qDebug() << "SaveService::process_queue() -> m_is_saving" << m_is_saving;

    if (m_is_saving) {
        qDebug() << "SaveService::save() -> Project is under saving. Waiting.";
        return;
    }

    if (!m_save_queue.isEmpty()) {
        qDebug() << "SaveService::save() -> Preparint to run a thread";
        m_is_saving = true;

        QString project_file_name = m_save_queue.dequeue();

        // saving project file in a main thread
        bool isAutosave = project_file_name.contains(ProjectUtils::autosaveSubdir()) ? true : false;
        m_document->save_project_file(project_file_name, isAutosave);

        if(m_document->hasData()) {
            // saving heavy data in separate thread
            SaveThread *saveThread = new SaveThread(this);
            saveThread->setSaveContext(m_document, project_file_name);

            connect(saveThread, &SaveThread::saveReady, this, &SaveService::onProjectSaved);
            connect(saveThread, &SaveThread::finished, saveThread, &QObject::deleteLater);
            saveThread->start();
        } else {
            onProjectSaved();
        }
    }
}

