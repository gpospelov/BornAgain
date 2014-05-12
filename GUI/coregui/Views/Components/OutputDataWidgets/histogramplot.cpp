#include "histogramplot.h"


HistogramPlot::HistogramPlot(PlotType type)
    :QCustomPlot()
{
    this->setObjectName(QStringLiteral("histogramPlot"));

    m_type = type;

}

/*QSize HistogramPlot::sizeHint() const {

qDebug() << "Hist Size:" <<histogramSize;
    if(m_type == this->Vertical)
    {
        return QSize(histogramSize, 600);
    }
    else
    {
        return QSize(600, histogramSize);
    }

}*/

void HistogramPlot::setupMap(CentralPlot *centralPlot)
{
    qDebug() << "HistogramPlot::setupMap()";
    Q_ASSERT(centralPlot);
    QCPColorMapData * data  = centralPlot->getColorMapData();
    Q_ASSERT(data);

    double min = data->cell(0,0);
    double max= data->cell(0,0);

    for(int i=0; i<data->keySize();i++)
    {
        for(int j=0;j<data->valueSize();j++)
        {
            double val = data->cell(i,j);
            if(min > val)
            {
                min = val;
            }
            else if(max < val)
            {
                max = val;
            }
        }
    }

    qDebug() << "Min: " << min << " Max: " << max;

    if(m_type == this->Vertical)
    {

        setupVerticalMap(centralPlot, min, max);
    }
    else
    {

        setupHorizontalMap(centralPlot, min, max);
    }
}



void HistogramPlot::setupHorizontalMap(CentralPlot *centralPlot, double min, double max)
{

    this->clearPlottables();
    this->axisRect()->setupFullAxesBox(true);

    QCPColorMapData * data  = centralPlot->getColorMapData();
    int binSize = data->keySize();
    QCPRange range = data->keyRange();

    m_dataScaleAxis = this->yAxis;

    this->yAxis->setRange(min, max);
    this->xAxis->setRange(range.lower, range.upper);
    this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    //set Logarithmic scale
    QCPRange colorScaleRange = centralPlot->getColorScaleRange();
    //this->yAxis->setScaleType(QCPAxis::stLogarithmic);
    this->setLogz(centralPlot->isLogz(), false);
    //this->yAxis->setRange(1.0, colorScaleRange.upper);
    this->yAxis->setRange(colorScaleRange.lower, colorScaleRange.upper);
    //end of logarithmic



    QCPBars *bars = new QCPBars(this->xAxis, this->yAxis);
    this->addPlottable(bars);
    //bars->setWidth(10/(double)binSize);
    bars->setWidth((xAxis->range().upper - xAxis->range().lower)/binSize);
    bars->setPen(Qt::NoPen);
    bars->setBrush(Qt::blue);


    const QMargins margins(28,0,82,0);

    this->axisRect()->setMargins(margins);
    this->axisRect()->layout()->setMargins(margins);

    //this->yAxis->setAutoTicks(false);
    //this->yAxis->setAutoTickLabels(false);
    //this->yAxis->setTickVector(QVector<double>() << this->yAxis->range().lower << this->yAxis->range().upper);
    //this->yAxis->setTickVectorLabels(QVector<QString>() << "-1.0" << "1.0");

    this->replot();

}

void HistogramPlot::setupVerticalMap(CentralPlot *centralPlot, double min, double max)
{

    this->clearPlottables();
    this->axisRect()->setupFullAxesBox(true);


    QCPColorMapData * data  = centralPlot->getColorMapData();
    int binSize = data->valueSize();
    QCPRange range = data->valueRange();

    //qDebug() << "Range" << range.lower;

    //qDebug() << "yyy vertical 1.0" << min << max << range.lower << range.upper;

    m_dataScaleAxis = this->xAxis;

    this->xAxis->setRange(min, max);
    this->yAxis->setRange(range.lower, range.upper);
    this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));


    //set Logarithmic scale
    QCPRange colorScaleRange = centralPlot->getColorScaleRange();
    this->setLogz(centralPlot->isLogz(), false);
    //this->xAxis->setScaleType(QCPAxis::stLogarithmic);
    //this->xAxis->setRange(1.0, colorScaleRange.upper);
    this->xAxis->setRange(colorScaleRange.lower, colorScaleRange.upper);
    //end of logarithmic


    QCPBars *bars = new QCPBars(this->yAxis, this->xAxis);
    this->addPlottable(bars);
    bars->setWidth((yAxis->range().upper - yAxis->range().lower)/binSize);
    bars->setPen(Qt::NoPen);
    bars->setBrush(Qt::blue);

    const QMargins margins(0,0,0,0);

    this->axisRect()->setMargins(margins);
    this->axisRect()->layout()->setMargins(margins);

    qDebug() << QString::number(this->xAxis->range().upper, 'e',0);

    //this->xAxis->setAutoTicks(false);
    //this->xAxis->setAutoTickLabels(false);
    //this->xAxis->setTickVector(QVector<double>() << this->xAxis->range().lower << this->xAxis->range().upper);
    //this->xAxis->setTickVectorLabels(QVector<QString>() << QString::number(this->xAxis->range().lower) <<  QString::number(this->xAxis->range().upper));
    this->xAxis->setTickLabelRotation(-90.0);



    this->replot();
}



void HistogramPlot::generateHistogram(const QVector<double> x, const QVector<double> y)
{
    /*qDebug() << x.size() << y.size() << x[10] << y[10];
    for(size_t i=0; i<x.size(); ++i) {
        qDebug() << x[i] << y[i];
    }*/

    QCPBars * bars = (QCPBars *)this->plottable(0);
    bars->setData(x, y);
    this->replot();
}

void HistogramPlot::setLogz(bool logz, bool isReplot)
{
    if(m_dataScaleAxis)
    {
        if(logz)
        {
            m_dataScaleAxis->setScaleType(QCPAxis::stLogarithmic);
        } else {
            m_dataScaleAxis->setScaleType(QCPAxis::stLinear);
        }

        if(isReplot)
        {
            this->replot();
        }
    }

}

void HistogramPlot::setColorScaleRange(double lower, double upper)
{
    if(m_dataScaleAxis)
    {
        m_dataScaleAxis->setRange(lower, upper);
        this->replot();
    }
}
