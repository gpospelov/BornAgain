// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobListWidget.h
//! @brief     Defines class JobListWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBLISTWIDGET_H
#define JOBLISTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QModelIndex>

class JobModel;
class JobListViewDelegate;
class QListView;
class QPushButton;
class QAction;
class JobListToolBar;
class QItemSelectionModel;
class QSignalMapper;
class JobItem;

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
    void equalizeSelectedToJob(int selected_id);

private:
    void setupContextMenuActions();
    bool jobItemCanBeRun(const QModelIndex &index);
    bool jobItemCanBeRemoved(const QModelIndex &index);

    JobModel *m_jobModel;
    JobListViewDelegate *m_listViewDelegate;
    QListView *m_listView;
    QAction *m_runJobAction;
    QAction *m_removeJobAction;
    JobListToolBar *m_toolBar;
    QSignalMapper *m_signalMapper;
};



#endif
