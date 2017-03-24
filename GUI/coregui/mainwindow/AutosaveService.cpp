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
#include <QTimer>
#include <QDebug>

namespace {
    const int update_every = 10000; // in msec
}

AutosaveService::AutosaveService(QObject* parent)
    : QObject(parent)
    , m_document(0)
    , m_timer(new QTimer(this))
    , m_modificationCount(0)
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
}

void AutosaveService::setDocument(ProjectDocument* document)
{
    qDebug() << "AutosaveService::setDocument" << document;

    Q_ASSERT(m_timer->isActive() == false);

    m_document = document;

    if(!m_document)
        return;

    connect(m_document, SIGNAL(destroyed(QObject*)), this,
            SLOT(onDocumentDestroyed(QObject*)));

    connect(m_document, SIGNAL(modified()), this,
            SLOT(onDocumentModified()));

    if(isDocumentForAutosave()) {
        qDebug() << "Starting timer first time";
        m_timer->start(update_every);
    }

}

void AutosaveService::onTimerTimeout()
{
    qDebug() << "AutosaveService::onTimerTimeout()" << m_document << m_document->isModified() << m_modificationCount;
    Q_ASSERT(m_document);

    if(m_document->isModified() && m_modificationCount!=0)
        autosave();
}

void AutosaveService::onDocumentDestroyed(QObject* object)
{
    qDebug() << "AutosaveService::onDocumentDestroyed" << m_document << object;
    Q_ASSERT(m_document == object);

    m_timer->stop();
    m_document = 0;
    m_modificationCount = 0;
}

//!

void AutosaveService::onDocumentModified()
{
    qDebug() << "AutosaveService::onDocumentModified()" << m_modificationCount << m_document->isModified();
    if(m_document->isModified())
        ++m_modificationCount;

    if(isDocumentForAutosave() && !m_timer->isActive()) {
        qDebug() << "Starting timer";
        m_timer->start(update_every);
    }
}

void AutosaveService::autosave()
{
    Q_ASSERT(m_document);
    qDebug() << "AutosaveService::autosave()";

    QString name = autosaveName();
    if(!name.isEmpty()) {
        bool result = m_document->save(name, true);
        qDebug() << "   saving ..." << name << "result" << result;
        m_modificationCount = 0;
    }
}

bool AutosaveService::isDocumentForAutosave()
{
    return m_document->hasValidNameAndPath() && m_document->isModified();
}

//! Return name for temporary project file.

QString AutosaveService::autosaveName() const
{
    qDebug() << "AutosaveService::autosaveName()" << m_document->hasValidNameAndPath() << m_document->getProjectDir() << m_document->getProjectName();
    Q_ASSERT(m_document);

    if(!m_document->hasValidNameAndPath())
        return QString();

    QString result = m_document->getProjectFileName();

    int index = result.lastIndexOf(m_document->getProjectFileExtension());
    result.remove(index, m_document->getProjectFileExtension().size());
    result.append(".temp");

    return result;
}
