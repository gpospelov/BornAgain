// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobListWidget.cpp
//! @brief     Implements class JobListWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobListWidget.h"
#include "ItemSelectorWidget.h"
#include "JobItem.h"
#include "JobListViewDelegate.h"
#include "JobModel.h"
#include <QItemSelectionModel>
#include <QListView>
#include <QVBoxLayout>


JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_listViewDelegate(new JobListViewDelegate(this))
    , m_listView(new ItemSelectorWidget(this))
    , m_jobModel(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_listView->listView()->setItemDelegate(m_listViewDelegate);
    m_listView->listView()->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

    vlayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);

    setLayout(mainLayout);

    connect(m_listView, SIGNAL(contextMenuRequest(const QPoint &, const QModelIndex &)),
            this, SIGNAL(contextMenuRequest(const QPoint &, const QModelIndex &)));

    connect(m_listView, SIGNAL(selectionChanged(SessionItem*)),
            this, SLOT(onItemSelectionChanged(SessionItem*)));

}

void JobListWidget::setModel(JobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        m_jobModel = model;
        m_listView->setModel(model);

        connect(m_listViewDelegate, SIGNAL(cancelButtonClicked(QModelIndex)),
        m_jobModel, SLOT(cancelJob(QModelIndex)), Qt::UniqueConnection);
    }
}

QItemSelectionModel *JobListWidget::selectionModel()
{
    return m_listView->selectionModel();
}

//! Returns currently selected JobItem

const JobItem *JobListWidget::currentJobItem() const
{
    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();
    if(selected.size() == 1)
        return m_jobModel->getJobItemForIndex(selected.at(0));
    return nullptr;
}


//! setup context menu for listView
//void JobListWidget::setupContextMenuActions()
//{
//    m_signalMapper = new QSignalMapper(this);
//    connect(m_signalMapper, SIGNAL(mapped(int)),
//            this, SLOT(equalizeSelectedToJob(int)));

//    m_removeJobAction = new QAction("Remove Job", this);
//    connect(m_removeJobAction, SIGNAL(triggered()), this, SLOT(removeJob()));

//    m_runJobAction = new QAction("Run Job", this);
//    connect(m_runJobAction, SIGNAL(triggered()), this, SLOT(runJob()));
//}

//! Equalize colormap plots (xmin, xmax; ymin, ymax; zmin, zmax) of all selected jobs to
//! the  plot of requested jobItem. selected_id corresponds to the certain position
//! in the list of selected items, as reported by context menu of QListView.
//void JobListWidget::equalizeSelectedToJob(int selected_id)
//{
//    QModelIndexList selectedList = m_listView->selectionModel()->selectedIndexes();

//    if(selected_id >= selectedList.size() ) return;

//    JobItem *referenceItem = m_jobModel->getJobItemForIndex(selectedList.at(selected_id));
//    Q_ASSERT(referenceItem);

//    IntensityDataItem *referenceDataItem = referenceItem->getIntensityDataItem();
//    if(!referenceDataItem) return;

//    foreach(QModelIndex index, selectedList) {
//        JobItem *jobItem = m_jobModel->getJobItemForIndex(index);
//        if(jobItem == referenceItem) continue;

//        if(IntensityDataItem *dataItem = jobItem->getIntensityDataItem()) {
//            dataItem->setLowerX(referenceDataItem->getLowerX());
//            dataItem->setUpperX(referenceDataItem->getUpperX());
//            dataItem->setLowerY(referenceDataItem->getLowerY());
//            dataItem->setUpperY(referenceDataItem->getUpperY());
//            dataItem->setLowerZ(referenceDataItem->getLowerZ());
//            dataItem->setUpperZ(referenceDataItem->getUpperZ());
//        }
//    }
//}

//void JobListWidget::makeJobItemSelected(const QModelIndex &index)
//{
//    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();

//    // already selected
//    if(selected.size() == 1 && selected.at(0) == index)
//        return;

//    m_listView->selectionModel()->clearSelection();
//    m_listView->selectionModel()->select(index, QItemSelectionModel::Select);
//}

void JobListWidget::makeJobItemSelected(JobItem *jobItem)
{
    Q_ASSERT(jobItem);
    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();

    // Already selected, but we still will emit the signal to notify widgets.
    // To handle the case, when the job was selected before it completed (and some stack widgets
    // were refusing to show the content for non-complete job).
    if(selected.size() == 1 && selected.at(0) == jobItem->index()) {
        emit selectionChanged(jobItem);
        return;
    }

    m_listView->selectionModel()->clearSelection();
    m_listView->selectionModel()->select(jobItem->index(), QItemSelectionModel::Select);
}

//! Recieves SeesionItem from ItemSelectorWidget and emits it further as JobItem.
//! Null item means the absence of selection.

void JobListWidget::onItemSelectionChanged(SessionItem *item)
{
    JobItem *jobItem(0);
    if(item) {
        jobItem = dynamic_cast<JobItem *>(item);
        Q_ASSERT(jobItem);
    }
    emit selectionChanged(jobItem);
}

//void JobListWidget::showContextMenu(const QPoint &pnt)
//{
//    QMenu menu;
//    menu.addAction(m_runJobAction);
//    menu.addAction(m_removeJobAction);

//    QModelIndex item_index = m_listView->indexAt(pnt);

//    if(item_index.isValid()) {
//        if(jobItemCanBeRun(item_index)) {
//            m_runJobAction->setDisabled(false);
//        } else {
//            m_runJobAction->setDisabled(true);
//        }
//        if(jobItemCanBeRemoved(item_index)) {
//            m_removeJobAction->setDisabled(false);
//        } else {
//            m_removeJobAction->setDisabled(true);
//        }
//    } else {
//        m_runJobAction->setDisabled(true);
//        m_removeJobAction->setDisabled(true);
//    }

//    // menu for equalization of selected plots
//    menu.addSeparator();

//    QMenu menu_equalize("Equalize selected plots");
//    menu_equalize.setToolTip("All plots from the list of selected jobs will be equalized to this one.");

//    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();
//    if(selected.size() <= 1)
//        menu_equalize.setDisabled(true);

//    for(int i =0; i<selected.count(); ++i) {
//        JobItem *jobItem = m_jobModel->getJobItemForIndex(selected.at(i));
//        QAction *action = new QAction(QString("to ").append(jobItem->itemName()), this);
//        connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
//        m_signalMapper->setMapping(action, i);
//        menu_equalize.addAction(action);
//    }

//    menu.addMenu(&menu_equalize);
//    menu.exec(m_listView->mapToGlobal(pnt));
//}
