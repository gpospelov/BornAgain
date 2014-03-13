#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include <QWidget>

class JobQueueModel;
class JobPropertiesWidget;
class QSplitter;
class QListView;
class QPushButton;

//! Widget to select JobQueueItem in a list
//! Top left corner of JobQueueView
//! Part of JobSelectorWidget
class JobListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobListWidget(QWidget *parent = 0);

    void setModel(JobQueueModel *model);

public slots:

private slots:
    void save();

private:
    JobQueueModel *m_jobQueueModel;
    QListView *m_listView;
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_saveButton;

};


//! Widget to select JobQueueItem in a list and display its properties
//! Left side of JobQueueView
//! Contains two widgets: JobListWidget (top) and JobQueueProperties(buttom)
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
