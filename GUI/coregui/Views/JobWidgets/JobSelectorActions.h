// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorActions.h
//! @brief     Declares class JobSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBSELECTORACTIONS_H
#define JOBSELECTORACTIONS_H

#include "WinDllMacros.h"
#include <QModelIndex>
#include <QObject>

class QAction;
class JobModel;
class QItemSelectionModel;
class QModelIndex;

//! The JobSelectorActions class contains actions to run/remove jobs. Actions are used by the
//! toolbar and JobSelectorList's context menu.

class BA_CORE_API_ JobSelectorActions : public QObject {
    Q_OBJECT
public:
    JobSelectorActions(JobModel *jobModel, QObject *parent = 0);

    void setSelectionModel(QItemSelectionModel *selectionModel);
    void setToolBar(class StyledToolBar *toolBar);

public slots:
    void onRunJob();
    void onRemoveJob();
    void onContextMenuRequest(const QPoint &point, const QModelIndex &indexAtPoint = QModelIndex());

private:
    void initItemContextMenu(class QMenu &menu, const QModelIndex &indexAtPoint);
    void setAllActionsEnabled(bool value);
    bool canRunJob(const QModelIndex &index) const;
    bool canRemoveJob(const QModelIndex &index) const;

    QAction *m_runJobAction;
    QAction *m_removeJobAction;
    //QSignalMapper *m_signalMapper;
    QItemSelectionModel *m_selectionModel;
    JobModel *m_jobModel;
};

#endif // JOBSELECTORACTIONS_H

