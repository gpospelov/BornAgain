// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitControlWidget.h
//! @brief     Defines class RunFitControlWidget
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

#include "SessionItemWidget.h"
#include <QWidget>

class JobItem;
class QPushButton;
class QSlider;
class WarningSign;
class QLabel;
class FitSuiteItem;
class JobMessagePanel;

//! The RunFitControlWidget contains elements to start/stop fitting and to provide minimal
//! diagnostic. Part of FitSuiteWidget.

class BA_CORE_API_ RunFitControlWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    RunFitControlWidget(QWidget* parent = 0);

signals:
    void startFittingPushed();
    void stopFittingPushed();

public slots:
    void onFittingError(const QString& what);

private slots:
    void onSliderValueChanged(int value);
    void onFitSuitePropertyChange(const QString& name);

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();

private:
    int sliderUpdateInterval();
    int sliderValueToUpdateInterval(int value);
    void updateControlElements();
    JobItem* jobItem();
    FitSuiteItem* fitSuiteItem();
    bool isValidJobItem();

    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    QSlider* m_intervalSlider;
    QLabel* m_updateIntervalLabel;
    QLabel* m_iterationsCountLabel;
    WarningSign* m_warningSign;
};

#endif // RUNFITCONTROLWIDGET_H
