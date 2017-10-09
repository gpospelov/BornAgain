// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMap.cpp
//! @brief     Implements class ColorMap
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMap.h"
#include "AxesItems.h"
#include "ColorMapEvent.h"
#include "ColorMapUtils.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "MathConstants.h"
#include "UpdateTimer.h"
#include "plot_constants.h"

namespace {
const int replot_update_interval = 10;
}

ColorMap::ColorMap(QWidget* parent)
    : SessionItemWidget(parent)
    , m_customPlot(new QCustomPlot)
    , m_colorMap(nullptr), m_colorScale(nullptr)
    , m_updateTimer(new UpdateTimer(replot_update_interval, this))
    , m_colorMapEvent(new ColorMapEvent(this))
    , m_block_update(true)
{
    initColorMap();

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

    setMouseTrackingEnabled(true);
    //    setFixedColorMapMargins();
}

double ColorMap::xAxisCoordToPixel(double axis_coordinate) const
{
    return m_customPlot->xAxis->coordToPixel(axis_coordinate);
}

double ColorMap::yAxisCoordToPixel(double axis_coordinate) const
{
    return m_customPlot->yAxis->coordToPixel(axis_coordinate);
}

double ColorMap::pixelToXaxisCoord(double pixel) const
{
    return m_customPlot->xAxis->pixelToCoord(pixel);
}

double ColorMap::pixelToYaxisCoord(double pixel) const
{
    return m_customPlot->yAxis->pixelToCoord(pixel);
}

QRectF ColorMap::viewportRectangleInWidgetCoordinates()
{
    QCPRange xrange = m_customPlot->xAxis->range();
    QCPRange yrange = m_customPlot->yAxis->range();
    double left = xrange.lower;
    double right = xrange.upper;
    double top = yrange.upper;
    double bottom = yrange.lower;

    return QRectF(xAxisCoordToPixel(left), yAxisCoordToPixel(top),
                  xAxisCoordToPixel(right) - xAxisCoordToPixel(left),
                  yAxisCoordToPixel(bottom) - yAxisCoordToPixel(top));
}

bool ColorMap::axesRangeContains(double xpos, double ypos) const
{
    if (customPlot()->xAxis->range().contains(xpos)
        && customPlot()->yAxis->range().contains(ypos)) {
        return true;
    }
    return false;
}

ColorMapBin ColorMap::colorMapBin(double xpos, double ypos) const
{
    ColorMapBin result;

    result.m_x = xpos;
    result.m_y = ypos;

    if (axesRangeContains(xpos, ypos))
        result.in_axes_range = true;

    m_colorMap->data()->coordToCell(xpos, ypos, &result.m_nx, &result.m_ny);
    result.m_value = m_colorMap->data()->cell(result.m_nx, result.m_ny);

    return result;
}

//! to track move events (used when showing profile histograms and printing status string)

void ColorMap::setMouseTrackingEnabled(bool enable)
{
    m_colorMapEvent->setMouseTrackingEnabled(enable);
}

//! sets logarithmic scale
void ColorMap::setLogz(bool logz)
{
    ColorMapUtils::setLogz(m_colorScale, logz);
}

//! reset all axes min,max to initial value
void ColorMap::resetView()
{
    intensityItem()->resetView();
}

void ColorMap::onIntensityModified()
{
    setAxesRangeFromItem(intensityItem());
    setDataFromItem(intensityItem());
    replot();
}

//! updates color map depending on  IntensityDataItem properties
void ColorMap::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == IntensityDataItem::P_GRADIENT) {
        m_colorMap->setGradient(ColorMapUtils::itemGradient(intensityItem()));
        replot();
    } else if (property_name == IntensityDataItem::P_IS_INTERPOLATED) {
        m_colorMap->setInterpolate(intensityItem()->isInterpolated());
        replot();
    } else if (property_name == IntensityDataItem::P_AXES_UNITS) {
        setAxesRangeFromItem(intensityItem());
        replot();
    }
}

