// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/ColorMapPlot.cpp
//! @brief     Implements class ColorMapPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ColorMapPlot.h"
#include "NIntensityDataItem.h"
#include "GUIHelpers.h"
#include "Units.h"
#include "qcpdocumentobject.h"
#include <QDebug>

ColorMapPlot::ColorMapPlot(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
    , m_colorMap(0)
    , m_colorScale(0)
    , m_item(0)
    , m_block_update(true)
{
    initColorMap();

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
}

void ColorMapPlot::setItem(NIntensityDataItem *item)
{
    qDebug() << "ColorMapPlot::setItem(NIntensityDataItem *item)";

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_item = item;

    if (!m_item) return;

    plotItem(m_item);

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));

}

// returns string containing bin content information
QString ColorMapPlot::getStatusString()
{
    qDebug() << "ColorMapPlot::getStatusString()";
    QString result;
    if(m_posData.valid) {
        result = QString(" [X: %1, Y: %2]    [binx: %3, biny:%4]    [value: %5]")
                .arg(QString::number(m_posData.m_xPos, 'f', 4))
                .arg(QString::number(m_posData.m_yPos, 'f', 4), 2)
                .arg(m_posData.key, 2)
                .arg(m_posData.value, 2)
                .arg(QString::number(m_posData.cellValue, 'f',2));
    }
    qDebug() << "ColorMapPlot::getStatusString()" << result;
    return result;
}

void ColorMapPlot::drawLinesOverTheMap()
{
    if(!m_customPlot->graph(0)->visible() || !m_customPlot->graph(1)->visible())
    {
        return;
    }

    QCPColorMapData *data  = m_colorMap->data();
    Q_ASSERT(data);

    //draw line over plot
    QCPRange keyRange = data->keyRange();
    QCPRange valueRange = data->valueRange();

    int keySize = data->keySize();
    int valueSize = data->valueSize();

    double fraction = (keyRange.upper-keyRange.lower)/keySize;

    QVector<double> x1(keySize+1), y1(valueSize+1);
    for(int i=0;i<x1.size();i++)
    {
        x1[i] = keyRange.lower + (i*fraction);
        y1[i] = m_posData.m_yPos;

        //qDebug() << "Line draw1: X:" << x1[i] << " Y:" << y1[i];
    }
    m_customPlot->graph(0)->setData(x1, y1);

    //draw vertical line

    fraction = (valueRange.upper-valueRange.lower)/valueSize;

    QVector<double> x2(valueSize+1), y2(keySize+1);
    for(int i=0;i<x2.size();i++)
    {
        x2[i] = m_posData.m_xPos;
        y2[i] = valueRange.lower+(i*fraction);

        //qDebug() << "Line draw2: X:" << x2[i] << " Y:" << y2[i];
    }
    m_customPlot->graph(1)->setData(x2, y2);

    //replot the graph
    m_customPlot->replot();
}

void ColorMapPlot::showLinesOverTheMap(bool isVisible)
{
    if(m_customPlot->graph(0) && m_customPlot->graph(1))
    {
        m_customPlot->graph(0)->setVisible(isVisible);
        m_customPlot->graph(1)->setVisible(isVisible);
        m_customPlot->replot();
    }
}

void ColorMapPlot::setLogz(bool logz, bool isReplot)
{
    if(logz) {
        m_colorScale->setDataScaleType(QCPAxis::stLogarithmic);
        m_colorScale->axis()->setNumberFormat("eb");
        m_colorScale->axis()->setNumberPrecision(0);
    } else {
        m_colorScale->axis()->setNumberFormat("f");
        m_colorScale->setDataScaleType(QCPAxis::stLinear);
    }
    if(isReplot)
        m_customPlot->replot();
}

void ColorMapPlot::resetView()
{
    m_block_update = true;
    qDebug() << "ColorMapPlot::resetView()";
    m_colorMap->rescaleAxes();


    QCPRange newDataRange = calculateDataRange(m_item);
    qDebug() << "XXX " << newDataRange.lower << newDataRange.upper;
    m_colorMap->setDataRange(newDataRange);
//    m_colorScale->setDataRange(newDataRange);


    m_customPlot->replot();
    m_block_update = false;
}


