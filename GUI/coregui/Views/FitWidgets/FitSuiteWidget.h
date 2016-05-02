// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitSuiteWidget.h
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
#include <QWidget>
#include <memory>

class QTabWidget;
class JobModel;
class JobItem;
class FitParametersWidget;
class ModelTuningWidget;
class RunFitManager;
class GUIFitObserver;
template <class T> class OutputData;


//! The FitSuiteWidget contains all fit settings for given JobItem (fit parameters,
//! minimizer settings) and all logic to start/stop fitting. Controlled by FitActivityPanel

class BA_CORE_API_ FitSuiteWidget : public QWidget
{
    Q_OBJECT

public:
    FitSuiteWidget(JobModel *jobModel, QWidget *parent = 0);
    ~FitSuiteWidget();

    void setItem(JobItem *jobItem);
    void setModelTuningWidget(ModelTuningWidget *tuningWidget);

signals:
    void fittingStarted();
    void fittingFinished();

public slots:
    void onError(const QString &text);
    void onUpdatePlots(OutputData<double>*sim, OutputData<double>*chi2);
    void onUpdateParameters(const QStringList &parameters, QVector<double> values);

    void startFitting();
    void stopFitting();

private:
    void connectSignals();

    QTabWidget *m_tabWidget;
    FitParametersWidget *m_fitParametersWidget;
    JobModel *m_jobModel;
    JobItem *m_currentItem;
    RunFitManager *m_manager;
    std::shared_ptr<GUIFitObserver> m_observer;
};

#endif
