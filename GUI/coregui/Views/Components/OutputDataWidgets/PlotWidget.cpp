#include "PlotWidget.h"
#include "minisplitter.h"
#include <QVBoxLayout>


PlotWidget::PlotWidget(bool isCreateToolbar, QWidget *parent)
    : QWidget(parent)
    //, m_splitter(new Manhattan::MiniSplitter(this))
    , m_splitter(new QSplitter(this))
    , m_centralPlot(new CentralPlot())
    , m_verticalPlot(new HistogramPlot(HistogramPlot::Vertical))
    , m_horizontalPlot(new HistogramPlot(HistogramPlot::Horizontal))
    //, m_toolBar(new OutputDataToolBar(this))
    , m_outputDataItem(0)
    , m_block_plot_update(true)
{
    m_gradient = QCPColorGradient::gpPolar;

    isProjectionsVisible = true;
    isPropertyWidgetVisible = true;
    histogramSize = 150;
    //int horizontalHeight = histogramSize-15;



    m_propertyWidget = new PropertyWidget(this);
    connect(m_propertyWidget, SIGNAL(projectionsChanged(bool)), this, SLOT(projectionsChanged(bool)));
    connect(m_propertyWidget, SIGNAL(gradientChanged(QCPColorGradient)), this, SLOT(gradientChanged(QCPColorGradient)));


    QWidget * emptyWidget = new QWidget();
    //emptyWidget->setMaximumSize(histogramSize, histogramSize);
    //emptyWidget->setStyleSheet("background-color:white;");



    m_splitterTop = new QSplitter(this);
    m_splitterTop->addWidget(m_verticalPlot);
    m_splitterTop->addWidget(m_centralPlot);
    m_splitterTop->setStyleSheet("background-color:white;");

    m_splitterBottom= new QSplitter(this);
    m_splitterBottom->addWidget(emptyWidget);
    m_splitterBottom->addWidget(m_horizontalPlot);
    m_splitterBottom->setStyleSheet("background-color:white;");
    m_splitterBottom->setHandleWidth(0);

    m_splitterLeft = new QSplitter(this);
    m_splitterLeft->setOrientation(Qt::Vertical);
    m_splitterLeft->addWidget(m_splitterTop);
    m_splitterLeft->addWidget(m_splitterBottom);
    m_splitterLeft->setStyleSheet("background-color:white;");

    m_splitterRight = new QSplitter(this);
    m_splitterRight->addWidget(m_propertyWidget);
    //m_splitterRight->setStyleSheet("background-color:white;");


    m_statusLabel = new QLabel(this);
    //m_statusLabel->setFrameStyle(QFrame::Panel );
    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    //m_statusLabel->setMaximumHeight(35);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);

    QWidget *leftPanel = new QWidget(this);
    QVBoxLayout * vl = new QVBoxLayout(this);
    vl->setMargin(0);
    vl->setSpacing(0);
    vl->addWidget(m_splitterLeft);
    vl->addWidget(m_statusLabel);
    leftPanel->setLayout(vl);


    //m_splitter->addWidget(m_splitterLeft);
    m_splitter->addWidget(leftPanel);
    m_splitter->addWidget(m_splitterRight);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    if(isCreateToolbar)
    {
        m_toolBar = new OutputDataToolBar();
        connectToobarSignals();
        vlayout->addWidget(m_toolBar);
    }

    vlayout->addWidget(m_splitter);
    //vlayout->addWidget(m_statusLabel);
    this->setLayout(vlayout);
    //setCentralWidget(widget);




    QList<int> h1_sizes;
    h1_sizes.append(histogramSize);
    h1_sizes.append(600);
    this->m_splitterBottom->setSizes(h1_sizes);

    QList<int> h_sizes;
    h_sizes.append(585);
    h_sizes.append(histogramSize);
    this->m_splitterLeft->setSizes(h_sizes);

    QList<int> v_sizes;
    v_sizes.append(histogramSize);
    v_sizes.append(600);
    this->m_splitterTop->setSizes(v_sizes);

}


void PlotWidget::connectToobarSignals()
{
    //m_toolBar = new OutputDataToolBar(this);
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(resetTriggered()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));

}



