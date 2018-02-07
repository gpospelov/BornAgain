// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SpecularDataItem.cpp
//! @brief     Implements class SpecularDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularDataItem.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "BornAgainNamespace.h"

const QString SpecularDataItem::P_AXES_UNITS = "Axes Units";
const QString SpecularDataItem::P_TITLE = "Title";
const QString SpecularDataItem::P_XAXIS = "x-axis";
const QString SpecularDataItem::P_YAXIS = "y-axis";
const QString SpecularDataItem::P_FILE_NAME = "FileName";

SpecularDataItem::SpecularDataItem() : SessionItem(Constants::SpecularDataType)
{
    ComboProperty units = ComboProperty() << Constants::UnitsNbins;
    addProperty(P_AXES_UNITS, units.variant());

    addProperty(P_TITLE, QString())->setVisible(false);

    SessionItem* item = addGroupProperty(P_XAXIS, Constants::BasicAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    item = addGroupProperty(P_YAXIS, Constants::AmplitudeAxisType);
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(true);

    item = item->getItem(AmplitudeAxisItem::P_IS_VISIBLE);
    item->setValue(true);
    item->setVisible(false);

    setXaxisTitle("X [nbins]");
    setYaxisTitle("Signal [a.u.]");

    // name of the file used to serialize given SpecularDataItem
    addProperty(P_FILE_NAME, QStringLiteral("undefined"))->setVisible(false);

    mapper()->setOnPropertyChange([this](const QString& name)
    {
        if(name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });

    mapper()->setOnValueChange([this]()
    {
        // OutputData was modified
        setLastModified(QDateTime::currentDateTime());
    });
}

void SpecularDataItem::setOutputData(OutputData<double>* data)
{
    Q_ASSERT(data);
    m_data.reset(data);

    updateAxesZoomLevel();
    updateAxesLabels();
    computeDataRange();

    emitDataChanged();
}

//! Sets the raw data vector from external source

void SpecularDataItem::setRawDataVector(const OutputData<double>* data)
{
    if (!m_data->hasSameDimensions(*data)) {
        throw GUIHelpers::Error("SpecularDataItem::setRawDataVector() -> Error. "
                                "Different dimensions of data.");
    }
    m_data->setRawDataVector(data->getRawDataVector());
    emitDataChanged();
}

int SpecularDataItem::getNbins() const
{
    return xAxisItem()->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

double SpecularDataItem::getLowerX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double SpecularDataItem::getUpperX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double SpecularDataItem::getXmin() const
{
    const double defaultXmin(0.0);
    return m_data ? m_data->getAxis(BornAgain::X_AXIS_INDEX).getMin() : defaultXmin;
}

double SpecularDataItem::getXmax() const
{
    const double defaultXmax(1.0);
    return m_data ? m_data->getAxis(BornAgain::X_AXIS_INDEX).getMax() : defaultXmax;
}

double SpecularDataItem::getLowerY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double SpecularDataItem::getUpperY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

double SpecularDataItem::getYmin() const
{
    const double defaultYmin(0.0);
    auto limits = dataRange();
    return m_data ? limits.first : defaultYmin;
}

double SpecularDataItem::getYmax() const
{
    const double defaultYmax(1.0);
    auto limits = dataRange();
    return m_data ? limits.second : defaultYmax;
}

bool SpecularDataItem::isLog() const
{
    return getItem(P_YAXIS)->getItemValue(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

QString SpecularDataItem::getXaxisTitle() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString SpecularDataItem::getYaxisTitle() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString SpecularDataItem::selectedAxesUnits() const
{
    ComboProperty combo = getItemValue(SpecularDataItem::P_AXES_UNITS).value<ComboProperty>();
    return combo.getValue();
}

QString SpecularDataItem::fileName(const QString& projectDir) const
{
    QString filename = getItemValue(SpecularDataItem::P_FILE_NAME).toString();
    return projectDir.isEmpty() ? filename : projectDir + QStringLiteral("/") + filename;
}

void SpecularDataItem::setLowerX(double xmin)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MIN, xmin);
}

void SpecularDataItem::setUpperX(double xmax)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MAX, xmax);
}

void SpecularDataItem::setLowerY(double ymin)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MIN, ymin);
}

void SpecularDataItem::setUpperY(double ymax)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MAX, ymax);
}

void SpecularDataItem::setLog(bool log_flag)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, log_flag);
}

void SpecularDataItem::setXaxisTitle(QString xtitle)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_TITLE, xtitle);
}

void SpecularDataItem::setYaxisTitle(QString ytitle)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void SpecularDataItem::setAxesRangeToData()
{
    setLowerX(getXmin());
    setUpperX(getXmax());
    setLowerY(getYmin());
    setUpperY(getYmax());
}

//! Sets zoom range of X,Y axes, if it was not yet defined.

void SpecularDataItem::updateAxesZoomLevel()
{
    // set zoom range of x-axis to min, max values if it was not set already
    if (getUpperX() < getLowerX()) {
        setLowerX(getXmin());
        setUpperX(getXmax());
    }

    // set zoom range of y-axis to min, max values if it was not set already
    if (getUpperY() < getLowerY()) {
        setLowerY(getYmin());
        setUpperY(getYmax());
    }

    const int nx = static_cast<int>(m_data->getAxis(BornAgain::X_AXIS_INDEX).size());
    xAxisItem()->setItemValue(BasicAxisItem::P_NBINS, nx);
}

//! Init axes labels, if it was not done already.

void SpecularDataItem::updateAxesLabels()
{
    if (getXaxisTitle().isEmpty())
        setXaxisTitle(QString::fromStdString(m_data->getAxis(BornAgain::X_AXIS_INDEX).getName()));
}

void SpecularDataItem::computeDataRange()
{
    QPair<double, double> minmax = dataRange();
    setLowerY(minmax.first);
    setUpperY(minmax.second);
}

//! Init ymin, ymax to match the intensity values range.
QPair<double, double> SpecularDataItem::dataRange() const
{
    const OutputData<double>* data = getOutputData();
    double min(*std::min_element(data->begin(), data->end()));
    double max(*std::max_element(data->begin(), data->end()));
    if (isLog()) {
        min /= 2.0;
        max *= 2.0;
    } else {
        max = max * 1.1;
    }

    return QPair<double, double>(min, max);
}

const BasicAxisItem* SpecularDataItem::xAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_XAXIS));
}

BasicAxisItem* SpecularDataItem::xAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const SpecularDataItem*>(this)->xAxisItem());
}

const AmplitudeAxisItem* SpecularDataItem::yAxisItem() const
{
    auto result = dynamic_cast<const AmplitudeAxisItem*>(getItem(P_YAXIS));
    Q_ASSERT(result);
    return result;
}

//! Set axes viewport to original data.

void SpecularDataItem::resetView()
{
    setAxesRangeToData();
    computeDataRange();
}

QDateTime SpecularDataItem::lastModified() const
{
    return m_last_modified;
}

void SpecularDataItem::setLastModified(const QDateTime &dtime)
{
    m_last_modified = dtime;
}
