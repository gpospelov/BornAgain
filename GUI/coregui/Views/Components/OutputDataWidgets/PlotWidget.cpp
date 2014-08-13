#include "PlotWidget.h"
#include "histogramplot.h"
#include "OutputData.h"
#include "minisplitter.h"
#include <QVBoxLayout>


PlotWidget::PlotWidget(QWidget *parent, bool isContextMenuEnabled)
    : QWidget(parent)
    , m_splitter(new QSplitter(this))
    , m_centralPlot(new CentralPlot())
    , m_verticalPlot(new HistogramPlot(HistogramPlot::Vertical))
    , m_horizontalPlot(new HistogramPlot(HistogramPlot::Horizontal))
    , m_outputDataItem(0)
    , m_block_plot_update(true)
{
    this->setObjectName(QStringLiteral("plotWidget"));

    m_gradient = QCPColorGradient::gpPolar;

    m_isProjectionsEnabled = true;
    m_isContextMenuEnabled = isContextMenuEnabled;
    histogramSize = 150;
    //int horizontalHeight = histogramSize-15;

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

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_splitterTop);
    m_splitter->addWidget(m_splitterBottom);
    m_splitter->setStyleSheet("background-color:white;");




    m_statusLabel = new QLabel(this);
    //m_statusLabel->setFrameStyle(QFrame::Panel );
    m_statusLabel->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    //m_statusLabel->setMaximumHeight(35);
    m_statusLabel->setStyleSheet("background-color:white;");
    m_statusLabel->setMargin(3);





    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);
    vlayout->addWidget(m_statusLabel);
    this->setLayout(vlayout);
    //setCentralWidget(widget);




    QList<int> h1_sizes;
    h1_sizes.append(histogramSize);
    h1_sizes.append(600);
    this->m_splitterBottom->setSizes(h1_sizes);

    QList<int> h_sizes;
    h_sizes.append(585);
    h_sizes.append(histogramSize);
    this->m_splitter->setSizes(h_sizes);

    QList<int> v_sizes;
    v_sizes.append(histogramSize);
    v_sizes.append(600);
    this->m_splitterTop->setSizes(v_sizes);

    initContextMenu();

}


void PlotWidget::savePlot()
{

    if(m_isProjectionsEnabled)
    {
        m_centralPlot->showLinesOverMap(false);
    }

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


    m_centralPlot->showLinesOverMap(m_isProjectionsEnabled);

}


void PlotWidget::drawPlot(OutputDataItem *outputDataItem)
{
    qDebug() << "PlotWidget::drawPlot()";
//    Q_ASSERT(outputDataItem);
    if(!outputDataItem) {

        qDebug() << "   PlotWidget::drawPlot() -> Zero item, disconnecting";
        disconnect();
        m_centralPlot->disconnect();

        m_outputDataItem = 0;
        return;
    }


    if(m_outputDataItem == outputDataItem) {
        qDebug() << "PlotWidget::drawPlot() -> Same outputDataItem !!!";
        //updatePlot();
        return;
    }

    disconnect();
    m_centralPlot->disconnect();

    m_outputDataItem = outputDataItem;


    if(outputDataItem)
    {
        qDebug() << "       PlotWidget::drawPlot() -> preparing all connections";

        m_block_plot_update = true;
        qDebug() << "PlotWidget::drawPlot called";
//        disconnect(m_centralPlot, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onZaxisRangeChanged(QCPRange)));
//        disconnect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
 //       disconnect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
        m_centralPlot->drawPlot(outputDataItem, m_gradient);
        m_verticalPlot->setupMap(m_centralPlot);
        m_horizontalPlot->setupMap(m_centralPlot);
        //m_propertyWidget->setupPropertyWidget(outputDataItem, m_gradient);

        connect(m_centralPlot, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onZaxisRangeChanged(QCPRange)), Qt::UniqueConnection);
        connect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)), Qt::UniqueConnection);
        connect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)), Qt::UniqueConnection);
        connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(updatePlot()), Qt::UniqueConnection);
        connect(m_centralPlot, SIGNAL(xaxisRangeChanged(QCPRange)), this, SLOT(onXaxisRangeChanged(QCPRange)), Qt::UniqueConnection);
        connect(m_centralPlot, SIGNAL(yaxisRangeChanged(QCPRange)), this, SLOT(onYaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

        m_block_plot_update = false;
    }
}


