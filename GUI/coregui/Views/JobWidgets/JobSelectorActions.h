// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobSelectorActions.h
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
#include <QObject>

class QAction;
class JobModel;
class QItemSelectionModel;
class QModelIndex;

//! The JobSelectorActions class contains actions to run/remove jobs. Actions are used by the
//! toolbar and JobSelectorTree's context menu.

class BA_CORE_API_ JobSelectorActions : public QObject {
    Q_OBJECT
public:
    JobSelectorActions(JobModel *jobModel, QObject *parent = 0);

    void setSelectionModel(QItemSelectionModel *selectionModel);
    void setToolBar(class StyledToolBar *toolBar);

public slots:
    void onRunJob();
    void onRemoveJob();

private:
    bool canRunJob(const QModelIndex &index) const;
    bool canRemoveJob(const QModelIndex &index) const;

    QAction *m_runJobAction;
    QAction *m_removeJobAction;
    QItemSelectionModel *m_selectionModel;
    JobModel *m_jobModel;
};

#endif

