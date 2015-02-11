// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobQueueWidgets/JobListWidget.h
//! @brief     Defines class JobListWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBLISTWIDGET_H
#define JOBLISTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QModelIndex>

//class JobQueueModel;
class JobModel;
class JobListViewDelegate;
class QListView;
class QPushButton;
class QAction;
class JobListToolBar;
class QItemSelectionModel;


//! Widget to select JobQueueItem in a list
//! Top left corner of JobQueueView
//! Part of JobSelectorWidget
class BA_CORE_API_ JobListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobListWidget(QWidget *parent = 0);

    void setModel(JobModel *model);

    QSize sizeHint() const { return QSize(64, 768); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

    QItemSelectionModel *getSelectionModel();

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
    bool jobItemCanBeRun(const QModelIndex &index);

    JobModel *m_jobModel;
    JobListViewDelegate *m_listViewDelegate;
    QListView *m_listView;
    QAction *m_runJobAction;
    QAction *m_removeJobAction;
    JobListToolBar *m_toolBar;
};



#endif
