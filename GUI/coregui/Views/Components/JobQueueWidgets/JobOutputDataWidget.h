#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include <QWidget>
#include <QMap>

class OutputDataWidget;
class JobQueueModel;
class QStackedWidget;
class QModelIndex;
class JobItem;

class JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(JobQueueModel *model, QWidget *parent = 0);

    void setModel(JobQueueModel *model);

public slots:
    void itemClicked(JobItem *item);
    void dataChanged(const QModelIndex &, const QModelIndex &);
    void onJobItemDelete(JobItem *item);

private:
    JobQueueModel *m_jobQueueModel;

    //OutputDataWidget *m_outputDataWidget;

    QStackedWidget *m_stack;
    QMap<JobItem *, OutputDataWidget *> m_jobItemToPlotWidget;
};


#endif
