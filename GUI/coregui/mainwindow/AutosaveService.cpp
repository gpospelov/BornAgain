// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AutosaveService.cpp
//! @brief     Implements class AutosaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "AutosaveService.h"
#include "projectdocument.h"
#include "UpdateTimer.h"
#include "GUIHelpers.h"
#include "ProjectUtils.h"
#include <QDir>

namespace
{
const int update_every = 5000; // in msec
}

AutosaveService::AutosaveService(QObject* parent)
    : QObject(parent), m_document(0), m_timer(new UpdateTimer(update_every, this))
{
    connect(m_timer, SIGNAL(timeToUpdate()), this, SLOT(onTimerTimeout()));
}

void AutosaveService::setDocument(ProjectDocument* document)
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

void AutosaveService::setAutosaveTime(int timerInterval)
{
    m_timer->setTimeInterval(timerInterval);
}

//! Returns the name of autosave directory.

QString AutosaveService::autosaveDir() const
{
    if (m_document->hasValidNameAndPath())
        return ProjectUtils::autosaveDir(m_document->projectFileName());

    return QString();
}

QString AutosaveService::autosaveName() const
{
    if (m_document->hasValidNameAndPath())
        return ProjectUtils::autosaveName(m_document->projectFileName());

    return QString();
}


void AutosaveService::removeAutosaveDir()
{
    if(autosaveDir().isEmpty())
        return;

    QDir dir(autosaveDir());
    dir.removeRecursively();
}

void AutosaveService::onTimerTimeout()
{
    if (m_document->isModified())
        autosave();
}

void AutosaveService::onDocumentDestroyed(QObject* object)
{
    Q_UNUSED(object);
    m_timer->reset();
    m_document = 0;
}

void AutosaveService::onDocumentModified()
{
    if (m_document->isModified() && m_document->hasValidNameAndPath())
        m_timer->scheduleUpdate();
}

#include <QDebug>
void AutosaveService::autosave()
{
    QString name = autosaveName();
    if (!name.isEmpty()) {
        GUIHelpers::createSubdir(m_document->projectDir(), ProjectUtils::autosaveSubdir());

        qDebug() << "       auto-saving";

        if(m_document->isSaving()) {
            qDebug() << "       skipping autosave";
            onDocumentModified();
            return;
        }

        if(!m_document->save(name, true))
            throw GUIHelpers::Error("AutosaveService::autosave() -> Error during autosave.");

        emit autosaved();
    }
}

void AutosaveService::setDocumentConnected(bool set_connected)
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
