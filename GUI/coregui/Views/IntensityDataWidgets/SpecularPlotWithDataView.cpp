// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotWithDataView.cpp
//! @brief     Implements class SpecularPlotWithDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularPlotWithDataView.h"
#include "AxesItems.h"
#include "ColorMapUtils.h"
#include "MathConstants.h"
#include "plot_constants.h"
#include "PlotEventInfo.h"
#include "SpecularDataItem.h"
#include "UpdateTimer.h"

namespace {
const int replot_update_interval = 10;

int getBin(double x, const QCPGraph* graph);
}

SpecularPlotWithDataView::SpecularPlotWithDataView(QWidget* parent)
    : ScientificPlot(parent, PLOT_TYPE::Plot1D)
    , m_custom_plot(new QCustomPlot)
    , m_update_timer(new UpdateTimer(replot_update_interval, this))
    , m_block_update(true)
{
    initPlot();

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_custom_plot);
    setLayout(vlayout);

    setMouseTrackingEnabled(true);
}

PlotEventInfo SpecularPlotWithDataView::eventInfo(double xpos, double ypos) const
{
    PlotEventInfo result(plotType());
    if (!specularItem())
        return result;

    result.setX(xpos);
    result.setValue(ypos);

    result.setInAxesRange(axesRangeContains(xpos, ypos));
    result.setNx(getBin(result.x(), m_custom_plot->graph()));

    return result;
}

void SpecularPlotWithDataView::setLog(bool log)
{
    ColorMapUtils::setLogz(m_custom_plot->yAxis, log);
    ColorMapUtils::setLogz(m_custom_plot->yAxis2, log);
}

void SpecularPlotWithDataView::resetView()
{
    specularItem()->resetView();
}

void SpecularPlotWithDataView::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == DataItem::P_AXES_UNITS) {
        setAxesRangeFromItem(specularItem());
        replot();
    }
}

void SpecularPlotWithDataView::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    specularItem()->setLowerX(newRange.lower);
    specularItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

void SpecularPlotWithDataView::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    specularItem()->setLowerY(newRange.lower);
    specularItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

void SpecularPlotWithDataView::onTimeToReplot()
{
    m_custom_plot->replot();
}

void SpecularPlotWithDataView::subscribeToItem()
{
    setPlotFromItem(specularItem());

    specularItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    specularItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if(item->modelType() == Constants::BasicAxisType ||
               item->modelType() == Constants::AmplitudeAxisType)
                modifyAxesProperties(item->itemName(), name);
        },
        this);

    specularItem()->mapper()->setOnValueChange([this]() { setPlotFromItem(this->specularItem()); },
                                               this);

    setConnected(true);
}

void SpecularPlotWithDataView::unsubscribeFromItem()
{
    setConnected(false);
}

void SpecularPlotWithDataView::initPlot()
{
    m_custom_plot->addGraph();

    QPen pen(QColor(0, 0, 255, 200));
    m_custom_plot->graph()->setLineStyle(QCPGraph::lsLine);
    m_custom_plot->graph()->setPen(pen);

    m_custom_plot->xAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));
    m_custom_plot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));
}

void SpecularPlotWithDataView::setConnected(bool isConnected)
{
    setAxesRangeConnected(isConnected);
    setUpdateTimerConnected(isConnected);
}

void SpecularPlotWithDataView::setAxesRangeConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_custom_plot->xAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &SpecularPlotWithDataView::onXaxisRangeChanged, Qt::UniqueConnection);

        connect(m_custom_plot->yAxis,
                static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                &SpecularPlotWithDataView::onYaxisRangeChanged, Qt::UniqueConnection);

    } else {
        disconnect(m_custom_plot->xAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &SpecularPlotWithDataView::onXaxisRangeChanged);

        disconnect(m_custom_plot->yAxis,
                   static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), this,
                   &SpecularPlotWithDataView::onYaxisRangeChanged);
    }
}

void SpecularPlotWithDataView::setUpdateTimerConnected(bool isConnected)
{
    if (isConnected)
        connect(m_update_timer, &UpdateTimer::timeToUpdate, this, &SpecularPlotWithDataView::onTimeToReplot,
                Qt::UniqueConnection);
    else
        disconnect(m_update_timer, &UpdateTimer::timeToUpdate, this, &SpecularPlotWithDataView::onTimeToReplot);
}

void SpecularPlotWithDataView::setPlotFromItem(SpecularDataItem* specularItem)
{
    Q_ASSERT(specularItem);

    m_block_update = true;

    m_custom_plot->graph(0)->data()->clear();
    setAxesRangeFromItem(specularItem);
    setAxesLabelsFromItem(specularItem);
    setDataFromItem(specularItem);

    replot();

    m_block_update = false;
}

void SpecularPlotWithDataView::setAxesRangeFromItem(SpecularDataItem* item)
{
    m_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_custom_plot->axisRect()->setupFullAxesBox(true);

    setAxesRangeConnected(false);
    m_custom_plot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_custom_plot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setLog(item->isLog());
    setAxesRangeConnected(true);
}

void SpecularPlotWithDataView::setAxesLabelsFromItem(SpecularDataItem* item)
{
    setLabel(item->xAxisItem(), m_custom_plot->xAxis, item->getXaxisTitle());
    setLabel(item->yAxisItem(), m_custom_plot->yAxis, item->getYaxisTitle());
}

void SpecularPlotWithDataView::setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label)
{
    Q_ASSERT(item && axis);
    if(item->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        axis->setLabel(std::move(label));
    else
        axis->setLabel(QString());
}

void SpecularPlotWithDataView::setDataFromItem(SpecularDataItem* item)
{
    Q_ASSERT(item);
    auto data = item->getOutputData();
    Q_ASSERT(data);
    if (!data)
        return;

    for (size_t i = 0, size = data->getAllocatedSize(); i < size; ++i) {
        double x = data->getAxisValue(i, 0);
        double y = data->operator[](i);
        m_custom_plot->graph()->addData(x, y);
    }
}

SpecularDataItem* SpecularPlotWithDataView::specularItem()
{
    return const_cast<SpecularDataItem*>(
        static_cast<const SpecularPlotWithDataView*>(this)->specularItem());
}

const SpecularDataItem* SpecularPlotWithDataView::specularItem() const
{
    const auto result = dynamic_cast<const SpecularDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void SpecularPlotWithDataView::modifyAxesProperties(const QString& axisName, const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE  ||
        propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(specularItem());
        replot();
    }

    if (axisName == SpecularDataItem::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->xAxis->setRange(specularItem()->getLowerX(), specularItem()->getUpperX());
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == SpecularDataItem::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->yAxis->setRange(specularItem()->getLowerY(), specularItem()->getUpperY());
            setAxesRangeConnected(true);
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLog(specularItem()->isLog());
            replot();
        }
    }
}

void SpecularPlotWithDataView::replot()
{
    m_update_timer->scheduleUpdate();
}

namespace {
int getBin(double x, const QCPGraph* graph) {
    const int key_start = graph->findBegin(x);
    const int key_end = graph->findBegin(x, false); // false = do not expand range
    if (key_end == key_start || key_end == graph->dataCount())
        return key_start;
    return (x - graph->dataSortKey(key_start)) <= (graph->dataSortKey(key_end) - x) ? key_start
                                                                                    : key_end;
}
}
