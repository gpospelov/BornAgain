#include "JobListWidget.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "JobListViewDelegate.h"
#include "progressbar.h"
#include "styledbar.h"
#include <QPushButton>
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>


JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_listView(new QListView(this))
    , m_submitButton(new QPushButton("Submit"))
    , m_runButton(new QPushButton("Run"))
    , m_saveButton(new QPushButton("Save"))
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_listView->setDragEnabled(true);
    m_listView->setAcceptDrops(true);
    m_listView->setDefaultDropAction(Qt::MoveAction);
    m_listView->setItemDelegate(new JobListViewDelegate(this));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    Manhattan::StyledBar *bar = new Manhattan::StyledBar;
    mainLayout->addWidget(bar);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_submitButton);
    buttonsLayout->addWidget(m_runButton);
    buttonsLayout->addWidget(m_saveButton);
    buttonsLayout->addStretch(1);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

    vlayout->addLayout(buttonsLayout);
    vlayout->addWidget(m_listView);

    Manhattan::ProgressBar *progressBar = new Manhattan::ProgressBar(this);
    progressBar->setRange(0,100);
    progressBar->setValue(50);
    vlayout->addWidget(progressBar);


    //mainLayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);


    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(m_submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(m_runButton, SIGNAL(clicked()), this, SLOT(run()));

    setLayout(mainLayout);

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
    }
}


void JobListWidget::save()
{
    Q_ASSERT(m_jobQueueModel);
    qDebug() << "JobListWidget::save() -> ";
    m_jobQueueModel->save("tmp2.xml");

}


void JobListWidget::submit()
{
    Q_ASSERT(m_jobQueueModel);
    qDebug() << "JobListWidget::submit() -> ";
    static int i=4;
    m_jobQueueModel->addJob(new JobQueueItem(QString("job")+QString::number(i++)));

}


void JobListWidget::run()
{
    Q_ASSERT(m_jobQueueModel);
    qDebug() << "JobListWidget::run()";

    QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
    qDebug() <<indexList;

    if(!indexList.empty()) {
        JobQueueItem *job = m_jobQueueModel->getJobQueueItemForIndex(indexList.front());
        qDebug() << "JobListWidget::run()" << job->getName();
//        job->run();
        m_jobQueueModel->runInThread(job);
    }
}
