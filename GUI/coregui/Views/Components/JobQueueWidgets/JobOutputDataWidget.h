#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class OutputDataWidget;
class JobQueueModel;
class QStackedWidget;
class QModelIndex;
class JobItem;

class BA_CORE_API_ JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(JobQueueModel *model, QWidget *parent = 0);

    void setModel(JobQueueModel *model);

public slots:
    void itemClicked(JobItem *item);
    void dataChanged(const QModelIndex &, const QModelIndex &);
    void onJobItemDelete(JobItem *item);
    void onJobItemFinished(const QString &identifier);

private:
    JobQueueModel *m_jobQueueModel;
    JobItem *m_currentJobItem;


    QStackedWidget *m_stack;
    QMap<JobItem *, OutputDataWidget *> m_jobItemToPlotWidget;

};


#endif
