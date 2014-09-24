#include "JobView.h"
#include "TestView.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "JobQueueModel.h"
#include "mainwindow.h"
#include "progressbar.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>


struct JobViewPrivate
{
    JobViewPrivate(JobQueueModel *jobQueueModel);
    QWidget *m_subWindows[JobView::NumberOfDocks];
    QDockWidget *m_dockWidgets[JobView::NumberOfDocks];
    JobQueueModel *m_jobQueueModel;
    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputDataWidget;
    Manhattan::ProgressBar *m_progressBar; //!< general progress bar
};


JobViewPrivate::JobViewPrivate(JobQueueModel *jobQueueModel)
    : m_jobQueueModel(jobQueueModel)
    , m_jobSelector(0)
    , m_jobOutputDataWidget(0)
    , m_progressBar(0)
{
    qFill(m_subWindows, m_subWindows + JobView::NumberOfDocks,
          static_cast<QWidget*>(0));
    qFill(m_dockWidgets, m_dockWidgets + JobView::NumberOfDocks,
          static_cast<QDockWidget*>(0));
}


JobView::JobView(JobQueueModel *jobQueueModel, QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_d(new JobViewPrivate(jobQueueModel))
{
    setObjectName("JobView");

    initWindows();

    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    for (int i = 0; i < NumberOfDocks; i++) {
        QWidget *subWindow = m_d->m_subWindows[i];
        m_d->m_dockWidgets[i] = addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames =
                subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0 ; i< frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);

    }

    resetToDefaultLayout();

    connectSignals();

    onJobViewActivityRequest();
}


JobView::~JobView()
{
    delete m_d;
}


void JobView::setProgressBar(Manhattan::ProgressBar *progressBar)
{
    if(m_d->m_progressBar != progressBar) {
        m_d->m_progressBar = progressBar;
        m_d->m_progressBar->hide();
        connect(m_d->m_progressBar, SIGNAL(clicked()), m_d->m_jobQueueModel->getJobQueueData(), SLOT(onCancelAllJobs()));
    }
}


void JobView::updateGlobalProgressBar(int progress)
{
    Q_ASSERT(m_d->m_progressBar);
    if(progress<0 || progress >= 100) {
        m_d->m_progressBar->setFinished(true);
        m_d->m_progressBar->hide();
    } else {
        m_d->m_progressBar->show();
        m_d->m_progressBar->setFinished(false);
        m_d->m_progressBar->setValue(progress);
    }
}


void JobView::onFocusRequest(JobItem *item)
{
    m_d->m_jobSelector->makeJobItemSelected(item);
    emit focusRequest(MainWindow::JobTab);
}


void JobView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    foreach (QDockWidget *dockWidget, dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }

    addDockWidget(Qt::LeftDockWidgetArea,
                  m_d->m_dockWidgets[JobListDock]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_d->m_dockWidgets[RealTimeDock]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);
}


void JobView::onJobViewActivityRequest()
{
    m_d->m_dockWidgets[JobListDock]->show();
    m_d->m_dockWidgets[RealTimeDock]->hide();
}


void JobView::onRealTimeActivityRequest()
{
    m_d->m_dockWidgets[JobListDock]->hide();
    m_d->m_dockWidgets[RealTimeDock]->show();
}


void JobView::initWindows()
{
    // central widget
    m_d->m_jobOutputDataWidget = new JobOutputDataWidget(m_d->m_jobQueueModel, this);
    setCentralWidget(m_d->m_jobOutputDataWidget);

    m_d->m_jobSelector = new JobSelectorWidget(m_d->m_jobQueueModel, this);
    m_d->m_subWindows[JobListDock] = m_d->m_jobSelector;

    TestView *realTimeWidget = new TestView(this);
    realTimeWidget->setWindowTitle("RealTimeWidget");
    realTimeWidget->setObjectName("RealTimeWidget");
    m_d->m_subWindows[RealTimeDock] = realTimeWidget;
}


void JobView::connectSignals()
{
    connect(m_d->m_jobQueueModel->getJobQueueData(), SIGNAL(globalProgress(int)), this, SLOT(updateGlobalProgressBar(int)));
    connect(m_d->m_jobQueueModel->getJobQueueData(), SIGNAL(focusRequest(JobItem*)), this, SLOT(onFocusRequest(JobItem*)));
    connect(m_d->m_jobOutputDataWidget, SIGNAL(jobViewActivityRequest()), this, SLOT(onJobViewActivityRequest()));
    connect(m_d->m_jobOutputDataWidget, SIGNAL(realTimeActivityRequest()), this, SLOT(onRealTimeActivityRequest()));
}


