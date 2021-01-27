//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/Data1DViewItem.cpp
//! @brief     Implements class Data1DViewItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DataViewUtils.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace {
const QString x_axis_default_name = "X [nbins]";
const QString y_axis_default_name = "Signal [a.u.]";

const double default_min = 0.0;
const double default_max = 1.0;
} // namespace

const QString Data1DViewItem::P_TITLE = "Title";
const QString Data1DViewItem::P_XAXIS = "x-axis";
const QString Data1DViewItem::P_YAXIS = "y-axis";
const QString Data1DViewItem::P_AXES_UNITS = "Axes Units";
const QString Data1DViewItem::T_DATA_PROPERTIES = "Data property container";

Data1DViewItem::Data1DViewItem() : SessionItem("Data1DViewItem"), m_job_item(nullptr)
{
    addProperty(P_TITLE, QString())->setVisible(false);

    auto basicAxis = addProperty<BasicAxisItem>(P_XAXIS);
    basicAxis->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    auto amplitudeAxis = addProperty<AmplitudeAxisItem>(P_YAXIS);
    amplitudeAxis->getItem(BasicAxisItem::P_NBINS)->setVisible(false);
    amplitudeAxis->getItem(BasicAxisItem::P_TITLE)->setVisible(true);
    amplitudeAxis->getItem(AmplitudeAxisItem::P_IS_VISIBLE)->setValue(true);
    amplitudeAxis->getItem(AmplitudeAxisItem::P_IS_VISIBLE)->setVisible(false);

    registerTag(T_DATA_PROPERTIES, 1, 1, QStringList() << "DataPropertyContainer");

    ComboProperty combo = ComboProperty() << "nbins";
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

int Data1DViewItem::getNbins() const
{

    return xAxisItem()->binCount();
}

double Data1DViewItem::getLowerX() const
{
    return xAxisItem()->lowerBound();
}

double Data1DViewItem::getUpperX() const
{
    return xAxisItem()->upperBound();
}

double Data1DViewItem::getLowerY() const
{
    return yAxisItem()->lowerBound();
}

double Data1DViewItem::getUpperY() const
{
    return yAxisItem()->upperBound();
}

bool Data1DViewItem::isLog() const
{
    return yAxisItem()->isLogScale();
}

QString Data1DViewItem::getXaxisTitle() const
{
    return xAxisItem()->title();
}

QString Data1DViewItem::getYaxisTitle() const
{
    return yAxisItem()->title();
}

void Data1DViewItem::setXaxisTitle(const QString& title)
{
    xAxisItem()->setTitle(title);
}

void Data1DViewItem::setYaxisTitle(const QString& title)
{
    yAxisItem()->setTitle(title);
}

//! set zoom range of x,y axes to axes of input data
void Data1DViewItem::setAxesRangeToData()
{
    const auto data =
        DataViewUtils::getTranslatedData(this, propertyContainerItem()->basicDataItem());

    // For data loading from disk: items appear earlier than
    // actual data.
    if (!data)
        return;

    setLowerX(data->axis(0).lowerBound());
    setUpperX(data->axis(0).upperBound());

    auto data_range = dataRange(data.get());
    setLowerY(data_range.first);
    setUpperY(data_range.second);
}

void Data1DViewItem::resetToDefault()
{
    // TODO: implement when applying DataITem1DView in ImportView
    throw GUIHelpers::Error("Error in DataItem1DView::resetToDefault: not implemented");
}

QPair<QVector<double>, QVector<double>> Data1DViewItem::graphData(Data1DProperties* property_item)
{
    const auto data = DataViewUtils::getTranslatedData(this, property_item->dataItem());
    if (!data)
        return {};

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto centers = data->axis(0).binCenters();
    auto values = data->getRawDataVector();
    return {QVector<double>(centers.begin(), centers.end()),
            QVector<double>(values.begin(), values.end())};
#else
    return {QVector<double>::fromStdVector(data->axis(0).binCenters()),
            QVector<double>::fromStdVector(data->getRawDataVector())};
#endif
}

JobItem* Data1DViewItem::jobItem()
{
    if (m_job_item != nullptr)
        return m_job_item; // returning preset job item

    auto item = parent();
    do {
        if (item->modelType() == "JobItem") {
            m_job_item = dynamic_cast<JobItem*>(item);
            return m_job_item;
        }
    } while ((item = item->parent()));
    throw GUIHelpers::Error(
        "Error in DataItem1DView::jobItem: passed item is not owned by any job item");
}

void Data1DViewItem::setLowerX(double value)
{
    xAxisItem()->setLowerBound(value);
}

void Data1DViewItem::setUpperX(double value)
{
    xAxisItem()->setUpperBound(value);
}

void Data1DViewItem::setLowerY(double value)
{
    yAxisItem()->setLowerBound(value);
}

void Data1DViewItem::setUpperY(double value)
{
    yAxisItem()->setUpperBound(value);
}

void Data1DViewItem::setLog(bool log_flag)
{
    yAxisItem()->setLogScale(log_flag);
}

DataPropertyContainer* Data1DViewItem::propertyContainerItem()
{
    return item<DataPropertyContainer>(T_DATA_PROPERTIES);
}

const BasicAxisItem* Data1DViewItem::xAxisItem() const
{
    return item<BasicAxisItem>(P_XAXIS);
}

BasicAxisItem* Data1DViewItem::xAxisItem()
{
    return item<BasicAxisItem>(P_XAXIS);
}

const AmplitudeAxisItem* Data1DViewItem::yAxisItem() const
{
    return item<AmplitudeAxisItem>(P_YAXIS);
}

AmplitudeAxisItem* Data1DViewItem::yAxisItem()
{
    return item<AmplitudeAxisItem>(P_YAXIS);
}

//! Set axes viewport to original data.

void Data1DViewItem::resetView()
{
    setAxesRangeToData();
}

//! Init ymin, ymax to match the intensity values range.
QPair<double, double> Data1DViewItem::dataRange(const OutputData<double>* data) const
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
