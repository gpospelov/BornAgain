#include "JobSelectorWidget.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "JobPropertiesWidget.h"
#include "JobListWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include "progressbar.h"
#include <QSplitter>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>



JobSelectorWidget::JobSelectorWidget(JobQueueModel *model, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobListWidget(new JobListWidget(this))
    , m_jobProperties(new JobPropertiesWidget(this))
{
    setModel(model);

    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Selector"));
    setObjectName(QLatin1String("Job Selector"));
//    setStyleSheet("background-color:white;");

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_jobListWidget);
    m_splitter->addWidget(m_jobProperties);
    m_splitter->setChildrenCollapsible(true);

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

