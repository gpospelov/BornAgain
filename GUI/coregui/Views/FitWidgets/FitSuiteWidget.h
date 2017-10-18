// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSuiteWidget.h
//! @brief     Defines class FitSuiteWidget
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

#include "FitProgressInfo.h"
#include "WinDllMacros.h"
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
template <class T> class OutputData;
//class FitProgressInfo;
class FitSuiteManager;
class RunFitControlWidget;
class JobMessagePanel;


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
    void setJobMessagePanel(JobMessagePanel *jobMessagePanel);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void onProgressInfoUpdate(const FitProgressInfo &info);

private slots:
    void onFittingStarted();
    void onFittingFinished();
    void onFittingLogUpdate(const QString &text);
    void onFittingError(const QString &text);

private:
    void connectSignals();
    void updateIterationCount(const FitProgressInfo &info);
    void updateTuningWidgetParameterValues(const FitProgressInfo &info);
    void updateLog(const FitProgressInfo &info);

    RunFitControlWidget *m_controlWidget;
    QTabWidget *m_tabWidget;
    FitParameterWidget *m_fitParametersWidget;
    MinimizerSettingsWidget *m_minimizerSettingsWidget;
    FitResultsWidget *m_fitResultsWidget;
    JobItem *m_currentItem;
    JobMessagePanel* m_jobMessagePanel;
    FitSuiteManager* m_fitSuiteManager;
    bool m_block_progress_update;
};

#endif // FITSUITEWIDGET_H
