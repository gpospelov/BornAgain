// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NIntensityDataItem.cpp
//! @brief     Implements class NIntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataItem.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "Units.h"
#include <QDebug>

const QString IntensityDataItem::P_XAXIS_MIN = "xmin";
const QString IntensityDataItem::P_XAXIS_MAX = "xmax";
const QString IntensityDataItem::P_YAXIS_MIN = "ymin";
const QString IntensityDataItem::P_YAXIS_MAX = "ymax";
const QString IntensityDataItem::P_ZAXIS_MIN = "zmin";
const QString IntensityDataItem::P_ZAXIS_MAX = "zmax";
const QString IntensityDataItem::P_GRADIENT = "Gradient";
const QString IntensityDataItem::P_IS_LOGZ = "Logz";
const QString IntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString IntensityDataItem::P_XAXIS_TITLE = "x-title";
const QString IntensityDataItem::P_YAXIS_TITLE = "y-title";
const QString IntensityDataItem::P_AXES_UNITS = "Axes Units";
const QString IntensityDataItem::P_PROPERTY_PANEL_FLAG = "Property Panel Flag";
const QString IntensityDataItem::P_PROJECTIONS_FLAG = "Projections Flag";

IntensityDataItem::IntensityDataItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::IntensityDataType, parent)
    , m_data(0)
{
    setItemName(Constants::IntensityDataType);
    registerProperty(P_XAXIS_MIN, 0.0);
    registerProperty(P_XAXIS_MAX, -1.0);
    registerProperty(P_YAXIS_MIN, 0.0);
    registerProperty(P_YAXIS_MAX, -1.0);
    registerProperty(P_ZAXIS_MIN, 0.0);
    registerProperty(P_ZAXIS_MAX, -1.0);

    ComboProperty gradient;

    gradient << Constants::GRADIENT_GRAYSCALE << Constants::GRADIENT_HOT
             << Constants::GRADIENT_COLD << Constants::GRADIENT_NIGHT
             << Constants::GRADIENT_CANDY << Constants::GRADIENT_GEOGRAPHY
             << Constants::GRADIENT_ION << Constants::GRADIENT_THERMAL
             << Constants::GRADIENT_POLAR << Constants::GRADIENT_SPECTRUM
             << Constants::GRADIENT_JET << Constants::GRADIENT_HUES;
    gradient.setValue(Constants::GRADIENT_POLAR);
    registerProperty(P_GRADIENT, gradient.getVariant());

    registerProperty(P_IS_LOGZ, true);
    registerProperty(P_IS_INTERPOLATED, true);
    registerProperty(P_XAXIS_TITLE, QString());
    registerProperty(P_YAXIS_TITLE, QString());
    registerProperty(P_AXES_UNITS, AngleProperty::Degrees(), PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_PROPERTY_PANEL_FLAG, false, PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_PROJECTIONS_FLAG, false);
}

IntensityDataItem::~IntensityDataItem()
{
    delete m_data;
}

void IntensityDataItem::setOutputData(OutputData<double> *data)
{
    Q_ASSERT(data);
    delete m_data;
    m_data = data;

    blockSignals(true);

    QString sunits(" [deg]");
    if(axesInRadians())
        sunits = QString(" [rad]");

    // set zoom range of x-axis to min, max values if it was not set already
    if(getUpperX() < getLowerX()) {
        setLowerX(getXmin());
        setUpperX(getXmax());
    }

    // set zoom range of z-axis to min, max values if it was not set already
    if(getUpperY() < getLowerY()) {
        setLowerY(getYmin());
        setUpperY(getYmax());
    }

    if(getXaxisTitle().isEmpty()) {
        setXaxisTitle(QString::fromStdString(m_data->getAxis(0)->getName()) + sunits);
    }
    if(getYaxisTitle().isEmpty()) {
        setYaxisTitle(QString::fromStdString(m_data->getAxis(1)->getName()) + sunits);
    }

    blockSignals(false);
    emit intensityModified();

}

double IntensityDataItem::getLowerX() const
{
    return getRegisteredProperty(P_XAXIS_MIN).toDouble();
}

double IntensityDataItem::getUpperX() const
{
    return getRegisteredProperty(P_XAXIS_MAX).toDouble();
}

double IntensityDataItem::getXmin() const
{
    Q_ASSERT(m_data);
    if(axesInRadians()) {
        return m_data->getAxis(0)->getMin();
    } else {
        return Units::rad2deg(m_data->getAxis(0)->getMin());
    }
}

double IntensityDataItem::getXmax() const
{
    Q_ASSERT(m_data);
    if(axesInRadians()) {
        return m_data->getAxis(0)->getMax();
    } else {
        return Units::rad2deg(m_data->getAxis(0)->getMax());
    }
}

