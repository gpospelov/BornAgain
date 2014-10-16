#include "PlotWidget.h"
#include "histogramplot.h"
#include "OutputData.h"
#include "projectmanager.h"
#include "minisplitter.h"
#include "projectdocument.h"
#include <QVBoxLayout>


PlotWidget::PlotWidget(QWidget *parent, bool isContextMenuEnabled, bool isProjectionsEnabled)
    : QWidget(parent)
    , m_splitter(new QSplitter(this))
    , m_centralPlot(new CentralPlot())
    , m_verticalPlot(new HistogramPlot(HistogramPlot::Vertical))
    , m_horizontalPlot(new HistogramPlot(HistogramPlot::Horizontal))
    , m_outputDataItem(0)
    , m_block_plot_update(true)
    , m_isProjectionsEnabled(isProjectionsEnabled)
    , m_isContextMenuEnabled(isContextMenuEnabled)
{
    this->setObjectName(QStringLiteral("plotWidget"));

    m_gradient = QCPColorGradient::gpPolar;
    m_isPropertyWidgetVisible = true;
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

    if(m_isProjectionsEnabled == false)
    {
        showProjectsions(m_isProjectionsEnabled);
    }
}


void PlotWidget::savePlot()
{

    if(m_isProjectionsEnabled)
    {
        m_centralPlot->showLinesOverMap(false);
    }




    QString filters("*.png;;*.jpg;;*.pdf");
    QString defaultFilter("*.png");
    QString defaultName = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/untitled");

    if(m_projectManager)
    {
        ProjectDocument *document  = m_projectManager->getDocument();

        if(document->hasValidNameAndPath())
        {
            defaultName = document->getProjectPath().append("/").append(document->getProjectName()).append("/untitled");
        }
    }

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

void PlotWidget::setProjectManager(ProjectManager *projectManager)
{
    m_projectManager = projectManager;
}


void PlotWidget::drawPlot(OutputDataItem *outputDataItem)
{
    qDebug() << "PlotWidget::drawPlot()";
//    Q_ASSERT(outputDataItem);
    if(!outputDataItem) {

        qDebug() << "   PlotWidget::drawPlot() -> Zero item, disconnecting";
        //disconnect();
        m_centralPlot->disconnect();
        m_outputDataItem->disconnect();
        m_outputDataItem = 0;
        return;
    }


    if(m_outputDataItem == outputDataItem) {
        qDebug() << "PlotWidget::drawPlot() -> Same outputDataItem !!!";
        //updatePlot();
        return;
    }

    //disconnect();
    m_centralPlot->disconnect();
    m_outputDataItem->disconnect();

    m_outputDataItem = outputDataItem;


    if(outputDataItem)
    {
        qDebug() << "       PlotWidget::drawPlot() -> preparing all connections";

        m_block_plot_update = true;
        qDebug() << "PlotWidget::drawPlot called";

        m_centralPlot->drawPlot(outputDataItem, m_gradient);
        m_verticalPlot->setupMap(m_centralPlot);
        m_horizontalPlot->setupMap(m_centralPlot);
        //m_propertyWidget->setupPropertyWidget(outputDataItem, m_gradient);

        connectSignals();

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

void PlotWidget::updateIntensity()
{
    qDebug() << "PlotWidget::updateIntensity()";
    m_centralPlot->drawPlot(m_outputDataItem, m_gradient);
}


void PlotWidget::initContextMenu()
{
    QString propertyPanelText = tr("&Property Panel");
    QString projectionsText = tr("Pr&ojections");


    m_propertyPanelAction = new QAction(propertyPanelText, this);
    m_propertyPanelAction->setCheckable(true);
    connect(m_propertyPanelAction, SIGNAL(triggered(bool)), this, SIGNAL(propertyWidgetVisibilityChanged(bool)));


    m_projectionsAction = new QAction(projectionsText, this);
    m_projectionsAction->setCheckable(true);
    connect(m_projectionsAction, SIGNAL(triggered(bool)), this, SLOT(projectionsChanged(bool)));

    m_resetAction = new QAction(tr("&Reset View"), this);
    connect(m_resetAction, SIGNAL(triggered()), this, SLOT(resetTriggered()));

    m_saveAction = new QAction(tr("&Save as"), this);
    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(savePlot()));





}

void PlotWidget::mousePress(QMouseEvent *event)
{
    if(m_block_plot_update) return;


    qDebug() << "PlotWidget::mousePress" << event->pos().x() << " : " << event->pos().y();



    if(event->button() == Qt::RightButton && m_isContextMenuEnabled)
    {
        m_propertyPanelAction->setChecked(m_isPropertyWidgetVisible);
        m_projectionsAction->setChecked(m_isProjectionsEnabled);

        m_contextMenu = new QMenu();

        m_contextMenu->addAction(m_propertyPanelAction);
        m_contextMenu->addAction(m_projectionsAction);
        m_contextMenu->addAction(m_resetAction);
        m_contextMenu->addAction(m_saveAction);


        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        m_contextMenu->exec(mouseEvent->globalPos());
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

    showProjectsions(projection);

    emit projectionsVisibilityChanged(projection);
}

void PlotWidget::showProjectsions(bool visible)
{
    int width;

    if(visible)
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

    m_centralPlot->showLinesOverMap(visible);
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


void PlotWidget::connectSignals()
{
    connect(m_centralPlot, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onZaxisRangeChanged(QCPRange)), Qt::UniqueConnection);
    connect(m_centralPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)), Qt::UniqueConnection);
    connect(m_centralPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)), Qt::UniqueConnection);
    connect(m_centralPlot, SIGNAL(xaxisRangeChanged(QCPRange)), this, SLOT(onXaxisRangeChanged(QCPRange)), Qt::UniqueConnection);
    connect(m_centralPlot, SIGNAL(yaxisRangeChanged(QCPRange)), this, SLOT(onYaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

    connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(updatePlot()), Qt::UniqueConnection);
    connect(m_outputDataItem, SIGNAL(intensityModified()), this, SLOT(updateIntensity()), Qt::UniqueConnection);
}

void PlotWidget::setPropertyWidgetVisibilityFlag(bool visible)
{
    m_isPropertyWidgetVisible = visible;
}


