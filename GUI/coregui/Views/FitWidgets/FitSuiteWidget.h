// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteWidget.h
//! @brief     Declares class FitSuiteWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEWIDGET_H
#define FITSUITEWIDGET_H

#include "WinDllMacros.h"
#include "FitProgressInfo.h"
#include <QWidget>
#include <memory>

class QTabWidget;
class JobModel;
class JobItem;
class SessionItem;
class FitParameterWidget;
class MinimizerSettingsWidget;
class FitResultsWidget;
class ParameterTuningWidget;
class RunFitManager;
class GUIFitObserver;
template <class T> class OutputData;
//class FitProgressInfo;


//! The FitSuiteWidget contains all fit settings for given JobItem (fit parameters,
//! minimizer settings) and all logic to communicate with fit observers.
//! Controlled by FitActivityPanel.

class BA_CORE_API_ FitSuiteWidget : public QWidget
{
    Q_OBJECT

public:
    FitSuiteWidget(QWidget *parent = 0);
    ~FitSuiteWidget();

    void setItem(JobItem *jobItem);
    void setModelTuningWidget(ParameterTuningWidget *tuningWidget);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void fittingStarted(JobItem *jobItem);
    void fittingFinished(JobItem *jobItem);
    void fittingError(const QString &what);
    void fittingLog(const QString &text);

public slots:
    void onError(const QString &text);
    void onPlotsUpdate();
    void onProgressInfoUpdate(const FitProgressInfo &info);

    void startFitting();
    void stopFitting();

private slots:
    void onFittingStarted();
    void onFittingFinished();
    void onFitSuitePropertyChange(const QString &name);

private:
    void connectSignals();
    void updateIterationCount(const FitProgressInfo &info);
    void updateTuningWidgetParameterValues(const FitProgressInfo &info);
    void updateLog(const FitProgressInfo &info);


    QTabWidget *m_tabWidget;
    FitParameterWidget *m_fitParametersWidget;
    MinimizerSettingsWidget *m_minimizerSettingsWidget;
    FitResultsWidget *m_fitResultsWidget;
    JobItem *m_currentItem;
    RunFitManager *m_runFitManager;
    std::shared_ptr<GUIFitObserver> m_observer;
    bool m_block_progress_update;
};

#endif
