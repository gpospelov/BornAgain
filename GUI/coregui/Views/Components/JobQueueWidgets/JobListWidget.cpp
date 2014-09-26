#include "JobListWidget.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "JobListViewDelegate.h"
#include "styledtoolbar.h"
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

//    Manhattan::StyledBar *bar = new Manhattan::StyledBar;
    StyledToolBar *bar = new StyledToolBar;
    mainLayout->addWidget(bar);

//    QHBoxLayout *buttonsLayout = new QHBoxLayout;
//    buttonsLayout->addWidget(m_submitButton);
//    buttonsLayout->addWidget(m_runButton);
//    buttonsLayout->addWidget(m_saveButton);
//    buttonsLayout->addStretch(1);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

//    vlayout->addLayout(buttonsLayout);
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


//void JobListWidget::submit()
//{
//    m_jobQueueModel->addJob(0);
//}


void JobListWidget::runJob()
{
    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
    if(!indexList.empty()) {
        m_jobQueueModel->runJob(indexList.front());
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


//! remove job from the list
void JobListWidget::removeJob()
{
    qDebug() << "JobListWidget::removeJob() ";
    QModelIndex index = m_listView->selectionModel()->currentIndex();
    m_jobQueueModel->removeJob(index);
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

    QModelIndex item_index = m_listView->indexAt(pnt);
    if(item_index.isValid()) {
        const JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(item_index);
        if(jobItem->getStatus() != JobItem::Completed && jobItem->getStatus() != JobItem::Failed) {
            menu.addAction(m_runJobAction);
        }
    }

    menu.addAction(m_removeJobAction);

    menu.exec(m_listView->mapToGlobal(pnt));
}



