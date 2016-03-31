// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitTools.h
//! @brief     Defines class FitTools
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITTOOLS_H
#define FITTOOLS_H

#include <QWidget>
#include "OutputData.h"
#include <memory>

class JobItem;
class JobModel;
class ModelMapper;
class QHBoxLayout;
class QItemSelectionModel;
class QPushButton;
class RunFitManager;
class GUIFitObserver;
class QSlider;
class RealDataWindow;

class FitTools : public QWidget
{
    Q_OBJECT

public:
    FitTools(JobModel *jobModel, QWidget *parent = 0);

    void setCurrentItem(JobItem *item, QItemSelectionModel *selection);

public slots:
    void onStartClick();
    void onFittingStarted();
    void onFittingFinished();
    void onStopClicked();
    void onError(const QString &text);
    void onUpdatePlots(OutputData<double>*sim, OutputData<double>*chi2);
    void onUpdateParameters(const QStringList &parameters, QVector<double> values);
    void onRealData();

private:

    JobModel *m_jobModel;
    JobItem *m_currentJobItem;
    QItemSelectionModel *m_selectionModel;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QSlider *m_intervalSlider;
    QPushButton *m_realData;
    RunFitManager *m_manager;
    std::shared_ptr<GUIFitObserver> m_observer;
    RealDataWindow *m_realDataWindow;
};

#endif
