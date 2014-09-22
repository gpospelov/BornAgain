#ifndef JOBLISTWIDGET_H
#define JOBLISTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QModelIndex>

class JobQueueModel;
class JobListViewDelegate;
class QListView;
class QPushButton;
class QAction;


//! Widget to select JobQueueItem in a list
//! Top left corner of JobQueueView
//! Part of JobSelectorWidget
class BA_CORE_API_ JobListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobListWidget(QWidget *parent = 0);

    void setModel(JobQueueModel *model);
//    QSize sizeHint() const { return QSize(128, 128); }

public slots:
    void makeJobItemSelected(const QModelIndex &index);

protected slots:
    void showContextMenu(const QPoint &pnt);

private slots:
    void save();
    void runJob();
    void removeJob();

private:
    void setupContextMenuActions();

    JobQueueModel *m_jobQueueModel;
    JobListViewDelegate *m_listViewDelegate;
    QListView *m_listView;
    QAction *m_runJobAction;
    QAction *m_removeJobAction;
//    QPushButton *m_submitButton;
//    QPushButton *m_runButton;
//    QPushButton *m_saveButton;
};



#endif
