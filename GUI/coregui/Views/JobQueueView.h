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

private:

    JobQueueModel *m_jobQueueModel;
    QPushButton *m_button1;
    QPushButton *m_button2;
    QListView *m_listView1;
    QListView *m_listView2;
    QTreeView *m_treeView;
    QTableView *m_tableView;
};

#endif // JOBQUEUEVIEW_H
