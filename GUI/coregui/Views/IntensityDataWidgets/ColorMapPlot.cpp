// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapPlot.cpp
//! @brief     Implements class ColorMapPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapPlot.h"
#include "AxesItems.h"
#include "ColorMapHelper.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "MathConstants.h"
#include "UpdateTimer.h"
#include <QDebug>

namespace {
const int replot_update_interval = 10;
}

ColorMapPlot::ColorMapPlot(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
    , m_colorMap(0)
    , m_colorScale(0)
    , m_item(0)
    , m_block_update(true)
    , m_updateTimer(new UpdateTimer(replot_update_interval, this))
{
    initColorMap();

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
    setMouseTracking(false);
    m_customPlot->setMouseTracking(false);

    //    setFixedColorMapMargins();
}

ColorMapPlot::~ColorMapPlot()
{
    if(m_item)
        m_item->mapper()->unsubscribe(this);

}

//! Sets ColorMap to track intensity item.

void ColorMapPlot::setItem(IntensityDataItem *item)
{
    if(item == m_item)
        return;

    resetColorMap();

    m_item = item;
    if(!m_item)
        return;

    // FIXME. ColorMapPlot should be functional, even if OutputData is zero
    if(m_item->getOutputData() == nullptr) {
        m_item = 0;
        return;
    }

    setColorMapFromItem(m_item);

    m_item->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        onPropertyChanged(name);
    }, this);

    m_item->mapper()->setOnChildPropertyChange([this](SessionItem *item, const QString name) {
        onSubItemPropertyChanged(item->itemName(), name);
    }, this);

    m_item->mapper()->setOnValueChange(
        [this]()
    {
        onIntensityModified();
    }, this);

    m_item->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_item = 0;
    }, this);

    setConnected(true);

}

//! returns string containing bin content information
QString ColorMapPlot::getStatusString()
{
    QString result;
    if (m_posData.valid) {
        result = QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                     .arg(QString::number(m_posData.m_xPos, 'f', 4))
                     .arg(QString::number(m_posData.m_yPos, 'f', 4), 2)
                     .arg(m_posData.key, 2)
                     .arg(m_posData.value, 2)
                     .arg(QString::number(m_posData.cellValue, 'f', 2));
    }
    return result;
}

//! draws two crossed lines
void ColorMapPlot::drawLinesOverTheMap()
{
    if (!m_customPlot->graph(0)->visible() || !m_customPlot->graph(1)->visible())
        return;

    QCPColorMapData *data = m_colorMap->data();
    Q_ASSERT(data);

    // draw line over plot
    QCPRange keyRange = data->keyRange();
    QCPRange valueRange = data->valueRange();

    int keySize = data->keySize();
    int valueSize = data->valueSize();

    double fraction = (keyRange.upper - keyRange.lower) / keySize;

    QVector<double> x1(keySize + 1), y1(keySize + 1);
    for (int i = 0; i < x1.size(); i++) {
        x1[i] = keyRange.lower + (i * fraction);
        y1[i] = m_posData.m_yPos;
    }
    m_customPlot->graph(0)->setData(x1, y1);

    // draw vertical line
    fraction = (valueRange.upper - valueRange.lower) / valueSize;

    QVector<double> x2(valueSize + 1), y2(valueSize + 1);
    for (int i = 0; i < x2.size(); i++) {
        x2[i] = m_posData.m_xPos;
        y2[i] = valueRange.lower + (i * fraction);
    }
    m_customPlot->graph(1)->setData(x2, y2);

    m_customPlot->replot();
}

//! switches visibility of two crossed lines
void ColorMapPlot::showLinesOverTheMap(bool isVisible)
{
    if (m_customPlot->graph(0) && m_customPlot->graph(1)) {
        m_customPlot->graph(0)->setVisible(isVisible);
        m_customPlot->graph(1)->setVisible(isVisible);
        m_customPlot->replot();
    }
}

