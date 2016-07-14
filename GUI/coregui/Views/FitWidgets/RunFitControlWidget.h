// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitControlWidget.h
//! @brief     Declares class RunFitControlWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RUNFITCONTROLWIDGET_H
#define RUNFITCONTROLWIDGET_H

#include <QWidget>
#include "WinDllMacros.h"

class JobItem;
class QPushButton;
class QSlider;
class WarningSignWidget;
class QLabel;
class FitSuiteItem;
class JobMessagePanel;

//! The RunFitControlWidget contains elements to start/stop fitting and to provide minimal
//! diagnostic. Part of FitActivityPanel.

class BA_CORE_API_ RunFitControlWidget : public QWidget
{
    Q_OBJECT
public:
    RunFitControlWidget(QWidget *parent = 0);

    void setJobMessagePanel(JobMessagePanel *jobMessagePanel);

signals:
    void startFittingPushed();
    void stopFittingPushed();

public slots:
    void onFittingStarted(JobItem *jobItem);
    void onFittingFinished(JobItem *jobItem);
    void onFittingError(const QString &what);
    void onFittingLog(const QString &text);
    void setItem(JobItem *item);

private slots:
    void onSliderValueChanged(int value);
    void onFitSuitePropertyChange(const QString &name);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QPoint getPositionForWarningSign();
    void clearWarningSign();
    int sliderUpdateInterval();
    int sliderValueToUpdateInterval(int value);
    FitSuiteItem *fitSuiteItem();
    bool isValidJobItem(JobItem *jobItem);

    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QSlider *m_intervalSlider;
    QLabel *m_updateIntervalLabel;
    QLabel *m_iterationsCountLabel;
    JobItem *m_currentItem;
    WarningSignWidget *m_warningSign;
    JobMessagePanel *m_jobMessagePanel;
};

#endif // RUNFITCONTROLWIDGET_H
