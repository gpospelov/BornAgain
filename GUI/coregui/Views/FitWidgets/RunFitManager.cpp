// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitManager.cpp
//! @brief     Implements class RunFitManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RunFitManager.h"
#include "FittingWorker.h"
#include "FitSuite.h"
#include <QThread>

RunFitManager::RunFitManager(QObject *parent = 0)
    : QObject(parent), m_fitSuite(0), m_is_fit_running(0)
{
}

void RunFitManager::setFitSuite(boost::shared_ptr<FitSuite> suite)
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

    connect(fw, SIGNAL(finished()), this, SLOT(intern_workerFinished()));

    // delete fitting worker and thread when done
    connect(fw, SIGNAL(finished()), fw, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    m_is_fit_running = true;
    thread->start();
}

void RunFitManager::interruptFitting()
{
    if (m_is_fit_running) {
        emit intern_interruptFittingWorker();
    }
}

void RunFitManager::intern_workerFinished()
{
    m_is_fit_running = false;
    emit finishedFitting();
}

void RunFitManager::intern_workerStarted()
{
    emit startedFitting();
}
