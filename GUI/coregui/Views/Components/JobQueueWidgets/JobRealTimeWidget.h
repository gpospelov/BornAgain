#ifndef JOBREALTIMEWIDGET_H
#define JOBREALTIMEWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class JobQueueModel;
class QStackedWidget;
class QModelIndex;
class JobItem;
class ModelTuningWidget;
class StyledToolBar;

//! The JobRealTimeWidget provides tuning of sample parameters and run of the simulation in real time.
//! Located on the right side of JobView and is visible when realtime activity is selected.
class BA_CORE_API_ JobRealTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobRealTimeWidget(JobQueueModel *jobQueueModel, QWidget *parent = 0);

    void setJobQueueModel(JobQueueModel *jobQueueModel);

public slots:
    void itemClicked(JobItem *item);
    void onJobItemDelete(JobItem *item);
    void onJobItemFinished(const QString &identifier);

private:
    JobQueueModel *m_jobQueueModel;
    JobItem *m_currentJobItem;
    QStackedWidget *m_stack;
    QMap<JobItem *, ModelTuningWidget *> m_jobItemToTuningWidget;
    StyledToolBar *m_toolBar;
};


#endif
