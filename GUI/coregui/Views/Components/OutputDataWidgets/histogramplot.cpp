#include "histogramplot.h"


HistogramPlot::HistogramPlot(PlotType type)
    :QCustomPlot()
{
    this->setObjectName(QStringLiteral("histogramPlot"));
    //qDebug() << type;
    m_type = type;
}

void HistogramPlot::setupMap(CentralPlot *centralPlot)
{
    QCPColorMapData * data  = centralPlot->getColorMapData();

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

    this->yAxis->setRange(min, max);
    this->xAxis->setRange(range.lower, range.upper);
    this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    //set Logarithmic scale
    QCPRange colorScaleRange = centralPlot->getColorScaleRange();
    this->yAxis->setScaleType(QCPAxis::stLogarithmic);
    this->yAxis->setRange(1.0, colorScaleRange.upper);
    //end of logarithmic



    QCPBars *bars = new QCPBars(this->xAxis, this->yAxis);
    this->addPlottable(bars);
    //bars->setWidth(10/(double)binSize);
    bars->setWidth((xAxis->range().upper - xAxis->range().lower)/binSize);
    bars->setPen(Qt::NoPen);
    bars->setBrush(Qt::blue);



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
    this->xAxis->setRange(min, max);
    this->yAxis->setRange(range.lower, range.upper);
    this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));


    //set Logarithmic scale
    QCPRange colorScaleRange = centralPlot->getColorScaleRange();
    this->xAxis->setScaleType(QCPAxis::stLogarithmic);
    this->xAxis->setRange(1.0, colorScaleRange.upper);
    //end of logarithmic


    QCPBars *bars = new QCPBars(this->yAxis, this->xAxis);
    this->addPlottable(bars);
    bars->setWidth((yAxis->range().upper - yAxis->range().lower)/binSize);
    bars->setPen(Qt::NoPen);
    bars->setBrush(Qt::blue);

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
