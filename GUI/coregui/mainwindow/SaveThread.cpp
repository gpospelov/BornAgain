// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveThread.h
//! @brief     Defines SaveThread classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SaveThread.h"
#include "projectdocument.h"
#include <QDebug>

SaveThread::SaveThread(QObject* parent)
    : QThread(parent)
    , m_document(nullptr)
{

}

SaveThread::~SaveThread()
{
    qDebug() << "SaveThread::~SaveThread() -> waiting";
    wait();
    qDebug() << "SaveThread::~SaveThread() -> done";
}

void SaveThread::run()
{
    qDebug() << "SaveThread::run() -> " << m_projectFile;
    Q_ASSERT(m_document);
    m_document->save_project_data(m_projectFile);
    qDebug() << "SaveThread::run() -> Ready. Emitting saveReady()";
    emit saveReady();
}

void SaveThread::setSaveContext(ProjectDocument* document, const QString& project_file_name)
{
    qDebug() << "SaveThread::setSaveContext" << project_file_name;
    m_document = document;
    m_projectFile = project_file_name;
}