void ColorMap::onAxisPropertyChanged(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE  ||
        propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(intensityItem());
        replot();
    }

    if (axisName == IntensityDataItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_customPlot->xAxis->setRange(ColorMapUtils::itemZoomX(intensityItem()));
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == IntensityDataItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_customPlot->yAxis->setRange(ColorMapUtils::itemZoomY(intensityItem()));
            setAxesRangeConnected(true);
            replot();
        }
    }

    else if (axisName == IntensityDataItem::P_ZAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setDataRangeFromItem(intensityItem());
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(intensityItem()->isLogz());
            replot();

        } else if (propertyName == BasicAxisItem::P_IS_VISIBLE) {
            setColorScaleVisible(intensityItem()
                                     ->getItem(IntensityDataItem::P_ZAXIS)
                                     ->getItemValue(BasicAxisItem::P_IS_VISIBLE)
                                     .toBool());
            replot();
        }
    }
}

//! Propagate zmin, zmax back to IntensityDataItem
void ColorMap::onDataRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerAndUpperZ(newRange.lower, newRange.upper);
    m_block_update = false;
}

//! Propagate xmin, xmax back to IntensityDataItem
void ColorMap::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerX(newRange.lower);
    intensityItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

//! Propagate ymin, ymax back to IntensityDataItem
void ColorMap::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    intensityItem()->setLowerY(newRange.lower);
    intensityItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

//! Schedule replot for later execution by onTimeReplot() slot.

void ColorMap::replot()
{
    m_updateTimer->scheduleUpdate();
}

//! Replots ColorMap.

void ColorMap::onTimeToReplot()
{
    m_customPlot->replot();
}

void ColorMap::subscribeToItem()
{
    setColorMapFromItem(intensityItem());

    intensityItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    intensityItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if(item->modelType() == Constants::BasicAxisType ||
               item->modelType() == Constants::AmplitudeAxisType)
                onAxisPropertyChanged(item->itemName(), name);
        },
        this);

    intensityItem()->mapper()->setOnValueChange([this]() { onIntensityModified(); }, this);

    setConnected(true);
}

void ColorMap::unsubscribeFromItem()
{
    setConnected(false);
}

//! creates and initializes the color map
void ColorMap::initColorMap()
{
    m_colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_colorScale = new QCPColorScale(m_customPlot);
    m_colorMap->setColorScale(m_colorScale);

    m_colorScale->setBarWidth(Constants::plot_colorbar_size);
    m_colorScale->axis()->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

    connect(m_customPlot, SIGNAL(afterReplot()), this, SLOT(marginsChangedNotify()));
}

void ColorMap::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setDataRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

//! Connects/disconnects signals related to ColorMap's X,Y axes rectangle change.

void ColorMap::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
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

void ColorMap::setDataRangeConnected(bool isConnected)
{
    if (isConnected)
        connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                SLOT(onDataRangeChanged(QCPRange)), Qt::UniqueConnection);
    else
        disconnect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
                   SLOT(onDataRangeChanged(QCPRange)));
}

void ColorMap::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()),
                Qt::UniqueConnection);
    else
        disconnect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(onTimeToReplot()));
}

//! to make fixed margins for whole colormap (change in axes labels wont affect axes rectangle)
void ColorMap::setFixedColorMapMargins()
{
    QFontMetrics fontMetric(font());
    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
    auto* axisRectangle = m_customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(QMargins(6.0 * em, fontAscent * 1.5, em * 1.2, 4.5 * fontAscent));
}

//! Sets initial state of ColorMap to match given intensity item.

void ColorMap::setColorMapFromItem(IntensityDataItem* intensityItem)
{
    Q_ASSERT(intensityItem);

    m_block_update = true;

    setAxesRangeFromItem(intensityItem);
    setAxesZoomFromItem(intensityItem);
    setAxesLabelsFromItem(intensityItem);
    setDataFromItem(intensityItem);
    setColorScaleAppearanceFromItem(intensityItem);
    setDataRangeFromItem(intensityItem);

    replot();

    m_block_update = false;
}

