#include "JobOutputDataWidget.h"
#include "JobQueueModel.h"
#include "OutputDataWidget.h"
#include "JobOutputDataToolBar.h"
#include "JobView.h"
#include "styledbar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QDebug>
#include "GUIHelpers.h"


JobOutputDataWidget::JobOutputDataWidget(JobQueueModel *jobQueueModel, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobOutputDataToolBar())
{
    setJobQueueModel(jobQueueModel);

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job OutputData"));
    setObjectName(QLatin1String("Job OutputData"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stack);
    m_stack->setMinimumSize(600, 600);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setLayout(mainLayout);

    connectSignals();

}


void JobOutputDataWidget::setJobQueueModel(JobQueueModel *jobQueueModel)
{
    Q_ASSERT(jobQueueModel);
    if(jobQueueModel != m_jobQueueModel) {
        m_jobQueueModel = jobQueueModel;

        connect(m_jobQueueModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( itemClicked(JobItem *) )
            );

        connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));
    }
}


void JobOutputDataWidget::itemClicked(JobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";



    m_currentJobItem = item;

    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget && (item->getStatus() == JobItem::Completed || item->getStatus() == JobItem::Canceled)) {

        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new OutputDataWidget(this, false, false, false);
        widget->setCurrentItem(item->getOutputDataItem());
        m_stack->addWidget(widget);
        m_jobItemToPlotWidget[item] = widget;

    }
    else
    {
        if( m_stack->currentWidget())
        {
            m_stack->currentWidget()->hide();
        }
    }


    if(widget)
    {
        qDebug() << "JobOutputDataWidget::itemClicked() -> setCurrentWidget";

        if(widget->isHidden())
        {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
    }
}


void JobOutputDataWidget::onJobItemFinished(const QString &identifier)
{
    qDebug() << "JobOutputDataWidget::onJobItemFinished()";
    JobItem *jobItem = m_jobQueueModel->getJobQueueData()->getJobItem(identifier);

    if(jobItem == m_currentJobItem)
    {
        if((jobItem->getStatus() == JobItem::Completed || jobItem->getStatus() == JobItem::Canceled) && jobItem->getOutputDataItem())
        {
            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
            itemClicked(jobItem);
        }
    }
}


void JobOutputDataWidget::togglePropertyPanel()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->togglePropertyPanel();
}


void JobOutputDataWidget::toggleProjections()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->toggleProjections();
}


void JobOutputDataWidget::resetTriggered()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->resetTriggered();
}


void JobOutputDataWidget::savePlot()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->savePlot();
}


void JobOutputDataWidget::onActivityChanged(int activity)
{
    m_toolBar->onActivityChanged(activity);
    if(activity == JobView::RealTimeActivity) {
        OutputDataWidget *widget = getCurrentOutputDataWidget();
        if(widget) {
            widget->setPropertyPanelVisible(false);
            //widget->setProjectionsVisible(false);
        }
    }
}


void JobOutputDataWidget::connectSignals()
{
    connect(m_toolBar, SIGNAL(jobViewActivityRequest(int)), this, SIGNAL(jobViewActivityRequest(int)));
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(resetTriggered()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));
}


OutputDataWidget *JobOutputDataWidget::getCurrentOutputDataWidget()
{
    OutputDataWidget *result = dynamic_cast<OutputDataWidget *>(m_stack->currentWidget());
    if(result && result->isHidden()) result = 0;
    return result;
}


void JobOutputDataWidget::onJobItemDelete(JobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        //throw GUIHelpers::Error("JobOutputDataWidget::onJobItemDelete -> Can't find widget");
        return;
    }

    QMap<JobItem *, OutputDataWidget *>::iterator it = m_jobItemToPlotWidget.begin();
    while(it!=m_jobItemToPlotWidget.end()) {
        if(it.value() == widget) {
            it = m_jobItemToPlotWidget.erase(it);
        } else {
            ++it;
        }
    }

    m_stack->removeWidget(widget);
    delete widget;
}