double ColorMapPlot::xAxisCoordToPixel(double axis_coordinate) const
{
    double result = m_customPlot->xAxis->coordToPixel(axis_coordinate);
//    qDebug() << "ColorMapPlot::xAxisCoordToPixel axis_coordinate:" << axis_coordinate << "result:" << result;
    return result;
}

double ColorMapPlot::yAxisCoordToPixel(double axis_coordinate) const
{
    return m_customPlot->yAxis->coordToPixel(axis_coordinate);
}

double ColorMapPlot::pixelToXaxisCoord(double pixel) const
{
    return m_customPlot->xAxis->pixelToCoord(pixel);
}

double ColorMapPlot::pixelToYaxisCoord(double pixel) const
{
    return m_customPlot->yAxis->pixelToCoord(pixel);
}

QRectF ColorMapPlot::getViewportRectangleInWidgetCoordinates()
{
    QCPRange xrange = m_customPlot->xAxis->range();
    QCPRange yrange = m_customPlot->yAxis->range();
    double left = xrange.lower;
    double right = xrange.upper;
    double top = yrange.upper;
    double bottom = yrange.lower;

    return QRectF(xAxisCoordToPixel(left),
                  yAxisCoordToPixel(top),
                  xAxisCoordToPixel(right) - xAxisCoordToPixel(left),
                  yAxisCoordToPixel(bottom) - yAxisCoordToPixel(top));
}

//! to track move events (used when showing profile histograms and printing status string)
void ColorMapPlot::setTrackMoveEventsFlag(bool flag)
{
    setMouseTracking(flag);
    m_customPlot->setMouseTracking(flag);
}

//! sets logarithmic scale
void ColorMapPlot::setLogz(bool logz)
{
    if (logz) {
        if(m_colorScale->dataScaleType() != QCPAxis::stLogarithmic) {
            m_colorScale->setDataScaleType(QCPAxis::stLogarithmic);
            m_colorScale->axis()->setNumberFormat("eb");
            m_colorScale->axis()->setNumberPrecision(0);
        }
    } else {
        if(m_colorScale->dataScaleType() != QCPAxis::stLinear) {
            m_colorScale->axis()->setNumberFormat("f");
            m_colorScale->axis()->setNumberPrecision(0);
            m_colorScale->setDataScaleType(QCPAxis::stLinear);
        }
    }
//    if (logz) {
//        m_colorScale->setDataScaleType(QCPAxis::stLogarithmic);
//        m_colorScale->axis()->setNumberFormat("eb");
//        m_colorScale->axis()->setNumberPrecision(0);
//    } else {
//        m_colorScale->axis()->setNumberFormat("f");
//        m_colorScale->axis()->setNumberPrecision(0);
//        m_colorScale->setDataScaleType(QCPAxis::stLinear);
//    }
}

//! reset all axes min,max to initial value
void ColorMapPlot::resetView()
{
    m_item->resetView();
}

//! saves information about mouse position and intensity data underneath
void ColorMapPlot::onMouseMove(QMouseEvent *event)
{
    m_posData.reset();
    QPoint point = event->pos();
    double xPos = m_customPlot->xAxis->pixelToCoord(point.x());
    double yPos = m_customPlot->yAxis->pixelToCoord(point.y());


    if (m_customPlot->xAxis->range().contains(xPos)
        && m_customPlot->yAxis->range().contains(yPos)) {
        m_posData.valid = true;
        m_posData.m_xPos = xPos;
        m_posData.m_yPos = yPos;
        QCPColorMapData *data = m_colorMap->data();
        data->coordToCell(xPos, yPos, &m_posData.key, &m_posData.value);
        m_posData.cellValue = data->cell(m_posData.key, m_posData.value);
        emit validMousMove();
    }
}

