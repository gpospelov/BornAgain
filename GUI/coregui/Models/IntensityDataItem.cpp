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
#include "AxesItems.h"
#include "Units.h"
#include "GUIHelpers.h"
#include "GISASSimulation.h"
#include <QDebug>

const QString IntensityDataItem::P_PROJECTIONS_FLAG = "Projections";
const QString IntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString IntensityDataItem::P_GRADIENT = "Gradient";
const QString IntensityDataItem::P_AXES_UNITS = "Axes Units";
const QString IntensityDataItem::P_PROPERTY_PANEL_FLAG = "Property Panel Flag";
const QString IntensityDataItem::P_XAXIS = "x-axis";
const QString IntensityDataItem::P_YAXIS = "y-axis";
const QString IntensityDataItem::P_ZAXIS = "color-axis";


IntensityDataItem::IntensityDataItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::IntensityDataType, parent)
    , m_data(0)
{
    registerProperty(P_NAME, Constants::IntensityDataType);

    ComboProperty units;
    units << Constants::UnitsNbins << Constants::UnitsRadians << Constants::UnitsDegrees
          << Constants::UnitsMm << Constants::UnitsQyQz;

    registerProperty(P_PROJECTIONS_FLAG, false);
    registerProperty(P_IS_INTERPOLATED, true);

    ComboProperty gradient;

    gradient << Constants::GRADIENT_GRAYSCALE << Constants::GRADIENT_HOT
             << Constants::GRADIENT_COLD << Constants::GRADIENT_NIGHT
             << Constants::GRADIENT_CANDY << Constants::GRADIENT_GEOGRAPHY
             << Constants::GRADIENT_ION << Constants::GRADIENT_THERMAL
             << Constants::GRADIENT_POLAR << Constants::GRADIENT_SPECTRUM
             << Constants::GRADIENT_JET << Constants::GRADIENT_HUES;
    gradient.setValue(Constants::GRADIENT_JET);
    registerProperty(P_GRADIENT, gradient.getVariant());

    registerProperty(P_AXES_UNITS, AngleProperty::Degrees()).setHidden();
    registerProperty(P_PROPERTY_PANEL_FLAG, false).setHidden();

    registerGroupProperty(P_XAXIS, Constants::BasicAxisType);
    getSubItems()[P_XAXIS]->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    registerGroupProperty(P_YAXIS, Constants::BasicAxisType);
    getSubItems()[P_YAXIS]->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    registerGroupProperty(P_ZAXIS, Constants::AmplitudeAxisType);
    getSubItems()[P_ZAXIS]->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    addToValidChildren(Constants::MaskContainerType);
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

    // set zoom range of y-axis to min, max values if it was not set already
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
    qDebug() << "Emmitting intensityModified();";
    emit intensityModified();
}

void IntensityDataItem::setResults(const GISASSimulation *simulation)
{
    Q_ASSERT(simulation);
    m_simulation.reset(simulation);
    setOutputData(m_simulation->getDetectorIntensity());
}

