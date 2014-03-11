#include "JobQueueView.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QTableView>
#include <QPushButton>
#include <QDebug>



class QStandardItemModel;


JobQueueView::JobQueueView(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(new JobQueueModel())
    , m_button1(new QPushButton("Run"))
    , m_button2(new QPushButton("Submit"))
    , m_saveButton(new QPushButton("Save"))
    , m_listView(new QListView(this))
{
//    m_jobQueueModel->addJob(new JobQueueItem("job1"));
//    m_jobQueueModel->addJob(new JobQueueItem("job2"));
//    m_jobQueueModel->addJob(new JobQueueItem("job3"));

    //
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_button1);
    buttonsLayout->addWidget(m_button2);
    buttonsLayout->addWidget(m_saveButton);
    buttonsLayout->addStretch(1);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_listView, 0, 0);
//    gridLayout->addWidget(m_listView2, 1, 0);
//    gridLayout->addWidget(m_treeView, 0, 1);
//    gridLayout->addWidget(m_tableView, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);

    m_listView->setDragEnabled(true);
    m_listView->setAcceptDrops(true);
    m_listView->setModel(m_jobQueueModel);
    m_listView->setDefaultDropAction(Qt::MoveAction);


    //m_jobQueueModel->save("tmp.xml");
    m_jobQueueModel->load("model.xml");

    //m_jobQueueModel->save("tmp2.xml");

    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));


}


void JobQueueView::save()
{
    qDebug() << "JobQueueView::save() -> ";
    m_jobQueueModel->save("tmp2.xml");

}