//! Sets (xmin,xmax,nbins) and (ymin,ymax,nbins) of ColorMap from intensity item.

void ColorMap::setAxesRangeFromItem(IntensityDataItem* item)
{
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_customPlot->axisRect()->setupFullAxesBox(true);
    m_colorMap->data()->setSize(item->getNbinsX(), item->getNbinsY());
    m_colorMap->data()->setRange(ColorMapUtils::itemXrange(item), ColorMapUtils::itemYrange(item));
}

//! Sets zoom range of X,Y axes as in intensity item.

void ColorMap::setAxesZoomFromItem(IntensityDataItem* item)
{
    setAxesRangeConnected(false);
    m_customPlot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_customPlot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setAxesRangeConnected(true);
}

//! Sets X,Y axes labels from item

void ColorMap::setAxesLabelsFromItem(IntensityDataItem* item)
{
    auto xaxis = item->xAxisItem();
    if(xaxis->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        m_customPlot->xAxis->setLabel(item->getXaxisTitle());
    else
        m_customPlot->xAxis->setLabel(QString());

    m_colorScale->setMargins(QMargins(0, 0, 0, 0));

    auto yaxis = item->yAxisItem();
    if(yaxis->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        m_customPlot->yAxis->setLabel(item->getYaxisTitle());
    else
        m_customPlot->yAxis->setLabel(QString());

}

//! Sets the intensity values to ColorMap.

void ColorMap::setDataFromItem(IntensityDataItem* item)
{
    auto data = item->getOutputData();
    if (!data)
        return;

    int nx(item->getNbinsX()); // outside of the loop because of slow retrieval
    int ny(item->getNbinsY());
    for (int ix = 0; ix < nx; ++ix)
        for (int iy = 0; iy < ny; ++iy)
            m_colorMap->data()->setCell(ix, iy, (*data)[iy + ny * ix]);
}

//! Sets the appearance of color scale (visibility, gradient type) from intensity item.

void ColorMap::setColorScaleAppearanceFromItem(IntensityDataItem* item)
{
    setColorScaleVisible(item->getItem(IntensityDataItem::P_ZAXIS)
                             ->getItemValue(BasicAxisItem::P_IS_VISIBLE)
                             .toBool());
    m_colorMap->setGradient(ColorMapUtils::itemGradient(intensityItem()));
    m_colorMap->setInterpolate(intensityItem()->isInterpolated());
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they
    // line up):
    QCPMarginGroup* marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
}

void ColorMap::setDataRangeFromItem(IntensityDataItem* item)
{
    setDataRangeConnected(false);
    m_colorMap->setDataRange(ColorMapUtils::itemDataZoom(item));
    setLogz(item->isLogz());
    setDataRangeConnected(true);
}

void ColorMap::setColorScaleVisible(bool visibility_flag)
{
    m_colorScale->setVisible(visibility_flag);
    if (visibility_flag) {
        // add it to the right of the main axis rect
        m_customPlot->plotLayout()->addElement(0, 1, m_colorScale);
    } else {
        m_customPlot->plotLayout()->take(m_colorScale);
        m_customPlot->plotLayout()->simplify();
    }
}

//! Calculates left, right margins around color map to report to projection plot.

void ColorMap::marginsChangedNotify()
{
    QMargins axesMargins = m_customPlot->axisRect()->margins();
    QMargins colorBarMargins = m_colorScale->margins();
    QMargins colorScaleMargins = m_colorScale->axis()->axisRect()->margins();

    double left = axesMargins.left();
    double right = axesMargins.right() + colorBarMargins.right() + m_colorScale->barWidth()
            + colorScaleMargins.right();

    emit marginsChanged(left, right);
}

IntensityDataItem* ColorMap::intensityItem()
{
    return dynamic_cast<IntensityDataItem*>(currentItem());
}
