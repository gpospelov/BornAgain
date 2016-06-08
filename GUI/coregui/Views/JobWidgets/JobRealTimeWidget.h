// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeWidget.h
//! @brief     Declares class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBREALTIMEWIDGET_H
#define JOBREALTIMEWIDGET_H

#include "JobPresenter.h"
#include "ItemStackPresenter.h"
#include <QMap>

class JobModel;
class JobItem;
class ParameterTuningWidget;
class JobRealTimeToolBar;

//! The JobRealTimeWidget class provides tuning of sample parameters in real time.
//! Located on the right side of JobView and is visible when realtime activity is selected.

class BA_CORE_API_ JobRealTimeWidget : public JobPresenter
{
    Q_OBJECT
public:
    JobRealTimeWidget(JobModel *jobModel, QWidget *parent = 0);

    ParameterTuningWidget *parameterTuningWidget(JobItem *jobItem);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setItem(JobItem *jobItem);
    void onResetParameters();
    void updateCurrentItem();
//    void onModelLoaded();

private:
    ParameterTuningWidget *currentParameterTuningWidget();
    bool isValidJobItem(JobItem *item);

    JobRealTimeToolBar *m_toolBar;
    ItemStackPresenter<ParameterTuningWidget> *m_stackedWidget;
};

#endif
