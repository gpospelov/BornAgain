#ifndef OUTPUTDATAWIDGET_H
#define OUTPUTDATAWIDGET_H

#include <QWidget>
#include "OutputData.h"

class QCustomPlot;
class JobQueueModel;
class JobItem;

class OutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit OutputDataWidget(JobQueueModel *model, QWidget *parent = 0);
    explicit OutputDataWidget(QWidget *parent = 0);

//    void setModel(JobQueueModel *model);

    void setCurrentItem(JobItem *item);

public slots:
    void onModifiedItem(JobItem *item);
//    void itemClicked(JobItem *item);
//    void dataChanged(const QModelIndex &, const QModelIndex &);

private:
    void Draw(const OutputData<double> *data);

    JobQueueModel *m_jobQueueModel;
    QCustomPlot *m_customPlot;
    JobItem *m_currentJobItem;
    const OutputData<double > *m_data;
};




#endif
