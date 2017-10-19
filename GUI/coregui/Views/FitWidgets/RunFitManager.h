// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorkerLauncher.h
//! @brief     Implements class FitWorkerLauncher
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITWORKERLAUNCHER_H
#define FITWORKERLAUNCHER_H

#include "WinDllMacros.h"
#include <QObject>
#include <atomic>
#include <memory>

class FitSuite;

class BA_CORE_API_ FitWorkerLauncher : public QObject
{
    Q_OBJECT

public:
    FitWorkerLauncher(QObject* parent);

    void runFitting(std::shared_ptr<FitSuite> suite);

    int getDuration();

public slots:
    void interruptFitting();

signals:
    void fittingStarted();
    void fittingFinished();
    void fittingError(const QString& message);
    void intern_interruptFittingWorker();

private slots:
    void intern_workerFinished(int duration);

    void intern_workerStarted();

    void intern_error(const QString& mesg);

private:
    std::atomic<bool> m_is_fit_running;
    int m_duration;
};

#endif // FITWORKERLAUNCHER_H
