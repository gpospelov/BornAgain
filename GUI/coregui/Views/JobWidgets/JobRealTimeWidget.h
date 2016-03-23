// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeWidget.h
//! @brief     Defines class JobRealTimeWidget
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

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class JobModel;
class JobItem;
class QStackedWidget;
class ModelTuningWidget;
class JobRealTimeToolBar;

//! The JobRealTimeWidget provides tuning of sample parameters and run of the simulation in real time.
//! Located on the right side of JobView and is visible when realtime activity is selected.
class BA_CORE_API_ JobRealTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobRealTimeWidget(JobModel *jobModel, QWidget *parent = 0);

    void setJobModel(JobModel *jobModel);

public slots:
    void setItem(JobItem *item);
    void onJobItemDelete(JobItem *item);
    void onJobItemFinished(const QString &identifier);
    void onResetParameters();
    void updateCurrentItem();

private:
    ModelTuningWidget *getCurrentModelTuningWidget();
    bool isValidJobItem(JobItem *item);

    JobModel *m_jobModel;
    JobItem *m_currentJobItem;
    QStackedWidget *m_stack;
    QMap<JobItem *, ModelTuningWidget *> m_jobItemToTuningWidget;
    JobRealTimeToolBar *m_toolBar;
};

#endif
