#include "OutputDataWidget.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "JobItem.h"
#include "OutputDataItem.h"
#include "qcustomplot.h"

#include <QVBoxLayout>
#include <QModelIndex>


OutputDataWidget::OutputDataWidget(JobQueueModel *model, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_customPlot(0)
    , m_currentJobItem(0)
    , m_data(0)
{
    setModel(model);

    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");

    m_customPlot = new QCustomPlot(this);
    m_customPlot->setObjectName(QString::fromUtf8("OutputDataWidget::customPlot"));
    m_customPlot->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(canvas);
    mainLayout->addWidget(m_customPlot);
    setLayout(mainLayout);

}


void OutputDataWidget::setModel(JobQueueModel *model)
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


    }
}


void OutputDataWidget::itemClicked(JobItem *jobItem)
{
    qDebug() << "OutputDataWidget::itemClicked" << jobItem->getName();

    if(m_currentJobItem != jobItem)
        m_currentJobItem = jobItem;

    OutputDataItem *dataItem = jobItem->getOutputDataItem();

    if(!dataItem || !dataItem->getOutputData()) {
        m_customPlot->hide();
        return;
    }

    m_customPlot->show();
    Draw(dataItem->getOutputData());
}


void OutputDataWidget::dataChanged(const QModelIndex &index, const QModelIndex &)
{
    qDebug() << "OutputDataWidget::dataChanged()";
    JobItem *jobItem = m_jobQueueModel->getJobItemForIndex(index);
    if(jobItem == m_currentJobItem) {
        itemClicked(jobItem);
    }
}



void OutputDataWidget::Draw(const OutputData<double> *data)
{
    Q_ASSERT(data);

    if(data->getRank() != 2) {
        throw NullPointerException("CustomCanvas::Draw() -> Error. Zero pointer to the data to draw");
    }

    if(data == m_data)
        return;

    m_data = data;

    qDebug() << "OutputDataWidget::Draw() ->";
    m_customPlot->clearPlottables();


    m_customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    m_customPlot->axisRect()->setupFullAxesBox(true);
    m_customPlot->xAxis->setLabel("x");
    m_customPlot->yAxis->setLabel("y");

    const IAxis *axis_x = data->getAxis(0);
    const IAxis *axis_y = data->getAxis(1);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(colorMap);

    int nx = axis_x->getSize();
    int ny = axis_y->getSize();
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(axis_x->getMin(), axis_x->getMax()), QCPRange(axis_y->getMin(), axis_y->getMax()));

    OutputData<double>::const_iterator it = data->begin();
    while (it != data->end()) {
        std::vector<int> indices =
                data->toCoordinates(it.getIndex());

        colorMap->data()->setCell(indices[0], indices[1], *it);
        ++it;
    }


    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(m_customPlot);
    m_customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect

    colorScale->setDataScaleType(QCPAxis::stLogarithmic);

    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    m_customPlot->rescaleAxes();

    m_customPlot->replot();
}

