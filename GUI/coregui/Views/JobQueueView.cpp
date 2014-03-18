#include "JobQueueView.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "minisplitter.h"
#include "progressbar.h"
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

    connect(m_jobQueueModel->getJobQueueData(), SIGNAL(globalProgress(int)), this, SLOT(updateGlobalProgressBar(int)));
}


void JobQueueView::setProgressBar(Manhattan::ProgressBar *progressBar)
{
    if(m_progressBar != progressBar) {
        m_progressBar = progressBar;
        m_progressBar->hide();
        connect(m_progressBar, SIGNAL(clicked()), m_jobQueueModel->getJobQueueData(), SLOT(onCancelAllJobs()));
    }
}


void JobQueueView::updateGlobalProgressBar(int progress)
{
    if(progress<0 || progress >= 100) {
        //m_progressBar->hide();
        m_progressBar->setFinished(true);
        m_progressBar->hide();
    } else {
        m_progressBar->show();
        m_progressBar->setFinished(false);
        m_progressBar->setValue(progress);
    }
}