double IntensityDataItem::getLowerY() const
{
    return getRegisteredProperty(P_YAXIS_MIN).toDouble();
}

double IntensityDataItem::getUpperY() const
{
    return getRegisteredProperty(P_YAXIS_MAX).toDouble();
}

double IntensityDataItem::getYmin() const
{
    Q_ASSERT(m_data);
    if(axesInRadians()) {
        return m_data->getAxis(1)->getMin();
    } else {
        return Units::rad2deg(m_data->getAxis(1)->getMin());
    }
}

double IntensityDataItem::getYmax() const
{
    Q_ASSERT(m_data);
    if(axesInRadians()) {
        return m_data->getAxis(1)->getMax();
    } else {
        return Units::rad2deg(m_data->getAxis(1)->getMax());
    }
}

double IntensityDataItem::getLowerZ() const
{
    return getRegisteredProperty(P_ZAXIS_MIN).toDouble();
}

double IntensityDataItem::getUpperZ() const
{
    return getRegisteredProperty(P_ZAXIS_MAX).toDouble();
}

QString IntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getRegisteredProperty(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool IntensityDataItem::isLogz() const
{
    return getRegisteredProperty(P_IS_LOGZ).toBool();

}

bool IntensityDataItem::isInterpolated() const
{
    return getRegisteredProperty(P_IS_INTERPOLATED).toBool();
}

QString IntensityDataItem::getXaxisTitle() const
{
    return getRegisteredProperty(P_XAXIS_TITLE).toString();
}

QString IntensityDataItem::getYaxisTitle() const
{
    return getRegisteredProperty(P_YAXIS_TITLE).toString();
}

QString IntensityDataItem::getAxesUnits() const
{
    qDebug() << "NIntensityDataItem::getAxesUnits()";
    Q_ASSERT(0);
    return QString();
}

bool IntensityDataItem::axesInRadians() const
{
    AngleProperty angle_property = getRegisteredProperty(P_AXES_UNITS).value<AngleProperty>();
    return angle_property.inRadians();
}

void IntensityDataItem::setLowerX(double xmin)
{
    qDebug() << "IntensityDataItem::setXaxisMin(double xmin)" << xmin;
    setRegisteredProperty(P_XAXIS_MIN, xmin);
}

void IntensityDataItem::setUpperX(double xmax)
{
    qDebug() << "IntensityDataItem::setXaxisMax(double xmax)" << xmax;
    setRegisteredProperty(P_XAXIS_MAX, xmax);
}

void IntensityDataItem::setLowerY(double ymin)
{
    qDebug() << "IntensityDataItem::setYaxisMin(double ymin)" << ymin;
    setRegisteredProperty(P_YAXIS_MIN, ymin);
}

void IntensityDataItem::setUpperY(double ymax)
{
    qDebug() << "IntensityDataItem::setYaxisMax(double ymax)" << ymax;
    setRegisteredProperty(P_YAXIS_MAX, ymax);
}

void IntensityDataItem::setLowerAndUpperZ(double zmin, double zmax)
{
    qDebug() << "IntensityDataItem::setZaxisRange()";
    setRegisteredProperty(P_ZAXIS_MIN, zmin);
    setRegisteredProperty(P_ZAXIS_MAX, zmax);
}

void IntensityDataItem::setLowerZ(double zmin)
{
    qDebug() << "IntensityDataItem::setZaxisMin(double zmin)";
    setRegisteredProperty(P_ZAXIS_MIN, zmin);
}

void IntensityDataItem::setUpperZ(double zmax)
{
    qDebug() << "IntensityDataItem::setZaxisMax(double zmax)";
    setRegisteredProperty(P_ZAXIS_MAX, zmax);
}

void IntensityDataItem::setLogz(bool logz)
{
    qDebug() << "IntensityDataItem::setLogz(bool logz)";
    setRegisteredProperty(P_IS_LOGZ, logz);
}

void IntensityDataItem::setInterpolated(bool interp)
{
    qDebug() << "IntensityDataItem::setInterpolated(bool interp)";
    setRegisteredProperty(P_IS_INTERPOLATED, interp);
}

void IntensityDataItem::setXaxisTitle(QString xtitle)
{
    qDebug() << "IntensityDataItem::setXaxisTitle(QString xtitle)";
    setRegisteredProperty(P_XAXIS_TITLE, xtitle);
}

void IntensityDataItem::setYaxisTitle(QString ytitle)
{
    qDebug() << "IntensityDataItem::setYaxisTitle(QString ytitle)";
    setRegisteredProperty(P_YAXIS_TITLE, ytitle);
}

void IntensityDataItem::setAxesUnits(const QString &units)
{
    qDebug() << "IntensityDataItem::setAxesUnits(QString units)";
    Q_UNUSED(units);
    Q_ASSERT(0);
}
