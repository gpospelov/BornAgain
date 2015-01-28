// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobListWidget.cpp
//! @brief     Implements class JobListWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobListWidget.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "JobListViewDelegate.h"
#include "JobListToolBar.h"
#include <QPushButton>
#include <QListView>
#include <QMenu>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>


JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_listViewDelegate(new JobListViewDelegate(this))
    , m_listView(new QListView(this))
    , m_runJobAction(0)
    , m_removeJobAction(0)
    , m_toolBar(new JobListToolBar)
//    , m_submitButton(new QPushButton("Submit"))
//    , m_runButton(new QPushButton("Run"))
//    , m_saveButton(new QPushButton("Save"))
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_listView->setDragEnabled(true);
    m_listView->setAcceptDrops(true);
    m_listView->setDefaultDropAction(Qt::MoveAction);
    m_listView->setItemDelegate(m_listViewDelegate);
    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);

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

//    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));
//    connect(m_submitButton, SIGNAL(clicked()), this, SLOT(submit()));
//    connect(m_runButton, SIGNAL(clicked()), this, SLOT(run()));

    setupContextMenuActions();
}


void JobListWidget::setModel(JobQueueModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
        m_listView->setModel(model);

        connect(m_listView->selectionModel(),
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
            m_jobQueueModel,
            SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
            );

        connect(m_listViewDelegate, SIGNAL(cancelButtonClicked(QModelIndex)),
        m_jobQueueModel, SLOT(cancelJob(QModelIndex)));

    }
}


void JobListWidget::save()
{
    Q_ASSERT(m_jobQueueModel);
    qDebug() << "JobListWidget::save() -> ";
    m_jobQueueModel->save("tmp2.xml");

}

void JobListWidget::runJob()
{
    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, indexList) {
        if(jobItemCanBeRun(index))
            m_jobQueueModel->runJob(index);
    }
}


//! setup context menu for listView
void JobListWidget::setupContextMenuActions()
{
    m_removeJobAction = new QAction(tr("Remove Job"), this);
    connect(m_removeJobAction, SIGNAL(triggered()), this, SLOT(removeJob()));

    m_runJobAction = new QAction(tr("Run Job"), this);
    connect(m_runJobAction, SIGNAL(triggered()), this, SLOT(runJob()));
}


bool JobListWidget::jobItemCanBeRun(const QModelIndex &index)
{
    if(!index.isValid()) return false;

    const JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(index);
    if(jobItem->getStatus() == JobItem::COMPLETED || jobItem->getStatus() == JobItem::FAILED) return false;

    return true;
}


//! remove job from the list
void JobListWidget::removeJob()
{
    qDebug() << "JobListWidget::removeJob() ";
    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, indexList) {
        m_jobQueueModel->removeJob(index);
    }
}


void JobListWidget::makeJobItemSelected(const QModelIndex &index)
{
    m_listView->selectionModel()->clearSelection();
    m_listView->selectionModel()->select(index, QItemSelectionModel::Select);
}


void JobListWidget::showContextMenu(const QPoint &pnt)
{
    qDebug() << "JobListWidget::showContextMenu()";

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
        m_removeJobAction->setDisabled(false);
    } else {
        m_runJobAction->setDisabled(true);
        m_removeJobAction->setDisabled(true);
    }

    menu.exec(m_listView->mapToGlobal(pnt));
}



