#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include <QWidget>

class QSplitter;
class QListView;
class JobPropertiesWidget;
class JobQueueModel;



//! holds list of jobs and some buttons
class JobListWidget : public QWidget
{
public:
    explicit JobListWidget(QWidget *parent = 0);

    void setModel(JobQueueModel *model);

private:
    QListView *m_listView;

};


//! holds JobListWidget and JobPropertiesWidget
class JobSelectorWidget : public QWidget
{
public:
    explicit JobSelectorWidget(JobQueueModel *model, QWidget *parent = 0);

    void setModel(JobQueueModel *model);

private:
    JobQueueModel *m_jobQueueModel;
    QSplitter *m_splitter;
    JobListWidget *m_jobListWidget;
    JobPropertiesWidget *m_jobProperties;
};




#endif
