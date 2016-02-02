// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RUNFITWIDGET_H
#define RUNFITWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <boost/shared_ptr.hpp>

class QSlider;
class QLabel;
class QPushButton;
class RunFitManager;
class FitSuite;
class FitProgressWidget;
class FitModel;
class SampleModel;
class InstrumentModel;
class ParameterizedItem;
class SessionModel;

class BA_CORE_API_ RunFitWidget : public QWidget
{
    Q_OBJECT

public:

    RunFitWidget(FitModel *fit, SampleModel *sample, InstrumentModel *inst, QWidget *parent = 0);

    // test only
    boost::shared_ptr<FitSuite> init_test_fitsuite();

    QString path;

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
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    ParameterizedItem *getTopItemFromSelection(SessionModel *model, const QString &itemType, const QString &selectionType);
};

#endif
