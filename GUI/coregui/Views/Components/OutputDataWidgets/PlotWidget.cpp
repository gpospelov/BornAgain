#include "PlotWidget.h"


PlotWidget::PlotWidget(QWidget *parent)
    : QWidget(parent)
    , m_splitter(new QSplitter())
    , m_centralPlot(new CentralPlot())
    , m_verticalPlot(new HistogramPlot(HistogramPlot::Vertical))
    , m_horizontalPlot(new HistogramPlot(HistogramPlot::Horizontal))
    , m_toolBar(new OutputDataToolBar(this))
{

    connect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));


    histogramSize = 150;
    int horizontalHeight = histogramSize-15;

    m_verticalPlot->setMaximumWidth(histogramSize);
    m_horizontalPlot->setMaximumHeight(horizontalHeight);


    m_propertyWidget = new PropertyWidget(this);

    QWidget * emptyWidget = new QWidget();
    emptyWidget->setMaximumSize(histogramSize, histogramSize);



    m_splitterTop = new QSplitter();
    m_splitterTop->addWidget(m_verticalPlot);
    m_splitterTop->addWidget(m_centralPlot);


    m_splitterBottom= new QSplitter();
    m_splitterBottom->addWidget(emptyWidget);
    m_splitterBottom->addWidget(m_horizontalPlot);

    m_splitterLeft = new QSplitter();
    m_splitterLeft->setOrientation(Qt::Vertical);
    m_splitterLeft->addWidget(m_splitterTop);
    m_splitterLeft->addWidget(m_splitterBottom);

    m_splitterRight = new QSplitter();
    m_splitterRight->addWidget(m_propertyWidget);

    m_splitter->addWidget(m_splitterLeft);
    m_splitter->addWidget(m_splitterRight);


    statusLabel = new QLabel(this);
    statusLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    statusLabel->setMaximumHeight(35);


    connectSignals();

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_toolBar);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(statusLabel);
    this->setLayout(vlayout);
    //setCentralWidget(widget);

}


void PlotWidget::connectSignals()
{
    m_toolBar = new OutputDataToolBar(this);
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertypanel()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));

}

void PlotWidget::togglePropertypanel()
{
    qDebug() << "togglePropertypanel called";

    QList<int> h_sizes_org = this->m_splitter->sizes();


    int width = 0;

    if(h_sizes_org.at(1) > 0)
    {
        width = 0;
    }
    else
    {
        width = m_propertyWidget->getWidth();
    }

    QList<int> h_sizes;
    h_sizes.append(this->m_splitter->height() - width);
    h_sizes.append(width);
    this->m_splitter->setSizes(h_sizes);

}

void PlotWidget::savePlot()
{

}

void PlotWidget::drawPlot(OutputDataItem *m_outputDataItem)
{
    const OutputData<double> *data = m_outputDataItem->getOutputData();
    if(data)
    {
        qDebug() << "PlotWidget::drawPlot called";
        m_centralPlot->drawPlot(data);
        m_verticalPlot->setupMap(m_centralPlot);
        m_horizontalPlot->setupMap(m_centralPlot);
        m_propertyWidget->setupPropertyWidget(m_centralPlot, m_outputDataItem);
    }
}


void PlotWidget::toggleHistogram()
{

    QList<int> h_sizes_org = this->m_splitter->sizes();
    QList<int> v_sizes_org = this->m_splitterTop->sizes();

    int width = 0;

    if(h_sizes_org.at(1) > 0 || v_sizes_org.at(0) > 0)
    {
        width = 0;
    }
    else
    {
        width = this->histogramSize;
    }

    QList<int> h_sizes;
    h_sizes.append(this->m_splitter->height() - width);
    h_sizes.append(width);
    this->m_splitter->setSizes(h_sizes);

    QList<int> v_sizes;
    v_sizes.append(width);
    v_sizes.append(this->m_splitterTop->width()-width);
    this->m_splitterTop->setSizes(v_sizes);

}


void PlotWidget::mousePress(QMouseEvent *event)
{
    qDebug() << event->pos().x() << " : " << event->pos().y();

    if(event->button() == Qt::RightButton)
    {
        QAction *reserAct = new QAction(tr("&Reset View"), this);
        connect(reserAct, SIGNAL(triggered()), this, SLOT(resetTriggered()));

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);

        menu->addAction(reserAct);
        menu->exec(mouseEvent->globalPos());
    }

}

void PlotWidget::resetTriggered()
{
    m_centralPlot->resetView();
}


void PlotWidget::mouseMove(QMouseEvent * event)
{
    QPoint point = event->pos();
    QVector<QVector<double> > histogramData = this->m_centralPlot->getHistogramData(point, true);

    statusLabel->setText(this->m_centralPlot->getStatusString());

    if(histogramData.size()>0)
    {
        this->m_horizontalPlot->generateHistogram(histogramData.at(0), histogramData.at(1));
        this->m_verticalPlot->generateHistogram(histogramData.at(2), histogramData.at(3));
    }
}
