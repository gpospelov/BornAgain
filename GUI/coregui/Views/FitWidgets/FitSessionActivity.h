// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionActivity.h
//! @brief     Defines class FitSessionActivity
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSESSIONACTIVITY_H
#define FITSESSIONACTIVITY_H

#include "WinDllMacros.h"
#include <QObject>
#include <memory>

class JobItem;
class FitWorkerLauncher;
class GUIFitObserver;
class FitProgressInfo;
class FitLog;

//! Handles all activity related to the single fitting task for JobItem.
//! Provides interaction between FitSessionWidget and fit observers.

class BA_CORE_API_ FitSessionActivity : public QObject
{
    Q_OBJECT
public:
    FitSessionActivity(QObject* parent = nullptr);
    ~FitSessionActivity();

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

#endif // FITSESSIONACTIVITY_H
