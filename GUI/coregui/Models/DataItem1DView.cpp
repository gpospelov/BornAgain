// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItem1DView.cpp
//! @brief     Implements class DataItem1DView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataItem1DView.h"
#include "DataItem.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"

namespace {
const QString x_axis_default_name = "X [nbins]";
const QString y_axis_default_name = "Signal [a.u.]";

const double default_min = 0.0;
const double default_max = 1.0;
}

const QString DataItem1DView::P_TITLE = "Title";
const QString DataItem1DView::P_XAXIS = "x-axis";
const QString DataItem1DView::P_YAXIS = "y-axis";

DataItem1DView::DataItem1DView()
    : DataItemView(Constants::DataItem1DViewType)
{
    addProperty(P_TITLE, QString())->setVisible(false);

    SessionItem* item = addGroupProperty(P_XAXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    item = addGroupProperty(P_YAXIS, Constants::AmplitudeAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(true);

    item = item->getItem(AmplitudeAxisItem::P_IS_VISIBLE);
    item->setValue(true);
    item->setVisible(false);

    setLowerX(default_min);
    setUpperX(default_max);
    setLowerY(default_min);
    setUpperY(default_max);
    setXaxisTitle(x_axis_default_name);
    setYaxisTitle(y_axis_default_name);
}

int DataItem1DView::getNbins() const
{
    return xAxisItem()->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

double DataItem1DView::getLowerX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double DataItem1DView::getUpperX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double DataItem1DView::getXmin() const
{
    auto output_data = getOutputData(0);
    return !output_data ? default_min : output_data->getAxis(BornAgain::X_AXIS_INDEX).getMin();
}

double DataItem1DView::getXmax() const
{
    auto output_data = getOutputData(0);
    return !output_data ? default_max : output_data->getAxis(BornAgain::X_AXIS_INDEX).getMax();
}

double DataItem1DView::getLowerY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double DataItem1DView::getUpperY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double DataItem1DView::getYmin() const
{
    return dataRange().first;
}

double DataItem1DView::getYmax() const
{
    return dataRange().second;
}

bool DataItem1DView::isLog() const
{
    return getItem(P_YAXIS)->getItemValue(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

QString DataItem1DView::getXaxisTitle() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString DataItem1DView::getYaxisTitle() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

void DataItem1DView::setXaxisTitle(QString xtitle)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_TITLE, xtitle);
}

void DataItem1DView::setYaxisTitle(QString ytitle)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void DataItem1DView::setAxesRangeToData()
{
    setLowerX(getXmin());
    setUpperX(getXmax());
    setLowerY(getYmin());
    setUpperY(getYmax());
}

void DataItem1DView::updateAxesUnits(const InstrumentItem* instrument)
{
    auto items = dataItems();
    std::for_each(items.begin(), items.end(),
                  [instrument](DataItem* item) { item->updateAxesUnits(instrument); });
}

void DataItem1DView::resetToDefault()
{
    auto items = dataItems();
    std::for_each(items.begin(), items.end(),
                  [](DataItem* item) { item->resetToDefault(); });

    setXaxisTitle(x_axis_default_name);
    setYaxisTitle(y_axis_default_name);
    setAxesRangeToData();
}

void DataItem1DView::setLowerX(double xmin)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MIN, xmin);
}

void DataItem1DView::setUpperX(double xmax)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MAX, xmax);
}

void DataItem1DView::setLowerY(double ymin)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MIN, ymin);
}

void DataItem1DView::setUpperY(double ymax)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MAX, ymax);
}

void DataItem1DView::setLog(bool log_flag)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, log_flag);
}

//! Init ymin, ymax to match the intensity values range.
QPair<double, double> DataItem1DView::dataRange() const
{
    auto output_data = getOutputData(0);
    if (!output_data)
        return QPair<double, double>(default_min, default_max);
    double min(*std::min_element(output_data->begin(), output_data->end()));
    double max(*std::max_element(output_data->begin(), output_data->end()));

    min /= 2.0;
    min = std::numeric_limits<double>::epsilon() < min ? min : default_min;
    max *= 2.0;
    max = max > min ? max : default_max;

    return QPair<double, double>(min, max);
}

const BasicAxisItem* DataItem1DView::xAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_XAXIS));
}

BasicAxisItem* DataItem1DView::xAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const DataItem1DView*>(this)->xAxisItem());
}

const AmplitudeAxisItem* DataItem1DView::yAxisItem() const
{
    auto result = dynamic_cast<const AmplitudeAxisItem*>(getItem(P_YAXIS));
    Q_ASSERT(result);
    return result;
}

//! Set axes viewport to original data.

void DataItem1DView::resetView()
{
    setAxesRangeToData();
}

//! Sets zoom range of X,Y axes, if it was not yet defined.

void DataItem1DView::updateAxesZoomLevel()
{
    auto output_data = getOutputData(0);
    if (!output_data)
        return;
    const int nx = static_cast<int>(output_data->getAxis(BornAgain::X_AXIS_INDEX).size());
    xAxisItem()->setItemValue(BasicAxisItem::P_NBINS, nx);
}