void PlotWidget::updatePlot()
{

    qDebug() << "PlotWidget::updatePlot()";
    if(m_block_plot_update) {
        qDebug() << "   PlotWidget::updatePlot() -> blocked, no update";
        return;
    }

    //qDebug() << "PlotWidget::updatePlot()";
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


void PlotWidget::initContextMenu()
{
    QString propertyPanelText = tr("&Property Panel");
    QString projectionsText = tr("Pr&ojections");


    propertyPanelAct = new QAction(propertyPanelText, this);
    propertyPanelAct->setCheckable(true);
    //propertyPanelAct->setChecked(isPropertyWidgetVisible);
    connect(propertyPanelAct, SIGNAL(triggered(bool)), this, SLOT(propertyWidgetChanged(bool)));


    projectionsAct = new QAction(projectionsText, this);
    projectionsAct->setCheckable(true);
    connect(projectionsAct, SIGNAL(triggered(bool)), this, SLOT(projectionsChanged(bool)));

    resetAct = new QAction(tr("&Reset View"), this);
    connect(resetAct, SIGNAL(triggered()), this, SLOT(resetTriggered()));

    saveAct = new QAction(tr("&Save as"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(savePlot()));




    m_contextMenu = new QMenu();

    m_contextMenu->addAction(propertyPanelAct);
    m_contextMenu->addAction(projectionsAct);
    m_contextMenu->addAction(resetAct);
    m_contextMenu->addAction(saveAct);
}

void PlotWidget::mousePress(QMouseEvent *event)
{
    if(m_block_plot_update) return;

    if(m_contextMenu->isVisible())
    {
        m_contextMenu->close();
    }


    qDebug() << "PlotWidget::mousePress" << event->pos().x() << " : " << event->pos().y();

    qDebug() << event->pos().x() << " : " << event->pos().y();


    if(event->button() == Qt::RightButton && m_isContextMenuEnabled)
    {
        projectionsAct->setChecked(m_isProjectionsEnabled);
        m_mouseEvent = static_cast<QMouseEvent*> (event);
        m_contextMenu->exec(m_mouseEvent->globalPos());
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
    QVector<QVector<double> > histogramData = this->m_centralPlot->getHistogramData(point, m_isProjectionsEnabled);

    m_statusLabel->setText(this->m_centralPlot->getStatusString());

    if(histogramData.size()>0 && m_isProjectionsEnabled)
    {
        this->m_horizontalPlot->generateHistogram(histogramData.at(0), histogramData.at(1));
        this->m_verticalPlot->generateHistogram(histogramData.at(2), histogramData.at(3));
    }
}


void PlotWidget::onZaxisRangeChanged(QCPRange newRange)
{
    qDebug() << "PlotWidget::onZaxisRangeChanged()";

    //if(m_block_plot_update) return;
    m_block_plot_update = true;
    Q_ASSERT(m_verticalPlot);
    Q_ASSERT(m_horizontalPlot);
    Q_ASSERT(m_outputDataItem);

    //qDebug() << "PlotWidget::onZaxisRangeChanged" << newRange.lower << newRange.upper;
    m_outputDataItem->setZaxisRange(newRange.lower, newRange.upper);
    m_verticalPlot->setColorScaleRange(newRange.lower, newRange.upper);
    m_horizontalPlot->setColorScaleRange(newRange.lower, newRange.upper);

    m_block_plot_update = false;
}



void PlotWidget::projectionsChanged(bool projection)
{

    if(projection == m_isProjectionsEnabled)
    {
        return;
    }

    m_isProjectionsEnabled = projection;

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
    h_sizes.append(this->m_splitter->height() - width);
    h_sizes.append(width);
    this->m_splitter->setSizes(h_sizes);

    QList<int> v_sizes;
    v_sizes.append(width);
    v_sizes.append(this->m_splitterTop->width()-width);
    this->m_splitterTop->setSizes(v_sizes);

    m_centralPlot->showLinesOverMap(projection);
    emit projectionsVisibilityChanged(projection);
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

void PlotWidget::propertyWidgetChanged(bool visible)
{
    qDebug() << "PlotWidget::propertyWidgetVisibilityChanged" << visible;
    emit propertyWidgetVisibilityChanged(visible);
}