double IntensityDataItem::getLowerX() const
{
    return getSubItems()[P_XAXIS]->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperX() const
{
    return getSubItems()[P_XAXIS]->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
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
    return getSubItems()[P_YAXIS]->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperY() const
{
    return getSubItems()[P_YAXIS]->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
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
    return getSubItems()[P_ZAXIS]->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperZ() const
{
    return getSubItems()[P_ZAXIS]->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
}

QString IntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getRegisteredProperty(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool IntensityDataItem::isLogz() const
{
    return getSubItems()[P_ZAXIS]->getRegisteredProperty(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

bool IntensityDataItem::isInterpolated() const
{
    return getRegisteredProperty(P_IS_INTERPOLATED).toBool();
}

QString IntensityDataItem::getXaxisTitle() const
{
    return getSubItems()[P_XAXIS]->getRegisteredProperty(BasicAxisItem::P_TITLE).toString();
}

QString IntensityDataItem::getYaxisTitle() const
{
    return getSubItems()[P_YAXIS]->getRegisteredProperty(BasicAxisItem::P_TITLE).toString();
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

bool IntensityDataItem::isZAxisLocked() const
{
    return getSubItems()[P_ZAXIS]->getRegisteredProperty(AmplitudeAxisItem::P_LOCK_MIN_MAX).toBool();
}

void IntensityDataItem::setZAxisLocked(bool state)
{
    return getSubItems()[P_ZAXIS]->setRegisteredProperty(AmplitudeAxisItem::P_LOCK_MIN_MAX, state);
}

//! Sets the name of intensity data item from proposed name. This name will be used to save file
//! on disk, so special characters should be removed.
void IntensityDataItem::setNameFromProposed(const QString &proposed_name)
{
    QString valid_name = GUIHelpers::getValidFileName(proposed_name);
    setItemName(QString("data_%1_%2.int").arg(valid_name, QString::number(0)));
}

void IntensityDataItem::setLowerX(double xmin)
{
    qDebug() << "IntensityDataItem::setXaxisMin(double xmin)" << xmin;
    getSubItems()[P_XAXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, xmin);
}

void IntensityDataItem::setUpperX(double xmax)
{
    qDebug() << "IntensityDataItem::setXaxisMax(double xmax)" << xmax;
    getSubItems()[P_XAXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, xmax);
}

void IntensityDataItem::setLowerY(double ymin)
{
    qDebug() << "IntensityDataItem::setYaxisMin(double ymin)" << ymin;
    getSubItems()[P_YAXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, ymin);
}

void IntensityDataItem::setUpperY(double ymax)
{
    qDebug() << "IntensityDataItem::setYaxisMax(double ymax)" << ymax;
    getSubItems()[P_YAXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, ymax);
}

void IntensityDataItem::setLowerAndUpperZ(double zmin, double zmax)
{
    qDebug() << "IntensityDataItem::setLowerAndUpperZ()";
    if(getLowerZ() != zmin) {
        getSubItems()[P_ZAXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, zmin);
    }
    if(getUpperZ() != zmax) {
        getSubItems()[P_ZAXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, zmax);
    }
}

void IntensityDataItem::setLowerZ(double zmin)
{
    qDebug() << "IntensityDataItem::setZaxisMin(double zmin)";
    getSubItems()[P_ZAXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, zmin);
}

void IntensityDataItem::setUpperZ(double zmax)
{
    qDebug() << "IntensityDataItem::setZaxisMax(double zmax)";
    getSubItems()[P_ZAXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, zmax);
}

void IntensityDataItem::setLogz(bool logz)
{
    qDebug() << "IntensityDataItem::setLogz(bool logz)";
    getSubItems()[P_ZAXIS]->setRegisteredProperty(AmplitudeAxisItem::P_IS_LOGSCALE, logz);
}

void IntensityDataItem::setInterpolated(bool interp)
{
    qDebug() << "IntensityDataItem::setInterpolated(bool interp)";
    setRegisteredProperty(P_IS_INTERPOLATED, interp);
}

void IntensityDataItem::setXaxisTitle(QString xtitle)
{
    qDebug() << "IntensityDataItem::setXaxisTitle(QString xtitle)";
    getSubItems()[P_XAXIS]->setRegisteredProperty(BasicAxisItem::P_TITLE, xtitle);
}

void IntensityDataItem::setYaxisTitle(QString ytitle)
{
    qDebug() << "IntensityDataItem::setYaxisTitle(QString ytitle)";
    getSubItems()[P_YAXIS]->setRegisteredProperty(BasicAxisItem::P_TITLE, ytitle);
}

void IntensityDataItem::setAxesUnits(const QString &units)
{
    qDebug() << "IntensityDataItem::setAxesUnits(QString units)";
    Q_UNUSED(units);
    Q_ASSERT(0);
}