void PlotWidget::savePlot()
{

    QString filters("*.png;;*.jpg;;*.pdf");
    QString defaultFilter("*.png");
    QString defaultName = qApp->applicationDirPath().append("/untitled");

    /* Static method approach */
    QString fileName =QFileDialog::getSaveFileName(0, "Save Plot", defaultName,
        filters, &defaultFilter);

    QString extension =  defaultFilter.mid(1);

    if (!fileName.isEmpty() && !defaultFilter.isEmpty())
    {
        if(fileName.endsWith(tr(".pdf"), Qt::CaseInsensitive))
        {
            m_centralPlot->savePdf(fileName);
        }
        else if(fileName.endsWith(tr(".jpg"), Qt::CaseInsensitive))
        {
            m_centralPlot->saveJpg(fileName);
        }
        else if(fileName.endsWith(tr(".png"), Qt::CaseInsensitive))
        {
            m_centralPlot->savePng(fileName);
        }
        else if(defaultFilter == "*.pdf")
        {
            m_centralPlot->savePdf(fileName+extension);
        }
        else if(defaultFilter == "*.jpg")
        {
            m_centralPlot->saveJpg(fileName+extension);
        }
        else
        {
            m_centralPlot->savePng(fileName+extension);
        }
    }
}


void PlotWidget::drawPlot(OutputDataItem *outputDataItem)
{
    if(m_outputDataItem == outputDataItem) {
        qDebug() << "PlotWidget::drawPlot() -> Same outputDataItem !!!";
        //updatePlot();
        return;
    }

    disconnect();
    m_outputDataItem = outputDataItem;


    if(outputDataItem)
    {
        m_block_plot_update = true;
        qDebug() << "PlotWidget::drawPlot called";
//        disconnect(m_centralPlot, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onZaxisRangeChanged(QCPRange)));
//        disconnect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
 //       disconnect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
        m_centralPlot->drawPlot(outputDataItem, m_gradient);
        m_verticalPlot->setupMap(m_centralPlot);
        m_horizontalPlot->setupMap(m_centralPlot);
        m_propertyWidget->setupPropertyWidget(outputDataItem, m_gradient);
        connect(m_centralPlot, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onZaxisRangeChanged(QCPRange)));
        connect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
        connect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
        connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(updatePlot()));
        connect(m_centralPlot, SIGNAL(xaxisRangeChanged(QCPRange)), this, SLOT(onXaxisRangeChanged(QCPRange)));
        connect(m_centralPlot, SIGNAL(yaxisRangeChanged(QCPRange)), this, SLOT(onYaxisRangeChanged(QCPRange)));
        m_block_plot_update = false;
    }
}


void PlotWidget::updatePlot()
{
    qDebug() << "PlotWidget::updatePlot()";
    if(m_block_plot_update) return;

    Q_ASSERT(m_outputDataItem);
    Q_ASSERT(m_centralPlot);
    Q_ASSERT(m_verticalPlot);
    Q_ASSERT(m_horizontalPlot);
    m_centralPlot->setInterpolate(m_outputDataItem->isInterpolated());
    m_centralPlot->setZmin(m_outputDataItem->getZaxisMin());
    m_centralPlot->setZmax(m_outputDataItem->getZaxisMax());
    m_centralPlot->setLogz(m_outputDataItem->isLogz());
    m_verticalPlot->setLogz(m_outputDataItem->isLogz());
    m_horizontalPlot->setLogz(m_outputDataItem->isLogz());
    m_centralPlot->setXaxisTitle(m_outputDataItem->getXaxisTitle());
    m_centralPlot->setYaxisTitle(m_outputDataItem->getYaxisTitle());

}



void PlotWidget::mousePress(QMouseEvent *event)
{
    if(m_block_plot_update) return;

    qDebug() << event->pos().x() << " : " << event->pos().y();

    if(event->button() == Qt::RightButton)
    {

        QString propertyPanelText = tr("&Property Panel");
        /*if(isPropertyWidgetVisible)
        {
            propertyPanelText = tr("Hide &Property Panel");
        }*/

        QString projectionsText = tr("Pr&ojections");
        /*if(isProjectionsVisible)
        {
            projectionsText = tr("Hide Pr&ojections");
        }*/



        propertyPanelAct = new QAction(propertyPanelText, this);
        propertyPanelAct->setCheckable(true);
        propertyPanelAct->setChecked(isPropertyWidgetVisible);
        connect(propertyPanelAct, SIGNAL(triggered()), this, SLOT(togglePropertyPanel()));

        projectionsAct = new QAction(projectionsText, this);
        projectionsAct->setCheckable(true);
        projectionsAct->setChecked(isProjectionsVisible);
        connect(projectionsAct, SIGNAL(triggered()), this, SLOT(toggleProjections()));

        resetAct = new QAction(tr("&Reset View"), this);
        connect(resetAct, SIGNAL(triggered()), this, SLOT(resetTriggered()));

        saveAct = new QAction(tr("&Save as"), this);
        connect(saveAct, SIGNAL(triggered()), this, SLOT(savePlot()));



        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);

        menu->addAction(propertyPanelAct);
        menu->addAction(projectionsAct);
        menu->addAction(resetAct);
        menu->addAction(saveAct);
        menu->exec(mouseEvent->globalPos());
    }

}

