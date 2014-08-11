#include "centralplot.h"
#include <algorithm>
#include <iostream>



CentralPlot::CentralPlot()
    : QCustomPlot()
    , m_colorMap(0)
    , m_colorScale(0)
    , m_outputDataItem(0)
{
    this->setObjectName(QStringLiteral("centralPlot"));
    //setupColorMap(this);


}


void CentralPlot::drawLineOverColorMap(double xPos, double yPos)
{
    //qDebug() << "x:" << xPos;

    if(!this->graph(0)->visible() || !this->graph(1)->visible())
    {
        return;
    }

    // FIXME Why not dynamic_cast ?
    QCPColorMap * colorMap = (QCPColorMap *) this->plottable(0);
    Q_ASSERT(colorMap);

    QCPColorMapData * data  = colorMap->data();
    Q_ASSERT(data);

    //draw line over plot
    QCPRange keyRange = data->keyRange();
    QCPRange valueRange = data->valueRange();

    int keySize = data->keySize();
    int valueSize = data->valueSize();

    //qDebug() << "keySize: " << keySize << " Value Size:" << valueSize;

    //draw horizontal line

    double fraction = (keyRange.upper-keyRange.lower)/keySize;

    QVector<double> x1(keySize+1), y1(valueSize+1);
    for(int i=0;i<x1.size();i++)
    {
        x1[i] = keyRange.lower + (i*fraction);
        y1[i] = yPos;

        //qDebug() << "Line draw1: X:" << x1[i] << " Y:" << y1[i];
    }
    this->graph(0)->setData(x1, y1);

    //draw vertical line

    fraction = (valueRange.upper-valueRange.lower)/valueSize;

    QVector<double> x2(valueSize+1), y2(keySize+1);
    for(int i=0;i<x2.size();i++)
    {
        x2[i] = xPos;
        y2[i] = valueRange.lower+(i*fraction);

        //qDebug() << "Line draw2: X:" << x2[i] << " Y:" << y2[i];
    }
    this->graph(1)->setData(x2, y2);

    //replot the graph
    this->replot();
}


bool CentralPlot::contains(QPoint point)
{
    double xPos = this->xAxis->pixelToCoord(point.x());
    double yPos = this->yAxis->pixelToCoord(point.y());

    return this->xAxis->range().contains(xPos) && this->yAxis->range().contains(yPos);
}



//void CentralPlot::drawGraphOnMouseEvent(QPoint point, HistogramPlot *verticalPlot, HistogramPlot *horizontalPlot)
QVector<QVector<double> > CentralPlot::getHistogramData(QPoint point, bool isDrawLine)
{

   double xPos = this->xAxis->pixelToCoord(point.x());
   double yPos = this->yAxis->pixelToCoord(point.y());

   QVector<QVector<double> > histogramData;


   //if(this->xAxis->range().contains(xPos) && this->yAxis->range().contains(yPos))
   if(this->contains(point))
   {

       //set status bar info
       QCPColorMap * colorMap = (QCPColorMap *) this->plottable(0);
       Q_ASSERT(colorMap);
       QCPColorMapData * data  = colorMap->data();
       Q_ASSERT(data);
       int key = 0;
       int value = 0;

       int keySize = data->keySize();
       int valueSize = data->valueSize();

       data->coordToCell(xPos, yPos, &key, &value);

       double cellValue = data->cell(key, value);
       std::ostringstream ss;
       ss << " [X: " << xPos << ", Y: " << yPos << "]\t[nBinX: " << key << ", nBinY: " << value << "] \t[Value: " << cellValue << "]";

       statusString = QString::fromStdString(ss.str());
       //ui->cellPropertiesLabel->setText(QString::fromStdString(ss.str()));
       //end of status bar info


       //draw line over color map indicating coordinate
       if(isDrawLine)
       {
            drawLineOverColorMap(xPos, yPos);
       }



       //horizontal histogram
       QCPRange range = data->keyRange();
       QVector<double> x1(keySize), y1(keySize);

       double fraction = (range.upper-range.lower)/keySize;

       for(int i=0; i<x1.size(); ++i)
       {
          // x1[i] =  range.lower + (i/(double)x1.size());
           x1[i] =  range.lower + (i*fraction);

           if(value>=0 && value<valueSize)
           {
                y1[i] = data->cell(i, value);
           }
           else
           {
               y1[i] = 0;
           }


       }
       //end of horizontal histogram

       //vertical histogram
       range = data->valueRange();
       QVector<double> x2(valueSize), y2(valueSize);
       fraction = (range.upper-range.lower)/valueSize;
       for(int i=0; i<x2.size(); ++i)
       {
           //x2[i] =  range.lower + (i/(double)x2.size()*10);
           x2[i] =  range.lower + (i*fraction);

           if(key>=0 && key< keySize)
           {
                y2[i] = data->cell(key, i);
           }
           else
           {
               y2[i] = 0;
           }

           //qDebug() << "X: " << x2[i] << " Y: " << y2[i];
       }
       //end of vertical histogram

        histogramData.append(x1);
        histogramData.append(y1);
        histogramData.append(x2);
        histogramData.append(y2);

    }
    else
    {
       //ui->cellPropertiesLabel->setText("");
       statusString = "";
    }

    return histogramData;
}


