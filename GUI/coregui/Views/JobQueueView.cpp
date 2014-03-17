#include "JobQueueView.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "minisplitter.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QSplitter>


JobQueueView::JobQueueView(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(new JobQueueModel())
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobSelector(new JobSelectorWidget(m_jobQueueModel, this))
    , m_jobOutputData(new JobOutputDataWidget(this))
{
    setObjectName("JobQueueView");

    m_jobQueueModel->addJob(0);
    m_jobQueueModel->addJob(0);
    m_jobQueueModel->addJob(0);

    m_splitter->addWidget(m_jobSelector);
    m_splitter->addWidget(m_jobOutputData);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);

}


void JobQueueView::setProgressBar(Manhattan::ProgressBar *progressBar)
{
    m_progressBar = progressBar;
}