void PlotWidget::resetTriggered()
{
    m_centralPlot->resetView();
}


void PlotWidget::mouseMove(QMouseEvent * event)
{
    if(m_block_plot_update) return;

    Q_ASSERT(m_centralPlot);
    Q_ASSERT(m_horizontalPlot);
    Q_ASSERT(m_verticalPlot);
    QPoint point = event->pos();
    QVector<QVector<double> > histogramData = this->m_centralPlot->getHistogramData(point, true);

    m_statusLabel->setText(this->m_centralPlot->getStatusString());

    if(histogramData.size()>0)
    {
        this->m_horizontalPlot->generateHistogram(histogramData.at(0), histogramData.at(1));
        this->m_verticalPlot->generateHistogram(histogramData.at(2), histogramData.at(3));
    }
}


void PlotWidget::onZaxisRangeChanged(QCPRange newRange)
{
    //if(m_block_plot_update) return;
    Q_ASSERT(m_verticalPlot);
    Q_ASSERT(m_horizontalPlot);
    Q_ASSERT(m_outputDataItem);

    qDebug() << "PlotWidget::onZaxisRangeChanged" << newRange.lower << newRange.upper;
    m_outputDataItem->setZaxisRange(newRange.lower, newRange.upper);
    m_verticalPlot->setColorScaleRange(newRange.lower, newRange.upper);
    m_horizontalPlot->setColorScaleRange(newRange.lower, newRange.upper);

}

void PlotWidget::togglePropertyPanel()
{


    QList<int> sizes_org = this->m_splitter->sizes();


    int width = 0;

    if(sizes_org.at(1) > 0)
    {
        width = 0;
        isPropertyWidgetVisible = false;
    }
    else
    {
        width = m_propertyWidget->getWidth();
        isPropertyWidgetVisible = true;
    }

    //qDebug() << "togglePropertypanel called: widget:" << this->m_splitter->width() << ", new: "<< width << ", org:" <<sizes_org.at(1);

    QList<int> sizes;
    sizes.append(this->m_splitter->width() - width);
    sizes.append(width);
    this->m_splitter->setSizes(sizes);

}

void PlotWidget::toggleProjections()
{
    m_propertyWidget->toggleProjections();
}

void PlotWidget::projectionsChanged(bool projection)
{
    //qDebug() << "PW Projections: " << projection;

    isProjectionsVisible = projection;

    int width;

    if(projection)
    {
        width = this->histogramSize;
    }
    else
    {
        width = 0;
    }

    QList<int> h_sizes;
    h_sizes.append(this->m_splitterLeft->height() - width);
    h_sizes.append(width);
    this->m_splitterLeft->setSizes(h_sizes);

    QList<int> v_sizes;
    v_sizes.append(width);
    v_sizes.append(this->m_splitterTop->width()-width);
    this->m_splitterTop->setSizes(v_sizes);

    m_centralPlot->showLinesOverMap(projection);
}

void PlotWidget::gradientChanged(QCPColorGradient gradient)
{
    m_gradient = gradient;
    m_centralPlot->setGradient(gradient);

}

void PlotWidget::onXaxisRangeChanged(QCPRange newRange)
{
    //qDebug() << "onXaxisRangeChanged: "<<newRange.lower << newRange.upper;
    m_horizontalPlot->setKeyAxisRange(newRange);
}

void PlotWidget::onYaxisRangeChanged(QCPRange newRange)
{
    //qDebug() << "onYaxisRangeChanged: "<<newRange.lower << newRange.upper;
    m_verticalPlot->setKeyAxisRange(newRange);
}

void PlotWidget::setProjectionsVisible(bool visible)
{
    projectionsChanged(visible);
}

void PlotWidget::setPropertyPanelVisible(bool visible)
{
    int width = 0;
    isPropertyWidgetVisible = visible;

    if(isPropertyWidgetVisible)
    {
        width = m_propertyWidget->getWidth();
    }
    else
    {
        width = 0;
    }

    QList<int> sizes;
    sizes.append(this->m_splitter->width() - width);
    sizes.append(width);
    this->m_splitter->setSizes(sizes);
}

