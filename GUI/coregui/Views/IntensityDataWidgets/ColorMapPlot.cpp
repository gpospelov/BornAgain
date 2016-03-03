// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/ColorMapPlot.cpp
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
#include "IntensityDataItem.h"
#include "AxesItems.h"
#include "GUIHelpers.h"
#include "Units.h"
#include <QDebug>

ColorMapPlot::ColorMapPlot(QWidget *parent)
    : QWidget(parent), m_customPlot(0), m_colorMap(0), m_colorScale(0), m_item(0),
      m_block_update(true)
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

//! initializes everything with new IntensityDataItem or plot it, if it was already the case
void ColorMapPlot::setItem(IntensityDataItem *item)
{
    if (item && (m_item == item)) {
        // qDebug() << "ColorMapPlot::setItem(NIntensityDataItem *item) item==m_item";
        plotItem(m_item);
        return;
    }

    if (m_item) {
        disconnect(m_item, SIGNAL(intensityModified()), this,
                   SLOT(onIntensityModified()));
    }

    m_item = item;

    if (!m_item)
        return;

    plotItem(m_item);

    connect(m_item, SIGNAL(intensityModified()), this,
               SLOT(onIntensityModified()));
    ModelMapper *mapper = new ModelMapper(this);
    mapper->setItem(item);
    mapper->setOnPropertyChange(
                [this](const QString &name)
    {
        onPropertyChanged(name);
    });
    mapper->setOnChildPropertyChange(
                [this](ParameterizedItem* item, const QString name)
    {
        if (item->parent() && item->parent()->modelType() == Constants::GroupItemType)
            onSubItemPropertyChanged(item->itemName(), name);
    });
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
    m_customPlot->setMouseTracking(isVisible);

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
void ColorMapPlot::setLogz(bool logz, bool isReplot)
{
    if (logz) {
        m_colorScale->setDataScaleType(QCPAxis::stLogarithmic);
        m_colorScale->axis()->setNumberFormat("eb");
        m_colorScale->axis()->setNumberPrecision(0);
    } else {
        m_colorScale->axis()->setNumberFormat("f");
        m_colorScale->axis()->setNumberPrecision(0);
        m_colorScale->setDataScaleType(QCPAxis::stLinear);
    }
    if (isReplot)
        m_customPlot->replot();
}

//! reset all axes min,max to initial value
void ColorMapPlot::resetView()
{
    m_block_update = true;
    m_colorMap->rescaleAxes();
    if(!m_item->isZAxisLocked()) {
        QCPRange newDataRange = calculateDataRange(m_item);
        m_colorMap->setDataRange(newDataRange);
    }
    m_customPlot->replot();
    m_block_update = false;
}

//! saves information about mouse position and intensity data underneath
void ColorMapPlot::onMouseMove(QMouseEvent *event)
{
    m_posData.reset();
    QPoint point = event->pos();
    double xPos = m_customPlot->xAxis->pixelToCoord(point.x());
    double yPos = m_customPlot->yAxis->pixelToCoord(point.y());

//    qDebug() << "AAA ColorMapPlot::onMouseMove() " << point << "xpos:" << xPos << "yPos:" << yPos;

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
    qDebug() << "ColorMapPlot::onIntensityModified()";
    plotItem(m_item);
}

//! updates color map depending on  IntensityDataItem properties
void ColorMapPlot::onPropertyChanged(const QString &property_name)
{
    if (m_block_update)
        return;

    if (property_name == IntensityDataItem::P_GRADIENT) {
        m_colorMap->setGradient(m_gradient_map[m_item->getGradient()]);
        m_customPlot->replot();
    } else if (property_name == IntensityDataItem::P_IS_INTERPOLATED) {
        m_colorMap->setInterpolate(m_item->isInterpolated());
        m_customPlot->replot();
    } else if (property_name == IntensityDataItem::P_PROJECTIONS_FLAG) {
        showLinesOverTheMap(
            m_item->getRegisteredProperty(IntensityDataItem::P_PROJECTIONS_FLAG).toBool());
    }
}

void ColorMapPlot::onSubItemPropertyChanged(const QString &property_group,
                                            const QString &property_name)
{
    if (m_block_update)
        return;

    qDebug() << "ColorMapPlot::onSubItemPropertyChanged(const QString &property_name)"
             << property_group << property_name;
    if (property_group == IntensityDataItem::P_XAXIS) {
        if (property_name == BasicAxisItem::P_MIN) {
            QCPRange range = m_customPlot->xAxis->range();
            range.lower = m_item->getLowerX();
            m_customPlot->xAxis->setRange(range);
        } else if (property_name == BasicAxisItem::P_MAX) {
            QCPRange range = m_customPlot->xAxis->range();
            range.upper = m_item->getUpperX();
            m_customPlot->xAxis->setRange(range);
        } else if (property_name == BasicAxisItem::P_TITLE) {
            m_customPlot->xAxis->setLabel(m_item->getXaxisTitle());
        }
        m_customPlot->replot();
    } else if (property_group == IntensityDataItem::P_YAXIS) {
        if (property_name == BasicAxisItem::P_MIN) {
            QCPRange range = m_customPlot->yAxis->range();
            range.lower = m_item->getLowerY();
            m_customPlot->yAxis->setRange(range);
        } else if (property_name == BasicAxisItem::P_MAX) {
            QCPRange range = m_customPlot->yAxis->range();
            range.upper = m_item->getUpperY();
            m_customPlot->yAxis->setRange(range);
        } else if (property_name == BasicAxisItem::P_TITLE) {
            m_customPlot->yAxis->setLabel(m_item->getYaxisTitle());
        }
        m_customPlot->replot();
    }

    else if (property_group == IntensityDataItem::P_ZAXIS) {
        if (property_name == BasicAxisItem::P_MIN) {
            QCPRange range = m_colorMap->dataRange();
            double zmin = m_item->getLowerZ();
            if (zmin != range.lower) {
                range.lower = zmin;
                m_colorMap->setDataRange(range);
            }
        } else if (property_name == BasicAxisItem::P_MAX) {
            QCPRange range = m_colorMap->dataRange();
            double zmax = m_item->getUpperZ();
            if (zmax != range.upper) {
                range.upper = zmax;
                m_colorMap->setDataRange(range);
                m_customPlot->replot();
            }
        } else if (property_name == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(m_item->isLogz());

        } else if (property_name == BasicAxisItem::P_IS_VISIBLE) {
            setColorScaleVisible(m_item->getGroupItem(IntensityDataItem::P_ZAXIS)
                ->getRegisteredProperty(BasicAxisItem::P_IS_VISIBLE).toBool());
        }
        m_customPlot->replot();
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

//! creates and initializes the color map
void ColorMapPlot::initColorMap()
{
    m_customPlot = new QCustomPlot();

//    m_customPlot->axisRect()->setAutoMargins(QCP::msNone);
//    m_customPlot->axisRect()->setMargins(QMargins(0.1, 0.1, 0.1, 0.1));

    m_colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(m_colorMap);
    m_colorScale = new QCPColorScale(m_customPlot);

//    QFontMetrics fontMetric(font());
//    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
//    auto *axisRectangle = m_colorScale->axis()->axisRect();
//    axisRectangle->setMargins(QMargins(0.0*em, fontAscent*1.0, em*5.0, em));
////    axisRectangle->setAutoMargins(QCP::msNone);
//    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
////    axisRectangle->setMargins(QMargins(1.0*em, fontAscent, em, 1.0*fontAscent));


//    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
//    m_colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
//    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);


    m_customPlot->plotLayout()->addElement(
        0, 1, m_colorScale); // add it to the right of the main axis rect

    m_colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels
                                             // right (actually atRight is already the default)
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

    connect(m_colorMap, SIGNAL(dataRangeChanged(QCPRange)), this,
            SLOT(onDataRangeChanged(QCPRange)));
    connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
            SLOT(onXaxisRangeChanged(QCPRange)));
    connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this,
            SLOT(onYaxisRangeChanged(QCPRange)));
    connect(m_customPlot, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(onMouseMove(QMouseEvent *)));
}

//! plot IntensityDataItem
void ColorMapPlot::plotItem(IntensityDataItem *intensityItem)
{
    m_block_update = true;
    Q_ASSERT(intensityItem == m_item);

    const OutputData<double> *data = intensityItem->getOutputData();
    // Q_ASSERT(data);
    if (!data)
        return;

    if (data->getRank() != 2) {
        throw NullPointerException(
            "ColorMapPlot::plotItem() -> Error. Zero pointer to the data to draw");
    }

    m_customPlot->setInteractions(
        QCP::iRangeDrag
        | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    m_customPlot->axisRect()->setupFullAxesBox(true);

    m_customPlot->xAxis->setLabel(intensityItem->getXaxisTitle());
    m_customPlot->yAxis->setLabel(intensityItem->getYaxisTitle());

    const IAxis *axis_x = data->getAxis(0);
    const IAxis *axis_y = data->getAxis(1);

    int nx = axis_x->getSize();
    int ny = axis_y->getSize();
    m_colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points

    m_colorMap->data()->setRange(QCPRange(intensityItem->getXmin(), intensityItem->getXmax()),
                                 QCPRange(intensityItem->getYmin(), intensityItem->getYmax()));

    OutputData<double>::const_iterator it = data->begin();
    while (it != data->end()) {
        std::vector<int> indices = data->getAxesBinIndices(it.getIndex());

        m_colorMap->data()->setCell(indices[0], indices[1], *it);

        ++it;
    }

    setColorScaleVisible(intensityItem->getGroupItem(IntensityDataItem::P_ZAXIS)
        ->getRegisteredProperty(BasicAxisItem::P_IS_VISIBLE).toBool());

    m_colorMap->setGradient(m_gradient_map[intensityItem->getGradient()]);

    QCPRange newDataRange(intensityItem->getLowerZ(), intensityItem->getUpperZ());
    if (!intensityItem->isZAxisLocked() || (intensityItem->getLowerZ() > intensityItem->getUpperZ())) {
        newDataRange = calculateDataRange(intensityItem);
        m_colorMap->setDataRange(newDataRange);
        intensityItem->setLowerAndUpperZ(newDataRange.lower, newDataRange.upper);
    }

    m_colorMap->setDataRange(newDataRange);
    setLogz(intensityItem->isLogz(), false);

    m_colorMap->setInterpolate(m_item->isInterpolated());

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they
    // line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    m_colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    //    m_customPlot->rescaleAxes();

    m_customPlot->xAxis->setRange(intensityItem->getLowerX(), intensityItem->getUpperX());
    m_customPlot->yAxis->setRange(intensityItem->getLowerY(), intensityItem->getUpperY());

    m_customPlot->replot();
    m_block_update = false;
}

//! calculate zmin, zmax for nicely looking linear, and logariphic z-axis
QCPRange ColorMapPlot::calculateDataRange(IntensityDataItem *intensityItem)
{
    const OutputData<double> *data = intensityItem->getOutputData();
    OutputData<double>::const_iterator it_max = std::max_element(data->begin(), data->end());
    OutputData<double>::const_iterator it_min = std::min_element(data->begin(), data->end());
    double min(*it_min), max(*it_max);
    if (intensityItem->isLogz()) {
        if (max > 10000) {
            min = 1.0;
            max = max * 1.1;
        } else {
            min = max / 10000;
            max = max * 1.1;
        }
    } else {
        max = max * 1.1;
    }
    return QCPRange(min, max);
}

void ColorMapPlot::setColorScaleVisible(bool visibility_flag)
{
    m_colorScale->setVisible(visibility_flag);
    if(visibility_flag) {
        m_customPlot->plotLayout()->addElement(
            0, 1, m_colorScale); // add it to the right of the main axis rect
    } else {
        m_customPlot->plotLayout()->take(m_colorScale);
        m_customPlot->plotLayout()->simplify();

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
