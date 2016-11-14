// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobListWidget.h
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
#include <QModelIndexList>
#include <QWidget>

class JobModel;
class JobListViewDelegate;
class QItemSelectionModel;
class ItemSelectorWidget;
class QModelIndex;
class JobItem;
class SessionItem;

//! The JobListWidget class contains list view to select job items.

class BA_CORE_API_ JobListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobListWidget(QWidget *parent = 0);

    void setModel(JobModel *model);

//    QSize sizeHint() const { return QSize(64, 768); }
//    QSize minimumSizeHint() const { return QSize(64, 64); }

    QItemSelectionModel *selectionModel();

    const JobItem *currentJobItem() const;

signals:
    void contextMenuRequest(const QPoint &point, const QModelIndex &index);
    void selectionChanged(JobItem *);

public slots:
    void makeJobItemSelected(JobItem *jobItem);

private slots:
    void onItemSelectionChanged(SessionItem *item);

private:
    JobListViewDelegate *m_listViewDelegate;
    ItemSelectorWidget *m_listView;
    JobModel *m_jobModel;
};

#endif // JOBLISTWIDGET_H
