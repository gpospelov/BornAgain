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

AutosaveService::AutosaveService(QObject* parent)
    : QObject(parent)
    , m_document(0)
    , m_timer(new QTimer(this))
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

    if(m_document->isModified())
        autosave();


    m_timer->start(5000);

}

void AutosaveService::onTimerTimeout()
{
    qDebug() << "AutosaveService::onTimerTimeout()" << m_document;
    Q_ASSERT(m_document);

    if(m_document->isModified())
        autosave();
}

void AutosaveService::onDocumentDestroyed(QObject* object)
{
    qDebug() << "AutosaveService::onDocumentDestroyed" << m_document << object;
    Q_ASSERT(m_document == object);

    m_timer->stop();
    m_document = 0;
}

void AutosaveService::autosave()
{
    Q_ASSERT(m_document);
    qDebug() << "AutosaveService::autosave()";

}