void CentralPlot::drawPlot(OutputDataItem *outputDataItem, QCPColorGradient gradient)
{
//    disconnect();
    Q_ASSERT(outputDataItem);
    qDebug() << "CentralPlot::drawPlot 1.1";
    m_outputDataItem = outputDataItem;
    const OutputData<double> *data = outputDataItem->getOutputData();



    Q_ASSERT(data);

    if(data->getRank() != 2) {
        throw NullPointerException("CustomCanvas::Draw() -> Error. Zero pointer to the data to draw");
    }

    OutputData<double>::const_iterator it_max = std::max_element(data->begin(), data->end());
    OutputData<double>::const_iterator it_min = std::min_element(data->begin(), data->end());

    std::cout << "CentralPlot::drawPlot min max" << (*it_min) << " "<< (*it_max) << std::endl;

    this->clearPlottables();
    qDebug() << "CentralPlot::drawPlot 1.2 after clearPlottable";
    // FIXME Is it correct?
    m_colorMap = 0;
    //m_customPlot->clearItems();


    qDebug() << "CentralPlot::drawPlot 1.3";
    this->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    this->axisRect()->setupFullAxesBox(true);
    this->xAxis->setLabel(outputDataItem->getXaxisTitle());
    this->yAxis->setLabel(outputDataItem->getYaxisTitle());

    // set up the QCPColorMap:

    // FIXME why axes and color map connected here?
    if(m_colorMap) {
        qDebug() << "CentralPlot::drawPlot 1.4";
        disconnect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this, SIGNAL(dataRangeChanged(QCPRange)));

    }

    delete m_colorMap;
    m_colorMap = new QCPColorMap(this->xAxis, this->yAxis);
    this->addPlottable(m_colorMap);

    connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this, SIGNAL(dataRangeChanged(QCPRange)), Qt::UniqueConnection);
    connect(this->xAxis,SIGNAL(rangeChanged(QCPRange)), this, SIGNAL(xaxisRangeChanged(QCPRange)), Qt::UniqueConnection);
    connect(this->yAxis,SIGNAL(rangeChanged(QCPRange)), this, SIGNAL(yaxisRangeChanged(QCPRange)), Qt::UniqueConnection);


    const IAxis *axis_x = data->getAxis(0);
    const IAxis *axis_y = data->getAxis(1);


    int nx = axis_x->getSize();
    int ny = axis_y->getSize();
    qDebug() << "CentralPlot::drawPlot 1.5";

    m_colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    m_colorMap->data()->setRange(QCPRange(axis_x->getMin(), axis_x->getMax()), QCPRange(axis_y->getMin(), axis_y->getMax()));

    qDebug() << "CentralPlot::drawPlot 1.6";

    OutputData<double>::const_iterator it = data->begin();
    while (it != data->end()) {
        std::vector<int> indices =
                data->toCoordinates(it.getIndex());
        //qDebug() << *it;

        m_colorMap->data()->setCell(indices[0], indices[1], *it);

        ++it;
    }

    qDebug() << "CentralPlot::drawPlot 1.7";

    // add a color scale:
    m_colorScale = new QCPColorScale(this);
    this->plotLayout()->addElement(0, 1, m_colorScale); // add it to the right of the main axis rect


    this->setLogz(outputDataItem->isLogz(), false);

    qDebug() << "CentralPlot::drawPlot 1.8";

    m_colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    m_colorMap->setColorScale(m_colorScale); // associate the color map with the color scale

    // set the color gradient of the color map to one of the presets:
    //m_colorMap->setGradient(QCPColorGradient::gpPolar);
    m_colorMap->setGradient(gradient);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    qDebug() << "CentralPlot::drawPlot 1.9";

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    m_colorMap->rescaleDataRange();

    QCPRange newDataRange = calculateDataRange();
    m_colorMap->setDataRange(newDataRange);
    outputDataItem->setZaxisRange(newDataRange.lower, newDataRange.upper);

    qDebug() << "CentralPlot::drawPlot 1.10";

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    m_colorScaleRange = m_colorScale->dataRange();


