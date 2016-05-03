// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitControlWidget.h
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

#include "WinDllMacros.h"
#include <QWidget>

class JobItem;
class QPushButton;
class QSlider;

//! The RunFitControlWidget contains elements to start/stop fitting and to provide minimal
//! diagnostic. Part of FitActivityPanel.

class BA_CORE_API_ RunFitControlWidget : public QWidget
{
    Q_OBJECT
public:
    RunFitControlWidget(QWidget *parent = 0);

signals:
    void startFitting();
    void stopFitting();

public slots:
    void onFittingStarted();
    void onFittingFinished();
    void setItem(JobItem *item);

private:
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QSlider *m_intervalSlider;
};

#endif
