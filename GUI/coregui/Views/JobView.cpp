#include "JobView.h"
#include "TestView.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>


struct JobViewPrivate
{
    JobViewPrivate();
    QWidget *m_subWindows[JobView::NumberOfDocks];
    QDockWidget *m_dockWidgets[JobView::NumberOfDocks];
};


JobViewPrivate::JobViewPrivate()
{
    qFill(m_subWindows, m_subWindows + JobView::NumberOfDocks,
          static_cast<QWidget*>(0));
}


JobView::JobView(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_d(new JobViewPrivate)
{
    setObjectName("JobView");

    TestView *outputDataWidget = new TestView(this);
    outputDataWidget->setWindowTitle("OutputDataWidget");
    outputDataWidget->setObjectName("OutputDataWidget");

    setCentralWidget(outputDataWidget);

    initSubWindows();

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


void JobView::initSubWindows()
{
    TestView *jobListWidget = new TestView(this);
    jobListWidget->setWindowTitle("JobListWidget");
    jobListWidget->setObjectName("JobListWidget");
    m_d->m_subWindows[JobListDock] = jobListWidget;

    TestView *realTimeWidget = new TestView(this);
    realTimeWidget->setWindowTitle("RealTimeWidget");
    realTimeWidget->setObjectName("RealTimeWidget");
    m_d->m_subWindows[RealTimeDock] = realTimeWidget;
}