//    QCPRange range2 = colorScale->dataRange();
//    qDebug()<< "Color scale: Min Max" << range2.lower << range2.upper;

    qDebug() << "CentralPlot::drawPlot 1.11";


    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255, 130));

    qDebug() << "CentralPlot::drawPlot 1.12";

    this->addGraph();
    this->graph(0)->setPen(pen);

    this->addGraph();
    this->graph(1)->setPen(pen);
    qDebug() << "CentralPlot::drawPlot 1.13";

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    this->rescaleAxes();
    qDebug() << "CentralPlot::drawPlot 1.14";

    this->replot();
    qDebug() << "CentralPlot::drawPlot 1.15";
}

QCPRange CentralPlot::calculateDataRange()
{
    //qDebug() << "ZMIN ZMAX" << m_colorMap->dataRange().lower<< ":" << m_colorMap->dataRange().upper;

    if(!m_colorMap)
    {
        return QCPRange(0, 0);
    }

    double min, max;
    QCPRange dataRange  = m_colorMap->dataRange();
    min = dataRange.lower;
    max = dataRange.upper;

    if(m_outputDataItem->isLogz())
    {
        if(max>10000)
        {
            min = 1.0;
            max = max*1.1;
        }
        else
        {
            max = max*1.1;
            min = max/10000;
        }
    }
    else
    {
        min = dataRange.lower;
        max = dataRange.upper*1.1;
    }
    return QCPRange(min, max);
}

/*QCPColorScale *CentralPlot::getColorScale() const
{
    return this->colorMap->colorScale();
}*/

QCPColorMap *CentralPlot::getColorMap() const
{
    return this->m_colorMap;
}

QCPRange CentralPlot::getColorScaleRange() const
{
    return this->m_colorMap->colorScale()->dataRange();
}

QCPColorMapData *CentralPlot::getColorMapData() const
{
    return this->m_colorMap->data();
}

QString CentralPlot::getStatusString() const
{
    return statusString;
}

void CentralPlot::setInterpolate(bool isInterpolate)
{
    m_colorMap->setInterpolate(isInterpolate);
    this->replot();
}

void CentralPlot::setZmin(double zmin)
{

    QCPRange range = getColorMap()->dataRange();
    //qDebug() << "CentralPlot::setZmin " << zmin << range.lower;
    if(zmin != range.lower) {
        range.lower = zmin;
        getColorMap()->setDataRange(range);
        this->replot();
    }
}

void CentralPlot::setZmax(double zmax)
{
    QCPRange range = getColorMap()->dataRange();
    //qDebug() << "CentralPlot::setZmax " << zmax << range.upper;
    if(zmax != range.upper) {
        range.upper = zmax;
        getColorMap()->setDataRange(range);
        this->replot();
    }
}


void CentralPlot::resetView()
{
    this->m_colorMap->rescaleAxes();
    this->m_colorScale->setDataRange(m_colorScaleRange);
    this->replot();
}

void CentralPlot::setGradient(QCPColorGradient gradient)
{
    m_colorMap->setGradient(gradient);
    this->replot();
}

void CentralPlot::setLogz(bool logz, bool isReplot)
{
    if(logz)
    {
        m_colorScale->setDataScaleType(QCPAxis::stLogarithmic);
    }
    else
    {
        m_colorScale->setDataScaleType(QCPAxis::stLinear);
    }

    if(isReplot)
    {
        this->replot();
    }

}

bool CentralPlot::isLogz()
{
    return m_outputDataItem->isLogz();
}

void CentralPlot::showLinesOverMap(bool isLineVisible)
{
    if(this->graph(0) && this->graph(1))
    {
        this->graph(0)->setVisible(isLineVisible);
        this->graph(1)->setVisible(isLineVisible);
        this->replot();
    }
}

void CentralPlot::setXaxisTitle(QString xtitle)
{
    this->xAxis->setLabel(xtitle);
    this->replot();
}

void CentralPlot::setYaxisTitle(QString ytitle)
{
    this->yAxis->setLabel(ytitle);
    this->replot();
}

//void CentralPlot::onDataRangeChanged(QCPRange newRange)
//{
//    qDebug() << "CentralPlot::onDataRangeChanged" << newRange.lower << newRange.upper;
//}
