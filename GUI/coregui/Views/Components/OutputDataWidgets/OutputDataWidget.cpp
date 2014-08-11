#include "OutputDataWidget.h"
#include "PlotWidget.h"
#include "PropertyWidget.h"
#include "OutputDataToolBar.h"
#include <QVBoxLayout>
#include <QModelIndex>
#include <QSplitter>
#include <QMouseEvent>


//OutputDataWidget::OutputDataWidget(JobQueueModel *model, QWidget *parent)
OutputDataWidget::OutputDataWidget(QWidget *parent, bool isCreateToolBar)
    : QWidget(parent)
    , m_plotWidget(0)
    , m_data(0)
{
    qDebug() << " ";
    qDebug() << "OutputDataWidget::OutputDataWidget() -> c-tor";
//    setModel(model);

    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");


    m_gradient = QCPColorGradient::gpPolar;

    m_isPropertyWidgetVisible = true;
    m_isProjectionsVisible = true;





    m_plotWidget = new PlotWidget(this);
    m_plotWidget->setObjectName(QString::fromUtf8("OutputDataWidget::customPlot"));
    //connect(m_plotWidget, SIGNAL(isProjectionsChanged(bool)),this, SLOT(projectionsChanged(bool)));

    m_splitter = new QSplitter(this);
    m_splitter->setStyleSheet("background-color:white;");
    m_splitter->addWidget(m_plotWidget);

    m_propertyWidget = new PropertyWidget(this);
    connect(m_propertyWidget, SIGNAL(projectionsChanged(bool)), this, SLOT(projectionsChanged(bool)));
    connect(m_propertyWidget, SIGNAL(gradientChanged(QCPColorGradient)), this, SLOT(gradientChanged(QCPColorGradient)));
    m_splitter->addWidget(m_propertyWidget);
    connect(m_splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(onPropertySplitterMoved(int,int)));
    m_currentPropertyWidgetWidth = m_propertyWidget->getWidth();


    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    if(isCreateToolBar)
    {
        m_toolBar = new OutputDataToolBar();
        //m_toolBar->hide();
        connectToobarSignals();
        m_mainLayout->addWidget(m_toolBar);
    }

    m_mainLayout->addWidget(m_splitter);
    setLayout(m_mainLayout);
}

/*void OutputDataWidget::connectPropertyWidgetSignals(bool isConnect)
{
    if(m_propertyWidget)
    {
        if(isConnect)
        {
            connect(m_propertyWidget, SIGNAL(projectionsChanged(bool)), this, SLOT(projectionsChanged(bool)));
            connect(m_propertyWidget, SIGNAL(gradientChanged(QCPColorGradient)), this, SLOT(gradientChanged(QCPColorGradient)));
        }
        else
        {
            disconnect(m_propertyWidget, SIGNAL(projectionsChanged(bool)), this, SLOT(projectionsChanged(bool)));
            disconnect(m_propertyWidget, SIGNAL(gradientChanged(QCPColorGradient)), this, SLOT(gradientChanged(QCPColorGradient)));
        }
    }

}*/


void OutputDataWidget::setCurrentItem(OutputDataItem *item)
{
    qDebug() << "OutputDataWidget::setCurrentItem()";

    m_plotWidget->drawPlot(item);
    m_propertyWidget->setupPropertyWidget(item, m_gradient);
    //connectPropertyWidgetSignals(isPropertyWidgetVisible);

}

void OutputDataWidget::connectToobarSignals()
{
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(resetTriggered()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));

}

void OutputDataWidget::togglePropertyPanel()
{


    QList<int> sizes_org = this->m_splitter->sizes();

    if(sizes_org.at(1) > 0)
    {
        setPropertyPanelVisible(false);
    }
    else
    {
       setPropertyPanelVisible(true);
    }

}

void OutputDataWidget::setPropertyPanelVisible(bool visible)
{
    int width = 0;
    m_isPropertyWidgetVisible = visible;
    if(visible)
    {
        width = m_propertyWidget->getWidth();
        m_propertyWidget->connectSignals();
    }
    else
    {
        width = 0;
        m_propertyWidget->disconnectSignals();
    }

    m_currentPropertyWidgetWidth = width;
    QList<int> sizes;
    sizes.append(this->m_splitter->width() - width);
    sizes.append(width);
    this->m_splitter->setSizes(sizes);



}

void OutputDataWidget::toggleProjections()
{
    qDebug() << "OutputDataWidget::toggleProjections() ";
    m_propertyWidget->toggleProjections();
}

void OutputDataWidget::resetTriggered()
{
    m_plotWidget->resetTriggered();
}

void OutputDataWidget::savePlot()
{

    m_plotWidget->savePlot();

}

void OutputDataWidget::projectionsChanged(bool projection)
{
    qDebug() << "PW Projections: " << projection;

    m_isProjectionsVisible = projection;
    m_plotWidget->projectionsChanged(projection);
}

void OutputDataWidget::gradientChanged(QCPColorGradient gradient)
{
    m_gradient = gradient;
    m_plotWidget->gradientChanged(gradient);

}

void OutputDataWidget::onPropertySplitterMoved(int pos, int index)
{
    qDebug() << "OutputDataWidget::onPropertySplitterMoved";
    QList<int> sizes_org = this->m_splitter->sizes();

    if(sizes_org.at(index) != m_currentPropertyWidgetWidth)
    {
        qDebug() << "   OutputDataWidget::onPropertySplitterMoved" << m_propertyWidget->getWidth() << "::" << sizes_org.at(index);
        if(sizes_org.at(index) == m_propertyWidget->getWidth())
        {
            m_currentPropertyWidgetWidth = sizes_org.at(1);
            m_isPropertyWidgetVisible = true;
            m_propertyWidget->connectSignals();

        }
        else
        {
            m_currentPropertyWidgetWidth = 0;
            m_isPropertyWidgetVisible = false;
            m_propertyWidget->disconnectSignals();
        }


    }


}



