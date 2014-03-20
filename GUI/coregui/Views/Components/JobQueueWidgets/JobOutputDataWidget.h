#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include <QWidget>

class OutputDataWidget;
class JobQueueModel;

class JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(JobQueueModel *model, QWidget *parent = 0);

private:
    JobQueueModel *m_jobQueueModel;
    OutputDataWidget *m_outputDataWidget;
};


#endif
