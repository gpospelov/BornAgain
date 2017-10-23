// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionController.h
//! @brief     Defines class FitSessionController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSESSIONCONTROLLER_H
#define FITSESSIONCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>
#include <memory>

class JobItem;
class FitWorkerLauncher;
class GUIFitObserver;
class FitProgressInfo;
class FitLog;

//! Controls all activity related to the single fitting task for JobItem.
//! Provides interaction between FitSessionWidget and fit observers.

class BA_CORE_API_ FitSessionController : public QObject
{
    Q_OBJECT
public:
    FitSessionController(QObject* parent = nullptr);
    ~FitSessionController();

    void setItem(JobItem* item);

    FitLog* fitLog();

signals:
    void fittingStarted();
    void fittingFinished();
    void fittingError(const QString& message);

public slots:
    void onStartFittingRequest();
    void onStopFittingRequest();

private slots:
    void onPlotsUpdate();
    void onFittingStarted();
    void onFittingFinished();
    void onFittingError(const QString& text);
    void onProgressInfoUpdate(const FitProgressInfo& info);
    void updateIterationCount(const FitProgressInfo& info);
    void updateFitParameterValues(const FitProgressInfo& info);
    void updateLog(const FitProgressInfo& info);

private:
    JobItem* m_jobItem;
    FitWorkerLauncher* m_runFitManager;
    std::shared_ptr<GUIFitObserver> m_observer;
    std::unique_ptr<FitLog> m_fitlog;
    bool m_block_progress_update;
};

#endif // FITSESSIONCONTROLLER_H
