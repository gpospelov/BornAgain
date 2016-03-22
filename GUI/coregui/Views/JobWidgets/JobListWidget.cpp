// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobListWidget.cpp
//! @brief     Implements class JobListWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobListWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobListViewDelegate.h"
#include "JobListToolBar.h"
#include "IntensityDataItem.h"
#include <QPushButton>
#include <QListView>
#include <QMenu>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QSignalMapper>


JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_listViewDelegate(new JobListViewDelegate(this))
    , m_listView(new QListView(this))
    , m_runJobAction(0)
    , m_removeJobAction(0)
    , m_toolBar(new JobListToolBar)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_listView->setDragEnabled(true);
    m_listView->setAcceptDrops(true);
    m_listView->setDefaultDropAction(Qt::MoveAction);
    m_listView->setItemDelegate(m_listViewDelegate);
    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // connect context menu for tree view
    connect(m_listView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    connect(m_toolBar, SIGNAL(runJob()), this, SLOT(runJob()));
    connect(m_toolBar, SIGNAL(removeJob()), this, SLOT(removeJob()));
    mainLayout->addWidget(m_toolBar);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

    vlayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);

    setLayout(mainLayout);

    setupContextMenuActions();
}

void JobListWidget::setModel(JobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        m_jobModel = model;
        m_listView->setModel(model);

        connect(m_listView->selectionModel(),
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
            m_jobModel,
            SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
            );

        connect(m_listViewDelegate, SIGNAL(cancelButtonClicked(QModelIndex)),
        m_jobModel, SLOT(cancelJob(QModelIndex)));

    }
}

QItemSelectionModel *JobListWidget::getSelectionModel()
{
    return m_listView->selectionModel();
}

void JobListWidget::save()
{
    Q_ASSERT(m_jobModel);
    m_jobModel->save("tmp.xml");
}

void JobListWidget::runJob()
{
    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, indexList) {
        if(jobItemCanBeRun(index))
            m_jobModel->runJob(index);
    }
}

//! setup context menu for listView
void JobListWidget::setupContextMenuActions()
{
    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, SIGNAL(mapped(int)),
            this, SLOT(equalizeSelectedToJob(int)));

    m_removeJobAction = new QAction(tr("Remove Job"), this);
    connect(m_removeJobAction, SIGNAL(triggered()), this, SLOT(removeJob()));

    m_runJobAction = new QAction(tr("Run Job"), this);
    connect(m_runJobAction, SIGNAL(triggered()), this, SLOT(runJob()));
}

bool JobListWidget::jobItemCanBeRun(const QModelIndex &index)
{
    if(!index.isValid()) return false;

    const JobItem *jobItem = m_jobModel->getJobItemForIndex(index);
//    if(jobItem->isCompleted() || jobItem->isFailed() || jobItem->isRunning()) return false;
    if(/*jobItem->isCompleted()  || */jobItem->isRunning()) return false;

    return true;
}

bool JobListWidget::jobItemCanBeRemoved(const QModelIndex &index)
{
    if(!index.isValid()) return false;

    const JobItem *jobItem = m_jobModel->getJobItemForIndex(index);
    if(jobItem->isRunning()) return false;

    return true;
}

//! remove job from the list
void JobListWidget::removeJob()
{
    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();

    while(indexList.size()) {
        if(jobItemCanBeRemoved(indexList.first())) {
            m_jobModel->removeJob(indexList.first());
            indexList = m_listView->selectionModel()->selectedIndexes();
        }
    }
}

//! Equalize colormap plots (xmin, xmax; ymin, ymax; zmin, zmax) of all selected jobs to
//! the  plot of requested jobItem. selected_id corresponds to the certain position
//! in the list of selected items, as reported by context menu of QListView.
void JobListWidget::equalizeSelectedToJob(int selected_id)
{
    QModelIndexList selectedList = m_listView->selectionModel()->selectedIndexes();

    if(selected_id >= selectedList.size() ) return;

    JobItem *referenceItem = m_jobModel->getJobItemForIndex(selectedList.at(selected_id));
    Q_ASSERT(referenceItem);

    IntensityDataItem *referenceDataItem = referenceItem->getIntensityDataItem();
    if(!referenceDataItem) return;

    foreach(QModelIndex index, selectedList) {
        JobItem *jobItem = m_jobModel->getJobItemForIndex(index);
        if(jobItem == referenceItem) continue;

        if(IntensityDataItem *dataItem = jobItem->getIntensityDataItem()) {
            dataItem->setLowerX(referenceDataItem->getLowerX());
            dataItem->setUpperX(referenceDataItem->getUpperX());
            dataItem->setLowerY(referenceDataItem->getLowerY());
            dataItem->setUpperY(referenceDataItem->getUpperY());
            dataItem->setLowerZ(referenceDataItem->getLowerZ());
            dataItem->setUpperZ(referenceDataItem->getUpperZ());
        }
    }
}

void JobListWidget::makeJobItemSelected(const QModelIndex &index)
{
    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();

    // already selected
    if(selected.size() == 1 && selected.at(0) == index)
        return;

    m_listView->selectionModel()->clearSelection();
    m_listView->selectionModel()->select(index, QItemSelectionModel::Select);
}

void JobListWidget::showContextMenu(const QPoint &pnt)
{
    QMenu menu;
    menu.addAction(m_runJobAction);
    menu.addAction(m_removeJobAction);

    QModelIndex item_index = m_listView->indexAt(pnt);

    if(item_index.isValid()) {
        if(jobItemCanBeRun(item_index)) {
            m_runJobAction->setDisabled(false);
        } else {
            m_runJobAction->setDisabled(true);
        }
        if(jobItemCanBeRemoved(item_index)) {
            m_removeJobAction->setDisabled(false);
        } else {
            m_removeJobAction->setDisabled(true);
        }
    } else {
        m_runJobAction->setDisabled(true);
        m_removeJobAction->setDisabled(true);
    }

    // menu for equalization of selected plots
    menu.addSeparator();

    QMenu menu_equalize("Equalize selected plots");
    menu_equalize.setToolTip("All plots from the list of selected jobs will be equalized to this one.");

    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();
    if(selected.size() <= 1)
        menu_equalize.setDisabled(true);

    for(int i =0; i<selected.count(); ++i) {
        JobItem *jobItem = m_jobModel->getJobItemForIndex(selected.at(i));
        QAction *action = new QAction(QString("to ").append(jobItem->itemName()), this);
        connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(action, i);
        menu_equalize.addAction(action);
    }

    menu.addMenu(&menu_equalize);
    menu.exec(m_listView->mapToGlobal(pnt));
}
