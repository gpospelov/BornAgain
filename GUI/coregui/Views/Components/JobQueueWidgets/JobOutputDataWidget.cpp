#include "JobOutputDataWidget.h"
#include "JobQueueModel.h"
#include "OutputDataWidget.h"
#include "styledbar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QDebug>
#include "GUIHelpers.h"

JobOutputDataWidget::JobOutputDataWidget(JobQueueModel *model,QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_stack(new QStackedWidget(this))
//    , m_outputDataWidget(new OutputDataWidget(model, this))
{
    setModel(model);

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job OutputData"));
    setObjectName(QLatin1String("Job OutputData"));
//    setStyleSheet("background-color:blue;");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    //Manhattan::StyledBar *bar = new Manhattan::StyledBar;
    //mainLayout->addWidget(bar);
//    mainLayout->addWidget(m_outputDataWidget);
    mainLayout->addWidget(m_stack);


    //m_plotPages->addWidget(new OutputDataWidget(m_jobQueueModel, this));
    //m_plotPages->addWidget(new OutputDataWidget(m_jobQueueModel, this));

    m_stack->setMinimumSize(600, 600);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    setLayout(mainLayout);


}


void JobOutputDataWidget::setModel(JobQueueModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;

        connect(m_jobQueueModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( itemClicked(JobItem *) )
            );

        connect(m_jobQueueModel, SIGNAL(dataChanged(QModelIndex, QModelIndex))
                , this, SLOT(dataChanged(QModelIndex, QModelIndex)));

        connect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));

    }
}



void JobOutputDataWidget::itemClicked(JobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";

    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget ) {
        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new OutputDataWidget();
        widget->setCurrentItem(item);
        m_stack->addWidget(widget);
        m_jobItemToPlotWidget[item] = widget;

    }

    m_stack->setCurrentWidget(widget);
}


void JobOutputDataWidget::dataChanged(const QModelIndex &, const QModelIndex &)
{
    qDebug() << "JobOutputDataWidget::dataChanged()";
}


void JobOutputDataWidget::onJobItemDelete(JobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget ) {
        throw GUIHelpers::Error("JobOutputDataWidget::onJobItemDelete -> Can't find widget");
    }
    m_stack->removeWidget(widget);
    delete widget;
}

