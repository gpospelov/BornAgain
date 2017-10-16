// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorActions.cpp
//! @brief     Implements class JobSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobSelectorActions.h"
#include "JobItem.h"
#include "JobModel.h"
#include "StyledToolBar.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QMenu>

JobSelectorActions::JobSelectorActions(JobModel* jobModel, QObject* parent)
    : QObject(parent)
    , m_runJobAction(nullptr)
    , m_removeJobAction(nullptr)
    , m_selectionModel(nullptr)
    , m_jobModel(jobModel)
{
    m_runJobAction = new QAction(QStringLiteral("Run"), this);
    m_runJobAction->setIcon(QIcon(":/images/toolbar16light_run.svg"));
    m_runJobAction->setToolTip("Run currently selected job");
    connect(m_runJobAction, &QAction::triggered, this, &JobSelectorActions::onRunJob);

    m_removeJobAction = new QAction(QStringLiteral("Remove"), this);
    m_removeJobAction->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeJobAction->setToolTip("Remove currently selected job.");
    connect(m_removeJobAction, &QAction::triggered, this, &JobSelectorActions::onRemoveJob);
}

void JobSelectorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

void JobSelectorActions::onRunJob()
{
    QModelIndexList indexList = m_selectionModel->selectedIndexes();
    foreach (QModelIndex index, indexList) {
        if (canRunJob(index))
            m_jobModel->runJob(index);
    }
}

void JobSelectorActions::onRemoveJob()
{
    Q_ASSERT(m_selectionModel);
    QModelIndexList indexList = m_selectionModel->selectedIndexes();

    while (indexList.size()) {
        if (canRemoveJob(indexList.first())) {
            m_jobModel->removeJob(indexList.first());
            indexList = m_selectionModel->selectedIndexes();
        }
    }
}

//! Generates context menu at given point. If indexAtPoint is provided, the actions will be done
//! for corresponding JobItem

void JobSelectorActions::onContextMenuRequest(const QPoint& point, const QModelIndex& indexAtPoint)
{
    QMenu menu;
    initItemContextMenu(menu, indexAtPoint);
    menu.exec(point);
    setAllActionsEnabled(true);
}

void JobSelectorActions::initItemContextMenu(QMenu& menu, const QModelIndex& indexAtPoint)
{
    menu.addAction(m_runJobAction);
    menu.addAction(m_removeJobAction);

    QModelIndex targetIndex = indexAtPoint;
    if (!targetIndex.isValid()) {
        QModelIndexList indexList = m_selectionModel->selectedIndexes();
        if (indexList.size())
            targetIndex = indexList.first();
    }

    m_runJobAction->setEnabled(canRunJob(targetIndex));
    m_removeJobAction->setEnabled(canRemoveJob(targetIndex));
}

void JobSelectorActions::setAllActionsEnabled(bool value)
{
    m_runJobAction->setEnabled(value);
    m_removeJobAction->setEnabled(value);
}

bool JobSelectorActions::canRunJob(const QModelIndex& index) const
{
    if (!index.isValid())
        return false;

    const JobItem* jobItem = m_jobModel->getJobItemForIndex(index);
    return jobItem->isRunning() ? false : true;
}

bool JobSelectorActions::canRemoveJob(const QModelIndex& index) const
{
    if (!index.isValid())
        return false;

    const JobItem* jobItem = m_jobModel->getJobItemForIndex(index);
    if (jobItem->isRunning())
        return false;

    return true;
}
