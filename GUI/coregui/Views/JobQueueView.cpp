#include "JobQueueView.h"
#include "JobQueueModel.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QTableView>
#include <QPushButton>



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

    QStandardItem *rootNode = m_jobQueueModel->invisibleRootItem();
    QStandardItem *job0 = new QStandardItem("job0");
    QStandardItem *job1 = new QStandardItem("job1");

    rootNode->appendRow(job0);
    job0->appendRow(new QStandardItem("hash"));
    job0->appendRow(new QStandardItem("name"));
    job0->appendRow(new QStandardItem("status"));
    job0->appendRow(new QStandardItem("time1"));
    job0->appendRow(new QStandardItem("time2"));
    job0->appendRow(new QStandardItem("comments"));

    QStandardItem *data0 = new QStandardItem("data0");
    data0->appendRow(new QStandardItem("xmin"));
    data0->appendRow(new QStandardItem("xmax"));
    data0->appendRow(new QStandardItem("logz"));
    job0->appendRow(data0);

    rootNode->appendRow(job1);
    job1->appendRow(new QStandardItem("hash"));
    job1->appendRow(new QStandardItem("name"));
    job1->appendRow(new QStandardItem("status"));
    job1->appendRow(new QStandardItem("time1"));
    job1->appendRow(new QStandardItem("time2"));
    job1->appendRow(new QStandardItem("comments"));

    QStandardItem *data1 = new QStandardItem("data1");
    data1->appendRow(new QStandardItem("xmin"));
    data1->appendRow(new QStandardItem("xmax"));
    data1->appendRow(new QStandardItem("logz"));
    job1->appendRow(data1);

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
}