//! returns vectors corresponding to the cut along x-axis
void ColorMapPlot::getHorizontalSlice(QVector<double> &x, QVector<double> &y)
{
    x.clear();
    y.clear();

    QCPColorMapData *data = m_colorMap->data();
    QCPRange range = data->keyRange();
    int keySize = data->keySize();
    int valueSize = data->valueSize();

    x.resize(keySize);
    y.resize(keySize);

    double fraction = (range.upper - range.lower) / keySize;

    for (int i = 0; i < x.size(); ++i) {
        x[i] = range.lower + (i * fraction);

        if (m_posData.value >= 0 && m_posData.value < valueSize) {
            y[i] = data->cell(i, m_posData.value);
        } else {
            y[i] = 0;
        }
    }
}

//! returns vectors corresponding to the cut along y-axis
void ColorMapPlot::getVerticalSlice(QVector<double> &x, QVector<double> &y)
{
    x.clear();
    y.clear();

    QCPColorMapData *data = m_colorMap->data();
    QCPRange range = data->valueRange();
    int keySize = data->keySize();
    int valueSize = data->valueSize();

    x.resize(valueSize);
    y.resize(valueSize);

    double fraction = (range.upper - range.lower) / valueSize;

    for (int i = 0; i < x.size(); ++i) {
        x[i] = range.lower + (i * fraction);

        if (m_posData.key >= 0 && m_posData.key < keySize) {
            y[i] = data->cell(m_posData.key, i);
        } else {
            y[i] = 0;
        }
    }
}

void ColorMapPlot::onIntensityModified()
{
    setDataFromItem(m_item);
    replot();
}

//! updates color map depending on  IntensityDataItem properties
void ColorMapPlot::onPropertyChanged(const QString &property_name)
{
    if (m_block_update)
        return;

    if (property_name == IntensityDataItem::P_GRADIENT) {
        m_colorMap->setGradient(ColorMapHelper::itemGradient(m_item));
        replot();
    } else if (property_name == IntensityDataItem::P_IS_INTERPOLATED) {
        m_colorMap->setInterpolate(m_item->isInterpolated());
        replot();
    } else if (property_name == IntensityDataItem::P_PROJECTIONS_FLAG) {
        showLinesOverTheMap(
            m_item->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
    } else if(property_name == IntensityDataItem::P_AXES_UNITS) {
        setAxesRangeFromItem(m_item);
        replot();
    }
}

void ColorMapPlot::onSubItemPropertyChanged(const QString &property_group,
                                            const QString &property_name)
{
    if (m_block_update)
        return;

    if (property_group == IntensityDataItem::P_XAXIS) {
        if (property_name == BasicAxisItem::P_MIN || property_name == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            QCPRange range = m_customPlot->xAxis->range();
            range.lower = m_item->getLowerX();
            range.upper = m_item->getUpperX();
            m_customPlot->xAxis->setRange(range);
            setAxesRangeConnected(true);
            replot();
        } else if (property_name == BasicAxisItem::P_TITLE) {
            m_customPlot->xAxis->setLabel(m_item->getXaxisTitle());
            m_colorScale->setMargins(QMargins(0,0,0,0));
            replot();
        }
    } else if (property_group == IntensityDataItem::P_YAXIS) {
        if (property_name == BasicAxisItem::P_MIN || property_name == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            QCPRange range = m_customPlot->yAxis->range();
            range.lower = m_item->getLowerY();
            range.upper = m_item->getUpperY();
            m_customPlot->yAxis->setRange(range);
            setAxesRangeConnected(true);
            replot();
        } else if (property_name == BasicAxisItem::P_TITLE) {
            m_customPlot->yAxis->setLabel(m_item->getYaxisTitle());
            replot();
        }
    }

    else if (property_group == IntensityDataItem::P_ZAXIS) {
        if (property_name == BasicAxisItem::P_MIN || property_name == BasicAxisItem::P_MAX) {
            setDataRangeFromItem(m_item);
            replot();
        } else if (property_name == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(m_item->isLogz());
            replot();

        } else if (property_name == BasicAxisItem::P_IS_VISIBLE) {
            setColorScaleVisible(m_item->getItem(IntensityDataItem::P_ZAXIS)
                ->getItemValue(BasicAxisItem::P_IS_VISIBLE).toBool());
            replot();
        }
    }
}

//! Propagate zmin, zmax back to IntensityDataItem
void ColorMapPlot::onDataRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setLowerAndUpperZ(newRange.lower, newRange.upper);
    m_block_update = false;
}

