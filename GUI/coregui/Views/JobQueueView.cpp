#include "JobQueueView.h"
#include "JobQueueModel.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QTableView>
#include <QPushButton>



class QStandardItemModel;


JobQueueView::JobQueueView(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(new JobQueueModel())
    , m_button1(new QPushButton("Run"))
    , m_button2(new QPushButton("Submit"))
    , m_listView1(new QListView())
    , m_listView2(new QListView())
    , m_treeView(new QTreeView())
    , m_tableView(new QTableView())
{

//    QStandardItem *rootNode = m_jobQueueModel->invisibleRootItem();
//    QStandardItem *job0 = new QStandardItem("job0");
//    QStandardItem *job1 = new QStandardItem("job1");
//    QStandardItem *job2 = new QStandardItem("job2");

//    rootNode->appendRow(job0);
//    job0->appendRow(new QStandardItem("hash"));
//    job0->appendRow(new QStandardItem("name"));
//    job0->appendRow(new QStandardItem("status"));
//    job0->appendRow(new QStandardItem("time1"));
//    job0->appendRow(new QStandardItem("time2"));
//    job0->appendRow(new QStandardItem("comments"));

//    QStandardItem *data0 = new QStandardItem("data0");
//    data0->appendRow(new QStandardItem("xmin"));
//    data0->appendRow(new QStandardItem("xmax"));
//    data0->appendRow(new QStandardItem("logz"));
//    job0->appendRow(data0);

//    rootNode->appendRow(job1);
//    job1->appendRow(new QStandardItem("hash"));
//    job1->appendRow(new QStandardItem("name"));
//    job1->appendRow(new QStandardItem("status"));
//    job1->appendRow(new QStandardItem("time1"));
//    job1->appendRow(new QStandardItem("time2"));
//    job1->appendRow(new QStandardItem("comments"));

//    QStandardItem *data1 = new QStandardItem("data1");
//    data1->appendRow(new QStandardItem("xmin"));
//    data1->appendRow(new QStandardItem("xmax"));
//    data1->appendRow(new QStandardItem("logz"));
//    job1->appendRow(data1);

//    rootNode->appendRow(job2);
//    job2->appendRow(new QStandardItem("hash"));
//    job2->appendRow(new QStandardItem("name"));
//    job2->appendRow(new QStandardItem("status"));
//    job2->appendRow(new QStandardItem("time1"));
//    job2->appendRow(new QStandardItem("time2"));
//    job2->appendRow(new QStandardItem("comments"));

//    QStandardItem *data2 = new QStandardItem("data2");
//    data2->appendRow(new QStandardItem("xmin"));
//    data2->appendRow(new QStandardItem("xmax"));
//    data2->appendRow(new QStandardItem("logz"));
//    job2->appendRow(data2);



//    JobQueueItem *root = m_jobQueueModel->getRootItem();

//    JobQueueItem *job0 = new JobQueueItem("job0");
//    job0->addChildItem(new JobQueueItem("data0"));
//    JobQueueItem *job1 = new JobQueueItem("job1");
//    job1->addChildItem(new JobQueueItem("data1"));
//    JobQueueItem *job2 = new JobQueueItem("job2");
//    job2->addChildItem(new JobQueueItem("data2"));
//    root->addChildItem(job0);
//    root->addChildItem(job1);
//    root->addChildItem(job2);

    JobQueueItem *job0 = new JobQueueItem("job0");
    JobQueueItem *job1 = new JobQueueItem("job1");
    JobQueueItem *job2 = new JobQueueItem("job2");
    m_jobQueueModel->insertNewItem(job0);
    m_jobQueueModel->insertNewItem(job1);
    m_jobQueueModel->insertNewItem(job2);
//    m_jobQueueModel->insertNewItem(new JobQueueItem("data0"), m_jobQueueModel->indexOfItem(job0));
//    m_jobQueueModel->insertNewItem(new JobQueueItem("data1"), m_jobQueueModel->indexOfItem(job1));
//    m_jobQueueModel->insertNewItem(new JobQueueItem("data2"), m_jobQueueModel->indexOfItem(job2));



    //
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_button1);
    buttonsLayout->addWidget(m_button2);
    buttonsLayout->addStretch(1);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_listView1, 0, 0);
    gridLayout->addWidget(m_listView2, 1, 0);
    gridLayout->addWidget(m_treeView, 0, 1);
    gridLayout->addWidget(m_tableView, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);

    m_treeView->setModel(m_jobQueueModel);
    m_tableView->setModel(m_jobQueueModel);
    m_listView1->setModel(m_jobQueueModel);
    m_listView2->setModel(m_jobQueueModel);


//    viewport()->setAcceptDrops(true);
//    setAcceptDrops(true);
//    setDragEnabled(true);
//    setDropIndicatorShown(true);
//    setDragDropMode(QListView::DragDrop);

    m_listView1->setDragEnabled(true);
    m_listView1->setAcceptDrops(true);
    m_listView1->setDragDropMode(QAbstractItemView::InternalMove);
    m_listView1->setDropIndicatorShown(true);
    m_listView1->setMovement(QListView::Snap);

    m_treeView->setDragEnabled(true);
    m_treeView->setAcceptDrops(true);
    m_treeView->setDragDropMode(QAbstractItemView::InternalMove);
    m_treeView->setDropIndicatorShown(true);
//    m_treeView->setMovement(QListView::Snap);

//    tree_view->setAllColumnsShowFocus(true);
//    tree_view->setWindowTitle(QString("Object Tree View"));
//    tree_view->setObjectName(QString("ObjectTree"));
//    tree_view->setContextMenuPolicy(Qt::CustomContextMenu);
//    tree_view->setDragDropMode(QAbstractItemView::InternalMove);


}



