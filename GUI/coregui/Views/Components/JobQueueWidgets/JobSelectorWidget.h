#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include <QWidget>

class JobQueueModel;
class JobPropertiesWidget;
class QSplitter;
class QPushButton;
class JobListWidget;


//! Widget to select JobQueueItem in a list and display its properties
//! Left side of JobQueueView
//! Contains two widgets: JobListWidget (top) and JobQueueProperties(buttom)
class JobSelectorWidget : public QWidget
{
public:
    explicit JobSelectorWidget(JobQueueModel *model, QWidget *parent = 0);

    void setModel(JobQueueModel *model);

    QSize sizeHint() const { return QSize(128, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

private:
    JobQueueModel *m_jobQueueModel;
    QSplitter *m_splitter;
    JobListWidget *m_jobListWidget;
    JobPropertiesWidget *m_jobProperties;

};




#endif