//! Propagate xmin, xmax back to IntensityDataItem
void ColorMapPlot::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setLowerX(newRange.lower);
    m_item->setUpperX(newRange.upper);
    m_block_update = false;
}

//! Propagate ymin, ymax back to IntensityDataItem
void ColorMapPlot::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    m_item->setLowerY(newRange.lower);
    m_item->setUpperY(newRange.upper);
    m_block_update = false;
}

//! Schedule replot for later execution by onTimeReplot() slot.

void ColorMapPlot::replot()
{
    m_updateTimer->scheduleUpdate();
//    m_customPlot->replot(); // will trigger immediate replot, seems that slower
}

//! Replots ColorMap.

void ColorMapPlot::onTimeToReplot()
{
    m_customPlot->replot();
}

//! creates and initializes the color map
void ColorMapPlot::initColorMap()
{
    m_customPlot = new QCustomPlot();

    m_colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(m_colorMap);
    m_colorScale = new QCPColorScale(m_customPlot);

    // add it to the right of the main axis rect
    m_customPlot->plotLayout()->addElement(0, 1, m_colorScale);

    // scale shall be vertical bar with tick/axis labels
    m_colorScale->setType(QCPAxis::atRight);

    m_colorMap->setColorScale(m_colorScale);

    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255, 130));
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(pen);
    m_customPlot->addGraph();
    m_customPlot->graph(1)->setPen(pen);

    //setConnected(true);
}


void ColorMapPlot::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setDataRangeConnected(isConnected);
    setMouseMoveConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

//! Connects/disconnects signals related to ColorMap's X,Y axes rectangle change.

void ColorMapPlot::setAxesRangeConnected(bool isConnected)
{
    if(isConnected) {
        connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onXaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

        connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onYaxisRangeChanged(QCPRange)), Qt::UniqueConnection);

    } else {
        disconnect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onXaxisRangeChanged(QCPRange)));

        disconnect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
                SLOT(onYaxisRangeChanged(QCPRange)));
    }
}

//! Connects/disconnects signals related to ColorMap's Z-axis (min,max) change.

void ColorMapPlot::setDataRangeConnected(bool isConnected)
{
    if(isConnected) {
        connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                SLOT(onDataRangeChanged(QCPRange)), Qt::UniqueConnection);
    } else {
        disconnect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                SLOT(onDataRangeChanged(QCPRange)));
    }
}

//! Connects/disconnects signals related to MouseMove in ColorMap

void ColorMapPlot::setMouseMoveConnected(bool isConnected)
{
    if(isConnected) {
        connect(m_customPlot, SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onMouseMove(QMouseEvent *)), Qt::UniqueConnection);

    } else {
        disconnect(m_customPlot, SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onMouseMove(QMouseEvent *)));
    }
}

void ColorMapPlot::setUpdateTimerConnected(bool isConnected)
{
    if(isConnected) {
        connect(m_updateTimer, SIGNAL(timeToUpdate()),
                this, SLOT(onTimeToReplot()), Qt::UniqueConnection);
    } else {
        disconnect(m_updateTimer, SIGNAL(timeToUpdate()),
                this, SLOT(onTimeToReplot()));
    }
}


//! to make fixed margins for whole colormap (change in axes labels wont affect axes rectangle)
void ColorMapPlot::setFixedColorMapMargins()
{
    QFontMetrics fontMetric(font());
    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
    auto *axisRectangle = m_customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(QMargins(6.0*em, fontAscent*1.5, em*1.2, 4.5*fontAscent));
}

