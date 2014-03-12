#include "JobSelectorWidget.h"
#include "JobQueueModel.h"
#include "JobPropertiesWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QSplitter>
#include <QListView>
#include <QVBoxLayout>



JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
{
    setMinimumSize(128, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_listView->setDragEnabled(true);
    m_listView->setAcceptDrops(true);
    m_listView->setDefaultDropAction(Qt::MoveAction);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    Manhattan::StyledBar *bar = new Manhattan::StyledBar;
//    QHBoxLayout *layout = new QHBoxLayout(bar);
//    layout->setMargin(0);
//    layout->setSpacing(0);

    mainLayout->addWidget(bar);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);
    vlayout->addWidget(m_listView);


    //mainLayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);


    setLayout(mainLayout);

}

void JobListWidget::setModel(JobQueueModel *model)
{
    m_listView->setModel(model);
}



JobSelectorWidget::JobSelectorWidget(JobQueueModel *model, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(model)
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobListWidget(new JobListWidget(this))
    , m_jobProperties(new JobPropertiesWidget(this))
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Selector"));
    setObjectName(QLatin1String("Job Selector"));
//    setStyleSheet("background-color:white;");

    m_jobListWidget->setModel(model);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_jobListWidget);
    m_splitter->addWidget(m_jobProperties);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);

}


void JobSelectorWidget::setModel(JobQueueModel *model)
{
    m_jobQueueModel = model;
    m_jobListWidget->setModel(m_jobQueueModel);
}

