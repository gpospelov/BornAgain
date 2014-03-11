#ifndef JOBQUEUEVIEW_H
#define JOBQUEUEVIEW_H

#include <QWidget>

class QListView;
class QTreeView;
class QTableView;
class QPushButton;
class JobQueueModel;

class JobQueueView : public QWidget
{
    Q_OBJECT

public:
    JobQueueView(QWidget *parent = 0);
    virtual ~JobQueueView() {}

public slots:

private slots:
    void save();

private:

    JobQueueModel *m_jobQueueModel;
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_saveButton;

    QListView *m_listView;
};

#endif // JOBQUEUEVIEW_H
