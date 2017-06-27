// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AutosaveController.cpp
//! @brief     Implements class AutosaveController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "AutosaveController.h"
#include "projectdocument.h"
#include "UpdateTimer.h"
#include "GUIHelpers.h"
#include "ProjectUtils.h"
#include <QDir>
#include <QDebug>

namespace
{
const int update_every = 5000; // in msec
}

AutosaveController::AutosaveController(QObject* parent)
    : QObject(parent), m_document(0), m_timer(new UpdateTimer(update_every, this))
{
    connect(m_timer, SIGNAL(timeToUpdate()), this, SLOT(onTimerTimeout()));
}

void AutosaveController::setDocument(ProjectDocument* document)
{
    if(document == m_document)
        return;

    m_timer->reset();

    if(m_document)
        setDocumentConnected(false);

    m_document = document;

    if(m_document)
        setDocumentConnected(true);

    onDocumentModified();
}

void AutosaveController::setAutosaveTime(int timerInterval)
{
    m_timer->reset();
    m_timer->setTimeInterval(timerInterval);
}

//! Returns the name of autosave directory.

QString AutosaveController::autosaveDir() const
{
    if (m_document && m_document->hasValidNameAndPath())
        return ProjectUtils::autosaveDir(m_document->projectFileName());

    return QString();
}

QString AutosaveController::autosaveName() const
{
    if (m_document && m_document->hasValidNameAndPath())
        return ProjectUtils::autosaveName(m_document->projectFileName());

    return QString();
}


void AutosaveController::removeAutosaveDir()
{
    if(autosaveDir().isEmpty())
        return;

    QDir dir(autosaveDir());
    dir.removeRecursively();
}

void AutosaveController::onTimerTimeout()
{
    if (m_document->isModified())
        autosave();
}

void AutosaveController::onDocumentDestroyed(QObject* object)
{
    Q_UNUSED(object);
    m_timer->reset();
    m_document = 0;
}

void AutosaveController::onDocumentModified()
{
    if(!m_document)
        return;

    qDebug() << "AutosaveController::onDocumentModified()  isModified:"
             << m_document->isModified() << " hasValidName:" << m_document->hasValidNameAndPath();
    if (m_document->isModified() && m_document->hasValidNameAndPath()) {
        qDebug() << "AutosaveController::onDocumentModified() -> scheduleUpdate()";
        m_timer->scheduleUpdate();
    }
}

void AutosaveController::autosave()
{
    QString name = autosaveName();
    if (!name.isEmpty()) {
        GUIHelpers::createSubdir(m_document->projectDir(), ProjectUtils::autosaveSubdir());

        qDebug() << "       AutosaveService::autosave() -> emitting autosave request";
        emit autosaveRequest();
    }
}

void AutosaveController::setDocumentConnected(bool set_connected)
{
    if(!m_document)
        return;

    if(set_connected) {
        connect(m_document, SIGNAL(destroyed(QObject*)),
                this, SLOT(onDocumentDestroyed(QObject*)), Qt::UniqueConnection);
        connect(m_document, SIGNAL(modified()), this,
                SLOT(onDocumentModified()), Qt::UniqueConnection);
    } else {
        disconnect(m_document, SIGNAL(destroyed(QObject*)),
                this, SLOT(onDocumentDestroyed(QObject*)));
        disconnect(m_document, SIGNAL(modified()), this,
                SLOT(onDocumentModified()));
    }
}
