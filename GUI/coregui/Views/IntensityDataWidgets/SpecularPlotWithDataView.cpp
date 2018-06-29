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
#include "DataItem.h"
#include "DataItem1DView.h"
#include "DataPresentationProperties.h"
#include "MathConstants.h"
#include "PlotEventInfo.h"
#include "UpdateTimer.h"
#include "plot_constants.h"

namespace
{
const int replot_update_interval = 10;

int getBin(double x, const QCPGraph* graph);
}

SpecularPlotWithDataView::SpecularPlotWithDataView(QWidget* parent)
    : ScientificPlot(parent, PLOT_TYPE::Plot1D), m_custom_plot(new QCustomPlot),
      m_update_timer(new UpdateTimer(replot_update_interval, this)), m_block_update(true)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_custom_plot);
    setLayout(vlayout);

    m_custom_plot->xAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));
    m_custom_plot->yAxis->setTickLabelFont(
        QFont(QFont().family(), Constants::plot_tick_label_size));

    setMouseTrackingEnabled(true);
}

PlotEventInfo SpecularPlotWithDataView::eventInfo(double xpos, double ypos) const
{
    PlotEventInfo result(plotType());
    if (!viewItem())
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
    viewItem()->resetView();
}

void SpecularPlotWithDataView::onPropertyChanged(const QString& property_name)
{
    if (m_block_update)
        return;

    if (property_name == DataItem1DView::P_AXES_UNITS) {
        setAxesRangeFromItem(viewItem());
        replot();
    }
}

void SpecularPlotWithDataView::onXaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    viewItem()->setLowerX(newRange.lower);
    viewItem()->setUpperX(newRange.upper);
    m_block_update = false;
}

void SpecularPlotWithDataView::onYaxisRangeChanged(QCPRange newRange)
{
    m_block_update = true;
    viewItem()->setLowerY(newRange.lower);
    viewItem()->setUpperY(newRange.upper);
    m_block_update = false;
}

void SpecularPlotWithDataView::onTimeToReplot()
{
    m_custom_plot->replot();
}

void SpecularPlotWithDataView::subscribeToItem()
{
    initPlots();
    refreshPlotData();

    viewItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    viewItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            if (item->modelType() == Constants::BasicAxisType
                || item->modelType() == Constants::AmplitudeAxisType)
                modifyAxesProperties(item->itemName(), name);
        },
        this);

    viewItem()->mapper()->setOnValueChange([this]() { refreshPlotData(); }, this);

    setConnected(true);
}

void SpecularPlotWithDataView::unsubscribeFromItem()
{
    m_custom_plot->clearGraphs();
    m_graph_map.clear();
    setConnected(false);
}

void SpecularPlotWithDataView::initPlots()
{
    auto property_items = viewItem()->propertyItems<Data1DPresentationProperties>();
    std::for_each(
        property_items.begin(), property_items.end(), [this](Data1DPresentationProperties* item) {
            auto graph = m_custom_plot->addGraph();
            QColor color(item->getItemValue(Data1DPresentationProperties::P_COLOR).toString());
            graph->setLineStyle(QCPGraph::lsLine);
            graph->setPen(QPen(color));
            m_graph_map[item] = graph;
        });
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
        connect(m_update_timer, &UpdateTimer::timeToUpdate, this,
                &SpecularPlotWithDataView::onTimeToReplot, Qt::UniqueConnection);
    else
        disconnect(m_update_timer, &UpdateTimer::timeToUpdate, this,
                   &SpecularPlotWithDataView::onTimeToReplot);
}

void SpecularPlotWithDataView::refreshPlotData()
{
    auto view_item = viewItem();
    assert(view_item);

    m_block_update = true;

    std::for_each(m_graph_map.begin(), m_graph_map.end(), [](auto pair){pair.second->data()->clear();});
    setAxesRangeFromItem(view_item);
    setAxesLabelsFromItem(view_item);
    setDataFromItem(view_item);

    replot();

    m_block_update = false;
}

void SpecularPlotWithDataView::setAxesRangeFromItem(DataItem1DView* item)
{
    m_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_custom_plot->axisRect()->setupFullAxesBox(true);

    setAxesRangeConnected(false);
    m_custom_plot->xAxis->setRange(item->getLowerX(), item->getUpperX());
    m_custom_plot->yAxis->setRange(item->getLowerY(), item->getUpperY());
    setLog(item->isLog());
    setAxesRangeConnected(true);
}

void SpecularPlotWithDataView::setAxesLabelsFromItem(DataItem1DView* item)
{
    setLabel(item->xAxisItem(), m_custom_plot->xAxis, item->getXaxisTitle());
    setLabel(item->yAxisItem(), m_custom_plot->yAxis, item->getYaxisTitle());
}

void SpecularPlotWithDataView::setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label)
{
    assert(item && axis);
    if (item->getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool())
        axis->setLabel(std::move(label));
    else
        axis->setLabel(QString());
}

void SpecularPlotWithDataView::setDataFromItem(DataItem1DView* item)
{
    assert(item);
    auto property_items = item->propertyItems<Data1DPresentationProperties>();
    std::for_each(property_items.begin(), property_items.end(),
                  [this](Data1DPresentationProperties* item) {
                      auto data = item->dataItem()->getOutputData();
                      if (!data)
                          return;

                      auto graph = m_graph_map.at(item);
                      for (size_t i = 0, size = data->getAllocatedSize(); i < size; ++i) {
                          double x = data->getAxisValue(i, 0);
                          double y = data->operator[](i);
                          graph->addData(x, y);
                      }
                  });
}

DataItem1DView* SpecularPlotWithDataView::viewItem()
{
    return const_cast<DataItem1DView*>(
        static_cast<const SpecularPlotWithDataView*>(this)->viewItem());
}

const DataItem1DView* SpecularPlotWithDataView::viewItem() const
{
    const auto result = dynamic_cast<const DataItem1DView*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void SpecularPlotWithDataView::modifyAxesProperties(const QString& axisName,
                                                    const QString& propertyName)
{
    if (m_block_update)
        return;

    if (propertyName == BasicAxisItem::P_TITLE
        || propertyName == BasicAxisItem::P_TITLE_IS_VISIBLE) {
        setAxesLabelsFromItem(viewItem());
        replot();
    }

    if (axisName == DataItem1DView::P_XAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->xAxis->setRange(viewItem()->getLowerX(), viewItem()->getUpperX());
            setAxesRangeConnected(true);
            replot();
        }
    } else if (axisName == DataItem1DView::P_YAXIS) {
        if (propertyName == BasicAxisItem::P_MIN || propertyName == BasicAxisItem::P_MAX) {
            setAxesRangeConnected(false);
            m_custom_plot->yAxis->setRange(viewItem()->getLowerY(), viewItem()->getUpperY());
            setAxesRangeConnected(true);
            replot();
        } else if (propertyName == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLog(viewItem()->isLog());
            replot();
        }
    }
}

void SpecularPlotWithDataView::replot()
{
    m_update_timer->scheduleUpdate();
}

namespace
{
int getBin(double x, const QCPGraph* graph)
{
    const int key_start = graph->findBegin(x);
    const int key_end = graph->findBegin(x, false); // false = do not expand range
    if (key_end == key_start || key_end == graph->dataCount())
        return key_start;
    return (x - graph->dataSortKey(key_start)) <= (graph->dataSortKey(key_end) - x) ? key_start
                                                                                    : key_end;
}
}
