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

#include "NIntensityDataItem.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include <QDebug>

const QString NIntensityDataItem::P_XAXIS_MIN = "xmin";
const QString NIntensityDataItem::P_XAXIS_MAX = "xmax";
const QString NIntensityDataItem::P_YAXIS_MIN = "ymin";
const QString NIntensityDataItem::P_YAXIS_MAX = "ymax";
const QString NIntensityDataItem::P_ZAXIS_MIN = "zmin";
const QString NIntensityDataItem::P_ZAXIS_MAX = "zmax";
const QString NIntensityDataItem::P_GRADIENT = "Gradient";
const QString NIntensityDataItem::P_IS_LOGZ = "Logz";
const QString NIntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString NIntensityDataItem::P_XAXIS_TITLE = "x-title";
const QString NIntensityDataItem::P_YAXIS_TITLE = "y-title";
const QString NIntensityDataItem::P_AXES_UNITS = "Axes Units";
const QString NIntensityDataItem::P_PROPERTY_PANEL_FLAG = "Property Panel Flag";
const QString NIntensityDataItem::P_PROJECTIONS_FLAG = "Projections Flag";

NIntensityDataItem::NIntensityDataItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::IntensityDataType, parent)
    , m_data(0)
{
    setItemName(Constants::IntensityDataType);
    registerProperty(P_XAXIS_MIN, 0.0);
    registerProperty(P_XAXIS_MAX, 0.0);
    registerProperty(P_YAXIS_MIN, 0.0);
    registerProperty(P_YAXIS_MAX, 0.0);
    registerProperty(P_ZAXIS_MIN, 0.0);
    registerProperty(P_ZAXIS_MAX, 0.0);

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
    registerProperty(P_XAXIS_TITLE, QString("x-axis"));
    registerProperty(P_YAXIS_TITLE, QString("y-axis"));
    registerProperty(P_AXES_UNITS, AngleProperty::Degrees(), PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_PROPERTY_PANEL_FLAG, false, PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_PROJECTIONS_FLAG, false);
}

NIntensityDataItem::~NIntensityDataItem()
{
    delete m_data;
}

void NIntensityDataItem::setOutputData(OutputData<double> *data)
{
//    if(data != m_data) {
        qDebug() << "OutputDataItem::setOutputData(OutputData<double> *data)";
        delete m_data;
        m_data = data;
//        if(axesInRadians()) {
//            m_xaxis_title = QString(data->getAxis(0)->getName().c_str())+QString(" [rad]");
//            m_yaxis_title = QString(data->getAxis(1)->getName().c_str())+QString(" [rad]");
//        } else {
//            m_xaxis_title = QString(data->getAxis(0)->getName().c_str())+QString(" [deg]");
//            m_yaxis_title = QString(data->getAxis(1)->getName().c_str())+QString(" [deg]");
//        }
//        emit modified();
        qDebug() << "OutputDataItem::setOutputData() -> emitting intensity modified";
        emit intensityModified();
        //    }
}

double NIntensityDataItem::getXaxisMin() const
{
    return getRegisteredProperty(P_XAXIS_MIN).toDouble();
}

double NIntensityDataItem::getXaxisMax() const
{
    return getRegisteredProperty(P_XAXIS_MAX).toDouble();
}

double NIntensityDataItem::getYaxisMin() const
{
    return getRegisteredProperty(P_YAXIS_MIN).toDouble();
}

double NIntensityDataItem::getYaxisMax() const
{
    return getRegisteredProperty(P_YAXIS_MAX).toDouble();
}

double NIntensityDataItem::getZaxisMin() const
{
    return getRegisteredProperty(P_ZAXIS_MIN).toDouble();
}

double NIntensityDataItem::getZaxisMax() const
{
    return getRegisteredProperty(P_ZAXIS_MAX).toDouble();
}

QString NIntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getRegisteredProperty(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool NIntensityDataItem::isLogz() const
{
    return getRegisteredProperty(P_IS_LOGZ).toBool();

}

bool NIntensityDataItem::isInterpolated() const
{
    return getRegisteredProperty(P_IS_INTERPOLATED).toBool();
}

QString NIntensityDataItem::getXaxisTitle() const
{
    return getRegisteredProperty(P_XAXIS_TITLE).toString();
}

QString NIntensityDataItem::getYaxisTitle() const
{
    return getRegisteredProperty(P_YAXIS_TITLE).toString();
}

QString NIntensityDataItem::getAxesUnits() const
{
    qDebug() << "NIntensityDataItem::getAxesUnits()";
    Q_ASSERT(0);
    return QString();
}

bool NIntensityDataItem::axesInRadians() const
{
    AngleProperty angle_property = getRegisteredProperty(P_AXES_UNITS).value<AngleProperty>();
    return angle_property.inRadians();
}

void NIntensityDataItem::setXaxisMin(double xmin)
{
    qDebug() << "NIntensityDataItem::setXaxisMin(double xmin)";
    setRegisteredProperty(P_XAXIS_MIN, xmin);
}

void NIntensityDataItem::setXaxisMax(double xmax)
{
    qDebug() << "NIntensityDataItem::setXaxisMax(double xmax)";
    setRegisteredProperty(P_XAXIS_MAX, xmax);
}

void NIntensityDataItem::setYaxisMin(double ymin)
{
    qDebug() << "NIntensityDataItem::setYaxisMin(double ymin)";
    setRegisteredProperty(P_YAXIS_MIN, ymin);
}

void NIntensityDataItem::setYaxisMax(double ymax)
{
    qDebug() << "NIntensityDataItem::setYaxisMax(double ymax)";
    setRegisteredProperty(P_YAXIS_MAX, ymax);
}

void NIntensityDataItem::setZaxisRange(double zmin, double zmax)
{
    qDebug() << "NIntensityDataItem::setZaxisRange()";
    setRegisteredProperty(P_ZAXIS_MIN, zmin);
    setRegisteredProperty(P_ZAXIS_MAX, zmax);
}

void NIntensityDataItem::setZaxisMin(double zmin)
{
    qDebug() << "NIntensityDataItem::setZaxisMin(double zmin)";
    setRegisteredProperty(P_ZAXIS_MIN, zmin);
}

void NIntensityDataItem::setZaxisMax(double zmax)
{
    qDebug() << "NIntensityDataItem::setZaxisMax(double zmax)";
    setRegisteredProperty(P_ZAXIS_MAX, zmax);
}

void NIntensityDataItem::setLogz(bool logz)
{
    qDebug() << "NIntensityDataItem::setLogz(bool logz)";
    setRegisteredProperty(P_IS_LOGZ, logz);
}

void NIntensityDataItem::setInterpolated(bool interp)
{
    qDebug() << "NIntensityDataItem::setInterpolated(bool interp)";
    setRegisteredProperty(P_IS_INTERPOLATED, interp);
}

void NIntensityDataItem::setXaxisTitle(QString xtitle)
{
    qDebug() << "NIntensityDataItem::setXaxisTitle(QString xtitle)";
    setRegisteredProperty(P_XAXIS_TITLE, xtitle);
}

void NIntensityDataItem::setYaxisTitle(QString ytitle)
{
    qDebug() << "NIntensityDataItem::setYaxisTitle(QString ytitle)";
    setRegisteredProperty(P_YAXIS_TITLE, ytitle);
}

void NIntensityDataItem::setAxesUnits(const QString &units)
{
    qDebug() << "NIntensityDataItem::setAxesUnits(QString units)";
    Q_UNUSED(units);
    Q_ASSERT(0);
}
