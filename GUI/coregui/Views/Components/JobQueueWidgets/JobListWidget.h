#ifndef JOBLISTWIDGET_H
#define JOBLISTWIDGET_H

#include <QWidget>

class JobQueueModel;
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
//    QSize sizeHint() const { return QSize(128, 128); }

public slots:

private slots:
    void save();
    void submit();
    void run();

private:
    JobQueueModel *m_jobQueueModel;
    QListView *m_listView;
    QPushButton *m_submitButton;
    QPushButton *m_runButton;
    QPushButton *m_saveButton;

};



#endif