//! Sets initial state of ColorMap to match given intensity item.

void ColorMapPlot::setColorMapFromItem(IntensityDataItem *intensityItem)
{
    Q_ASSERT(intensityItem);

    m_block_update = true;

    setAxesRangeFromItem(intensityItem);
    setAxesZoomFromItem(intensityItem);
    setLabelsFromItem(intensityItem);
    setDataFromItem(intensityItem);
    setColorScaleAppearanceFromItem(intensityItem);
    setDataRangeFromItem(intensityItem);

    replot();

    m_block_update = false;
}

//! Sets (xmin,xmax,nbins) and (ymin,ymax,nbins) of ColorMapPlot from intensity item.

void ColorMapPlot::setAxesRangeFromItem(IntensityDataItem *item)
{
    auto data = item->getOutputData();
    if(!data) return;

    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_customPlot->axisRect()->setupFullAxesBox(true);

    const IAxis &axis_x = data->getAxis(0);
    const IAxis &axis_y = data->getAxis(1);

    m_colorMap->data()->setSize(static_cast<int>(axis_x.size()),
                                static_cast<int>(axis_y.size()));

    m_colorMap->data()->setRange(ColorMapHelper::itemXrange(item),
                                 ColorMapHelper::itemYrange(item));

}

//! Sets zoom range of X,Y axes as in intensity item.

void ColorMapPlot::setAxesZoomFromItem(IntensityDataItem *item)
{
    setAxesRangeConnected(false);
    m_customPlot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_customPlot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setAxesRangeConnected(true);
}

//! Sets X,Y axes labels from item

void ColorMapPlot::setLabelsFromItem(IntensityDataItem *item)
{
    m_customPlot->xAxis->setLabel(item->getXaxisTitle());
    m_customPlot->yAxis->setLabel(item->getYaxisTitle());
}

//! Sets the intensity values to ColorMapPlot.

void ColorMapPlot::setDataFromItem(IntensityDataItem *item)
{
    auto data = item->getOutputData();
    if(!data) return;

    const IAxis &axis_x = data->getAxis(0);
    const IAxis &axis_y = data->getAxis(1);

    for(size_t ix=0; ix<axis_x.size(); ++ix) {
        for(size_t iy=0; iy<axis_y.size(); ++iy) {
            m_colorMap->data()->setCell(static_cast<int>(ix), static_cast<int>(iy),
                                        (*data)[iy+axis_y.size()*ix]);
        }
    }
}

//! Sets the appearance of color scale (visibility, gradient type) from intensity item.

void ColorMapPlot::setColorScaleAppearanceFromItem(IntensityDataItem *item)
{
    setColorScaleVisible(item->getItem(IntensityDataItem::P_ZAXIS)
        ->getItemValue(BasicAxisItem::P_IS_VISIBLE).toBool());
    m_colorMap->setGradient(ColorMapHelper::itemGradient(m_item));
    m_colorMap->setInterpolate(m_item->isInterpolated());
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they
    // line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
}

void ColorMapPlot::setDataRangeFromItem(IntensityDataItem *item)
{
    setDataRangeConnected(false);

    QCPRange newDataRange(item->getLowerZ(), item->getUpperZ());
    m_colorMap->setDataRange(newDataRange);
    setLogz(item->isLogz());

    setDataRangeConnected(true);
}


void ColorMapPlot::setColorScaleVisible(bool visibility_flag)
{
    m_colorScale->setVisible(visibility_flag);
    if(visibility_flag) {
        // add it to the right of the main axis rect
        m_customPlot->plotLayout()->addElement(0, 1, m_colorScale);
    } else {
        m_customPlot->plotLayout()->take(m_colorScale);
        m_customPlot->plotLayout()->simplify();
    }
}

//! Disconnects everything

void ColorMapPlot::resetColorMap()
{
    setConnected(false);
    if(m_item)
        m_item->mapper()->unsubscribe(this);
}

