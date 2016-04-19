// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitManager.h
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

#ifndef RUNFITMANAGER_H
#define RUNFITMANAGER_H

#include "WinDllMacros.h"
#include <atomic>
#include <memory>
#include <QObject>

class FitSuite;

class BA_CORE_API_ RunFitManager : public QObject
{
    Q_OBJECT

public:
    RunFitManager(QObject *parent);

    void setFitSuite(std::shared_ptr<FitSuite> suite);

    void runFitting();

public slots:
    void interruptFitting();

signals:
    void finishedFitting();

    void startedFitting();

    void error(const QString &message);

// only used by manager for communication with FittingWorker
private slots:
    void intern_workerFinished();

    void intern_workerStarted();

    void intern_error(const QString &mesg);

signals:
    void intern_interruptFittingWorker();

private:
    std::shared_ptr<FitSuite> m_fitSuite;
    std::atomic<bool> m_is_fit_running;
};

#endif
