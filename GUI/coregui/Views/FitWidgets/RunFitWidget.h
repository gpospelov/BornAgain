// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Declares class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RUNFITWIDGET_H
#define RUNFITWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class QSlider;
class QLabel;
class QPushButton;
class RunFitManager;
class FitSuite;
class FitProgressWidget;
class FitModel;
class SampleModel;
class InstrumentModel;
class SessionItem;
class SessionModel;

class BA_CORE_API_ RunFitWidget : public QWidget
{
    Q_OBJECT

public:
    RunFitWidget(FitModel *fitModel, QWidget *parent = 0);

    // test only
    std::shared_ptr<FitSuite> init_test_fitsuite();

public slots:
    void onIntervalChanged(int value);
    void onStartClicked();
    void onStopClicked();
    void onFittingStarted();
    void onFittingFinished();

private:
    QPushButton *m_start_button;
    QPushButton *m_stop_button;
    QLabel *m_interval_label;
    QSlider *m_interval_slider;
    RunFitManager *m_runfitmanager;
    FitProgressWidget *m_fitprogress;
    FitModel *m_fitModel;

    SessionItem *getTopItemFromSelection(SessionModel *model, const QString &itemType, const QString &selectionType);
};

#endif