// saves information about mouse position and intensity data underneath
void ColorMapPlot::onMouseMove(QMouseEvent *event)
{
    qDebug() << "ColorMapPlot::onMouseMove(QMouseEvent *event)";
    m_posData.reset();

    QPoint point = event->pos();
    double xPos = m_customPlot->xAxis->pixelToCoord(point.x());
    double yPos = m_customPlot->yAxis->pixelToCoord(point.y());

    if(m_customPlot->xAxis->range().contains(xPos) && m_customPlot->yAxis->range().contains(yPos)) {
        m_posData.valid = true;
        m_posData.m_xPos = xPos;
        m_posData.m_yPos = yPos;
        QCPColorMapData * data  = m_colorMap->data();
        data->coordToCell(xPos, yPos, &m_posData.key, &m_posData.value);
        m_posData.cellValue = data->cell(m_posData.key, m_posData.value);
        emit validMousMove();
    }
}

// returns vectors corresponding to the cut along x-axis
void ColorMapPlot::getHorizontalSlice(QVector<double> &x, QVector<double> &y)
{
    x.clear();
    y.clear();

    QCPColorMapData * data  = m_colorMap->data();
    QCPRange range = data->keyRange();
    int keySize = data->keySize();
    int valueSize = data->valueSize();

    x.resize(keySize);
    y.resize(keySize);

    double fraction = (range.upper-range.lower)/keySize;

    for(int i=0; i<x.size(); ++i) {
        x[i] =  range.lower + (i*fraction);

        if(m_posData.value>=0 && m_posData.value<valueSize) {
            y[i] = data->cell(i, m_posData.value);
        } else {
            y[i] = 0;
        }
    }
}

void ColorMapPlot::getVerticalSlice(QVector<double> &x, QVector<double> &y)
{
    x.clear();
    y.clear();

    QCPColorMapData * data  = m_colorMap->data();
    QCPRange range = data->valueRange();
    int keySize = data->keySize();
    int valueSize = data->valueSize();

    x.resize(valueSize);
    y.resize(valueSize);

    double fraction = (range.upper-range.lower)/valueSize;

    for(int i=0; i<x.size(); ++i) {
        x[i] =  range.lower + (i*fraction);

        if(m_posData.key>=0 && m_posData.key< keySize) {
             y[i] = data->cell(m_posData.key, i);
        } else {
            y[i] = 0;
        }
    }
}

void ColorMapPlot::onPropertyChanged(const QString &property_name)
{
    qDebug() << "ColorMapPlot::onPropertyChanged(const QString &property_name)" << property_name;
    if(m_block_update) return;

    if(property_name == NIntensityDataItem::P_GRADIENT) {
        qDebug() << "XXX" << m_gradient_map.size() << m_item->getGradient();
        m_colorMap->setGradient(m_gradient_map[m_item->getGradient()]);
        m_customPlot->replot();
    } else if(property_name == NIntensityDataItem::P_IS_LOGZ) {
        setLogz(m_item->isLogz());
    } else if(property_name == NIntensityDataItem::P_IS_INTERPOLATED) {
        m_colorMap->setInterpolate(m_item->isInterpolated());
        m_customPlot->replot();
    } else if(property_name == NIntensityDataItem::P_ZAXIS_MIN) {
        QCPRange range = m_colorMap->dataRange();
        double zmin = m_item->getZaxisMin();
        if(zmin != range.lower) {
            range.lower = zmin;
            m_colorMap->setDataRange(range);
            m_customPlot->replot();
        }
    } else if(property_name == NIntensityDataItem::P_ZAXIS_MAX) {
        QCPRange range = m_colorMap->dataRange();
        double zmax = m_item->getZaxisMax();
        if(zmax != range.upper) {
            range.upper = zmax;
            m_colorMap->setDataRange(range);
            m_customPlot->replot();
        }
    } else if(property_name == NIntensityDataItem::P_PROJECTIONS_FLAG) {
        showLinesOverTheMap(m_item->getRegisteredProperty(NIntensityDataItem::P_PROJECTIONS_FLAG).toBool());
    }
}

void ColorMapPlot::onDataRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setZaxisRange(newRange.lower, newRange.upper);
    m_block_update = false;
}

void ColorMapPlot::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setXaxisMin(newRange.lower);
    m_item->setXaxisMax(newRange.upper);
    m_block_update = false;
}

void ColorMapPlot::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setYaxisMin(newRange.lower);
    m_item->setYaxisMax(newRange.upper);
    m_block_update = false;
}


