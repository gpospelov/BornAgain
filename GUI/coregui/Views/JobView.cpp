#include "JobView.h"
#include "TestView.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>


struct JobViewPrivate
{
    JobViewPrivate(JobQueueModel *jobQueueModel);
    QWidget *m_subWindows[JobView::NumberOfDocks];
    QDockWidget *m_dockWidgets[JobView::NumberOfDocks];
    JobQueueModel *m_jobQueueModel;
    JobOutputDataWidget *m_jobOutputDataWidget;
};


JobViewPrivate::JobViewPrivate(JobQueueModel *jobQueueModel)
    : m_jobQueueModel(jobQueueModel)
    , m_jobOutputDataWidget(0)
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
}


JobView::~JobView()
{
    delete m_d;
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

    m_d->m_subWindows[JobListDock] = new JobSelectorWidget(m_d->m_jobQueueModel, this);

    TestView *realTimeWidget = new TestView(this);
    realTimeWidget->setWindowTitle("RealTimeWidget");
    realTimeWidget->setObjectName("RealTimeWidget");
    m_d->m_subWindows[RealTimeDock] = realTimeWidget;
}


void JobView::connectSignals()
{
    connect(m_d->m_jobOutputDataWidget, SIGNAL(jobViewActivityRequest()), this, SLOT(onJobViewActivityRequest()));
    connect(m_d->m_jobOutputDataWidget, SIGNAL(realTimeActivityRequest()), this, SLOT(onRealTimeActivityRequest()));
}


