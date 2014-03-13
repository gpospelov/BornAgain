#include "JobSelectorWidget.h"
#include "JobQueueModel.h"
#include "JobPropertiesWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QSplitter>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


JobListWidget::JobListWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_listView(new QListView(this))
    , m_button1(new QPushButton("Submit"))
    , m_button2(new QPushButton("Run"))
    , m_saveButton(new QPushButton("Save"))
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
    mainLayout->addWidget(bar);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_button1);
    buttonsLayout->addWidget(m_button2);
    buttonsLayout->addWidget(m_saveButton);
    buttonsLayout->addStretch(1);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

    vlayout->addLayout(buttonsLayout);
    vlayout->addWidget(m_listView);


    //mainLayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);


    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));

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



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

JobSelectorWidget::JobSelectorWidget(JobQueueModel *model, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobListWidget(new JobListWidget(this))
    , m_jobProperties(new JobPropertiesWidget(this))
{
    setModel(model);

    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Selector"));
    setObjectName(QLatin1String("Job Selector"));
//    setStyleSheet("background-color:white;");

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
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
        m_jobListWidget->setModel(m_jobQueueModel);
        m_jobProperties->setModel(m_jobQueueModel);
    }
}

