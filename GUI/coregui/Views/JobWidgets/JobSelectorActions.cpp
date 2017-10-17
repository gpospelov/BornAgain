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
#include "IntensityDataItem.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QSignalMapper>
#include <QMenu>
#include <memory>

JobSelectorActions::JobSelectorActions(JobModel* jobModel, QObject* parent)
    : QObject(parent)
    , m_runJobAction(nullptr)
    , m_removeJobAction(nullptr)
    , m_signalMapper(new QSignalMapper(this))
    , m_selectionModel(nullptr)
    , m_jobModel(jobModel)
{
    m_runJobAction = new QAction(QStringLiteral("Run"), this);
    m_runJobAction->setIcon(QIcon(":/images/toolbar16dark_run.svg"));
    m_runJobAction->setToolTip("Run currently selected job");
    connect(m_runJobAction, &QAction::triggered, this, &JobSelectorActions::onRunJob);

    m_removeJobAction = new QAction(QStringLiteral("Remove"), this);
    m_removeJobAction->setIcon(QIcon(":/images/toolbar16dark_recycle.svg"));
    m_removeJobAction->setToolTip("Remove currently selected job.");
    connect(m_removeJobAction, &QAction::triggered, this, &JobSelectorActions::onRemoveJob);

    connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(equalizeSelectedToJob(int)));

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

//! Puts all IntensityDataItem axes range to the selected job

void JobSelectorActions::equalizeSelectedToJob(int selected_id)
{
    QModelIndexList selectedList = m_selectionModel->selectedIndexes();

    if (selected_id >= selectedList.size())
        return;

    JobItem* referenceItem = m_jobModel->getJobItemForIndex(selectedList.at(selected_id));
    Q_ASSERT(referenceItem);

    IntensityDataItem* referenceDataItem = referenceItem->intensityDataItem();
    if (!referenceDataItem)
        return;

    foreach (QModelIndex index, selectedList) {
        JobItem* jobItem = m_jobModel->getJobItemForIndex(index);
        if (jobItem == referenceItem)
            continue;

        if (IntensityDataItem* dataItem = jobItem->intensityDataItem()) {
            dataItem->setLowerX(referenceDataItem->getLowerX());
            dataItem->setUpperX(referenceDataItem->getUpperX());
            dataItem->setLowerY(referenceDataItem->getLowerY());
            dataItem->setUpperY(referenceDataItem->getUpperY());
            dataItem->setLowerZ(referenceDataItem->getLowerZ());
            dataItem->setUpperZ(referenceDataItem->getUpperZ());
        }
    }
}

void JobSelectorActions::initItemContextMenu(QMenu& menu, const QModelIndex& indexAtPoint)
{
    menu.setToolTipsVisible(true);

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

    setupEqualizeMenu(menu);
}

void JobSelectorActions::setupEqualizeMenu(QMenu& menu)
{
    menu.addSeparator();

    QMenu* equalize_menu = menu.addMenu("Equalize selected plots");
    equalize_menu->setToolTipsVisible(true);
    equalize_menu->setToolTip(
        "All plots from the list of selected jobs will be equalized to the one.");
    QModelIndexList selected = m_selectionModel->selectedIndexes();

    if (selected.size() <= 1) {
        equalize_menu->setDisabled(true);
        return;
    }

    std::sort(selected.begin(), selected.end(),
              [](const QModelIndex& a, const QModelIndex& b) { return a.row() < b.row(); });

    for (int i = 0; i < selected.count(); ++i) {
        JobItem* jobItem = m_jobModel->getJobItemForIndex(selected.at(i));
        QAction* action = equalize_menu->addAction(QString("to ").append(jobItem->itemName()));
        connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(action, i);
    }
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
