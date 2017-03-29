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
#include <QDebug>

namespace
{
const int update_every = 10000; // in msec
}

AutosaveService::AutosaveService(QObject* parent)
    : QObject(parent), m_document(0), m_timer(new UpdateTimer(update_every, this))
{
    connect(m_timer, SIGNAL(timeToUpdate()), this, SLOT(onTimerTimeout()));
}

void AutosaveService::setDocument(ProjectDocument* document)
{
    qDebug() << "AutosaveService::setDocument" << document;

    m_timer->reset();

    m_document = document;

    if (!m_document)
        return;

    connect(m_document, SIGNAL(destroyed(QObject*)), this, SLOT(onDocumentDestroyed(QObject*)));

    connect(m_document, SIGNAL(modified()), this, SLOT(onDocumentModified()));
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

    qDebug() << "AutosaveService::removeAutosaveDir()" << autosaveDir();
    QDir dir(autosaveDir());
    dir.removeRecursively();
}

void AutosaveService::onTimerTimeout()
{
    qDebug() << "AutosaveService::onTimerTimeout()" << m_document << m_document->isModified();
    Q_ASSERT(m_document);

    if (m_document->isModified())
        autosave();
}

void AutosaveService::onDocumentDestroyed(QObject* object)
{
    qDebug() << "AutosaveService::onDocumentDestroyed" << m_document << object;
    Q_ASSERT(m_document == object);

    m_timer->reset();
    m_document = 0;
}

void AutosaveService::onDocumentModified()
{
    qDebug() << "AutosaveService::onDocumentModified()" << m_document << m_document->isModified();
    if (m_document->isModified() && m_document->hasValidNameAndPath()) {
        qDebug() << "   ... scheduling update";
        m_timer->scheduleUpdate();
    }
}

void AutosaveService::autosave()
{
    Q_ASSERT(m_document);
    qDebug() << "AutosaveService::autosave()";

    QString name = autosaveName();
    if (!name.isEmpty()) {
        GUIHelpers::createSubdir(m_document->projectDir(), ProjectUtils::autosaveSubdir());

        qDebug() << "   saving ..." << name;
        bool result = m_document->save(name, true);
        qDebug() << "           save result" << result;
        emit autosaved();
    }
}
