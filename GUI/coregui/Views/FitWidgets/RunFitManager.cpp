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
#include "FitSuite.h"
#include "FittingWorker.h"
#include <QThread>

RunFitManager::RunFitManager(QObject* parent)
    : QObject(parent)
    , m_is_fit_running(false)
    , m_duration(0)
{
}

// start fitting in separate thread
void RunFitManager::runFitting(std::shared_ptr<FitSuite> suite)
{
    if (!suite || m_is_fit_running)
        return;

    auto thread = new QThread();
    auto fw = new FittingWorker(suite);
    fw->moveToThread(thread);

    // start fitting when thread starts
    connect(thread, &QThread::started, fw, &FittingWorker::startFit);
    connect(fw, &FittingWorker::started, this, &RunFitManager::intern_workerStarted);

    connect(this, &RunFitManager::intern_interruptFittingWorker,
            fw, &FittingWorker::interruptFitting, Qt::DirectConnection);

    connect(fw, &FittingWorker::error, this, &RunFitManager::intern_error);
    connect(fw, &FittingWorker::finished, this, &RunFitManager::intern_workerFinished);

    // delete fitting worker and thread when done
    connect(fw, SIGNAL(finished(int)), fw, SLOT(deleteLater()));
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

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
    if (m_is_fit_running)
        emit intern_interruptFittingWorker();
}

void RunFitManager::intern_workerFinished(int duration)
{
    m_is_fit_running = false;
    m_duration = duration;
    emit fittingFinished();
}

void RunFitManager::intern_workerStarted()
{
    emit fittingStarted();
}

void RunFitManager::intern_error(const QString& mesg)
{
    emit fittingError(mesg);
}
