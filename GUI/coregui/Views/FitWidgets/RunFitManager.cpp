// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitManager.cpp
//! @brief     Implements class RunFitManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RunFitManager.h"
#include "FittingWorker.h"
#include "FitSuite.h"
#include <QThread>
#include <memory>
#include <QDebug>

RunFitManager::RunFitManager(QObject *parent)
    : QObject(parent)
    , m_fitSuite(nullptr)
    , m_is_fit_running{false}
    , m_duration(0)
{
}

void RunFitManager::setFitSuite(std::shared_ptr<FitSuite> suite)
{
    m_fitSuite = suite;
}

// start fitting in separate thread
void RunFitManager::runFitting()
{
    if (!m_fitSuite || m_is_fit_running)
        return;

    QThread *thread = new QThread();
    FittingWorker *fw = new FittingWorker(m_fitSuite);
    fw->moveToThread(thread);

    // start fitting when thread starts
    connect(thread, SIGNAL(started()), fw, SLOT(startFit()));
    connect(fw, SIGNAL(started()), this, SLOT(intern_workerStarted()));

    connect(this, SIGNAL(intern_interruptFittingWorker()), fw, SLOT(interruptFitting()),
            Qt::DirectConnection);

    connect(fw, SIGNAL(error(QString)), this, SLOT(intern_error(QString)));

    connect(fw, SIGNAL(finished(int)), this, SLOT(intern_workerFinished(int)));

    // delete fitting worker and thread when done
    connect(fw, SIGNAL(finished()), fw, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    m_is_fit_running = true;
    thread->start();
}

//! Returns duration of fit in msec.

int RunFitManager::getDuration()
{
    return m_duration;
}

void RunFitManager::interruptFitting()
{
    if (m_is_fit_running) {
        emit intern_interruptFittingWorker();
    }
}

void RunFitManager::intern_workerFinished(int duration)
{
    m_is_fit_running = false;
    m_duration = duration;
    m_fitSuite.reset();
    emit finishedFitting();
}

void RunFitManager::intern_workerStarted()
{
    emit startedFitting();
}

void RunFitManager::intern_error(const QString &mesg)
{
    emit error(mesg);
}