void ColorMapPlot::initColorMap()
{
    m_customPlot = new QCustomPlot();

    m_colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(m_colorMap);
    m_colorScale = new QCPColorScale(m_customPlot);
    m_customPlot->plotLayout()->addElement(0, 1, m_colorScale); // add it to the right of the main axis rect

    m_colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    m_colorMap->setColorScale(m_colorScale); // associate the color map with the color scale

    m_gradient_map[Constants::GRADIENT_GRAYSCALE] = QCPColorGradient::gpGrayscale;
    m_gradient_map[Constants::GRADIENT_HOT] = QCPColorGradient::gpHot;
    m_gradient_map[Constants::GRADIENT_COLD] = QCPColorGradient::gpCold;
    m_gradient_map[Constants::GRADIENT_NIGHT] = QCPColorGradient::gpNight;
    m_gradient_map[Constants::GRADIENT_CANDY] = QCPColorGradient::gpCandy;
    m_gradient_map[Constants::GRADIENT_GEOGRAPHY] = QCPColorGradient::gpGeography;
    m_gradient_map[Constants::GRADIENT_ION] = QCPColorGradient::gpIon;
    m_gradient_map[Constants::GRADIENT_THERMAL] = QCPColorGradient::gpThermal;
    m_gradient_map[Constants::GRADIENT_POLAR] = QCPColorGradient::gpPolar;
    m_gradient_map[Constants::GRADIENT_SPECTRUM] = QCPColorGradient::gpSpectrum;
    m_gradient_map[Constants::GRADIENT_JET] = QCPColorGradient::gpJet;
    m_gradient_map[Constants::GRADIENT_HUES] = QCPColorGradient::gpHues;


    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255, 130));
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(pen);
    m_customPlot->addGraph();
    m_customPlot->graph(1)->setPen(pen);

    connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(onDataRangeChanged(QCPRange)));
    connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXaxisRangeChanged(QCPRange)));
    connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onYaxisRangeChanged(QCPRange)));
    connect(m_customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
//    connect(m_customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SIGNAL(mouseMove(QMouseEvent*)));
}

void ColorMapPlot::plotItem(NIntensityDataItem *intensityItem)
{
    m_block_update = true;
    qDebug() << "ColorMapPlot::updateItem(NIntensityDataItem *intensityItem)";
    Q_ASSERT(intensityItem);

    const OutputData<double> *data = intensityItem->getOutputData();
    Q_ASSERT(data);

    if(data->getRank() != 2) {
        throw NullPointerException("ColorMapPlot::plotItem() -> Error. Zero pointer to the data to draw");
    }

    m_customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    m_customPlot->axisRect()->setupFullAxesBox(true);
    m_customPlot->xAxis->setLabel(intensityItem->getXaxisTitle());
    m_customPlot->yAxis->setLabel(intensityItem->getYaxisTitle());

    const IAxis *axis_x = data->getAxis(0);
    const IAxis *axis_y = data->getAxis(1);

    int nx = axis_x->getSize();
    int ny = axis_y->getSize();
    m_colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    if(intensityItem->axesInRadians()) {
        m_colorMap->data()->setRange(QCPRange(axis_x->getMin(), axis_x->getMax()), QCPRange(axis_y->getMin(), axis_y->getMax()));
    } else {
        m_colorMap->data()->setRange(QCPRange(Units::rad2deg(axis_x->getMin()), Units::rad2deg(axis_x->getMax())), QCPRange(Units::rad2deg(axis_y->getMin()), Units::rad2deg(axis_y->getMax())));
    }

    OutputData<double>::const_iterator it = data->begin();
    while (it != data->end()) {
        std::vector<int> indices =
                data->toCoordinates(it.getIndex());

        m_colorMap->data()->setCell(indices[0], indices[1], *it);

        ++it;
    }

    setLogz(intensityItem->isLogz(), false);

    m_colorMap->setGradient(m_gradient_map[intensityItem->getGradient()]);

    QCPRange newDataRange = calculateDataRange(intensityItem);
    m_colorMap->setDataRange(newDataRange);
    intensityItem->setZaxisRange(newDataRange.lower, newDataRange.upper);

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    m_customPlot->rescaleAxes();

    m_customPlot->replot();
    m_block_update = false;
}

QCPRange ColorMapPlot::calculateDataRange(NIntensityDataItem *intensityItem)
{
    const OutputData<double> *data = intensityItem->getOutputData();
    OutputData<double>::const_iterator it_max = std::max_element(data->begin(), data->end());
    OutputData<double>::const_iterator it_min = std::min_element(data->begin(), data->end());
    double min(*it_min), max(*it_max);
    if(intensityItem->isLogz()) {
        if(max>10000) {
            min = 1.0;
            max = max*1.1;
        } else {
            min = max/10000;
            max = max*1.1;
        }
    } else {
        max = max*1.1;
    }
    return QCPRange(min, max);
}

