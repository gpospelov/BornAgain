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
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "DataItem.h"
#include "DataPropertyContainer.h"
#include "DataProperties.h"
#include "DataViewUtils.h"
#include "GUIHelpers.h"
#include "JobItem.h"

namespace {
const QString x_axis_default_name = "X [nbins]";
const QString y_axis_default_name = "Signal [a.u.]";

const double default_min = 0.0;
const double default_max = 1.0;
}

const QString DataItem1DView::P_TITLE = "Title";
const QString DataItem1DView::P_XAXIS = "x-axis";
const QString DataItem1DView::P_YAXIS = "y-axis";
const QString DataItem1DView::P_AXES_UNITS = "Axes Units";
const QString DataItem1DView::T_DATA_PROPERTIES = "Data property container";

DataItem1DView::DataItem1DView()
    : SessionItem(Constants::DataItem1DViewType)
    , m_job_item(nullptr)
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

    registerTag(T_DATA_PROPERTIES, 1, 1, QStringList() << Constants::DataPropertyContainerType);

    ComboProperty combo = ComboProperty() << Constants::UnitsNbins;
    addProperty(P_AXES_UNITS, combo.variant());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name != P_AXES_UNITS)
            return;
        setAxesRangeToData();
        DataViewUtils::updateAxesTitle(this);
    });

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

double DataItem1DView::getLowerY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double DataItem1DView::getUpperY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
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
    const auto data
        = DataViewUtils::getTranslatedData(this, propertyContainerItem()->basicDataItem());

    // For data loading from disk: items appear earlier than
    // actual data.
    if (!data)
        return;

    setLowerX(data->getAxis(BornAgain::X_AXIS_INDEX).getMin());
    setUpperX(data->getAxis(BornAgain::X_AXIS_INDEX).getMax());


    auto data_range = dataRange(data.get());
    setLowerY(data_range.first);
    setUpperY(data_range.second);
}

void DataItem1DView::resetToDefault()
{
    //TODO: implement when applying DataITem1DView in ImportView
    throw GUIHelpers::Error("Error in DataItem1DView::resetToDefault: not implemented");
}

QPair<QVector<double>, QVector<double>> DataItem1DView::graphData(Data1DProperties* property_item)
{
    const auto data = DataViewUtils::getTranslatedData(this, property_item->dataItem());
    if (!data)
        return {};
    return {QVector<double>::fromStdVector(data->getAxis(0).getBinCenters()),
                QVector<double>::fromStdVector(data->getRawDataVector())};
}

JobItem* DataItem1DView::jobItem()
{
    if (m_job_item != nullptr)
        return m_job_item; // returning preset job item

    auto item = parent();
    do {
        if (item->modelType() == Constants::JobItemType) {
            m_job_item = dynamic_cast<JobItem*>(item);
            return m_job_item;
        }
    } while ((item = item->parent()));
    throw GUIHelpers::Error(
        "Error in DataItem1DView::jobItem: passed item is not owned by any job item");
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

DataPropertyContainer *DataItem1DView::propertyContainerItem()
{
    return dynamic_cast<DataPropertyContainer*>(getItem(T_DATA_PROPERTIES));
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

//! Init ymin, ymax to match the intensity values range.
QPair<double, double> DataItem1DView::dataRange(const OutputData<double>* data) const
{
    if (!data)
        return QPair<double, double>(default_min, default_max);

    double min(*std::min_element(data->begin(), data->end()));
    double max(*std::max_element(data->begin(), data->end()));

    min /= 2.0;
    min = std::numeric_limits<double>::epsilon() < min ? min : default_min;
    max *= 2.0;
    max = max > min ? max : default_max;

    return QPair<double, double>(min, max);
}
