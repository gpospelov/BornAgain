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
#include "BornAgainNamespace.h"
#include "IDetector2D.h"
#include "SphericalDetector.h"
#include "RectangularDetector.h"
#include <QDebug>

const QString IntensityDataItem::P_AXES_UNITS = "Axes Units";
const QString IntensityDataItem::P_PROJECTIONS_FLAG = "Projections";
const QString IntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString IntensityDataItem::P_GRADIENT = "Gradient";
const QString IntensityDataItem::P_PROPERTY_PANEL_FLAG = "Property Panel Flag";
const QString IntensityDataItem::P_XAXIS = "x-axis";
const QString IntensityDataItem::P_YAXIS = "y-axis";
const QString IntensityDataItem::P_ZAXIS = "color-axis";


IntensityDataItem::IntensityDataItem()
    : ParameterizedItem(Constants::IntensityDataType)
{
//    registerProperty(OBSOLETE_P_NAME, Constants::IntensityDataType).setHidden();
    setItemName(Constants::IntensityDataType);

    ComboProperty units;
    registerProperty(P_AXES_UNITS, units.getVariant()).setHidden();

    registerProperty(P_PROJECTIONS_FLAG, false).setHidden();
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

    registerProperty(P_PROPERTY_PANEL_FLAG, false).setHidden();

    registerGroupProperty(P_XAXIS, Constants::BasicAxisType);
    getGroupItem(P_XAXIS)->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    registerGroupProperty(P_YAXIS, Constants::BasicAxisType);
    getGroupItem(P_YAXIS)->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    registerGroupProperty(P_ZAXIS, Constants::AmplitudeAxisType);
    getGroupItem(P_ZAXIS)->getPropertyAttribute(BasicAxisItem::P_NBINS).setHidden();

    addToValidChildren(Constants::MaskContainerType);
}

IntensityDataItem::~IntensityDataItem()
{

}

void IntensityDataItem::setOutputData(OutputData<double> *data)
{
    Q_ASSERT(data);
    m_data.reset(data);

    blockSignals(true);

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

    if(getXaxisTitle().isEmpty())
        setXaxisTitle(QString::fromStdString(m_data->getAxis(BornAgain::X_AXIS_INDEX)->getName()));

    if(getYaxisTitle().isEmpty())
        setYaxisTitle(QString::fromStdString(m_data->getAxis(BornAgain::Y_AXIS_INDEX)->getName()));

    blockSignals(false);
    qDebug() << "Emmitting intensityModified();";
    emit intensityModified();
}

double IntensityDataItem::getLowerX() const
{
    return getGroupItem(P_XAXIS)->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperX() const
{
    return getGroupItem(P_XAXIS)->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
}

double IntensityDataItem::getXmin() const
{
    Q_ASSERT(m_data);
    return m_data->getAxis(BornAgain::X_AXIS_INDEX)->getMin();
}

double IntensityDataItem::getXmax() const
{
    Q_ASSERT(m_data);
    return m_data->getAxis(BornAgain::X_AXIS_INDEX)->getMax();
}

double IntensityDataItem::getLowerY() const
{
    return getGroupItem(P_YAXIS)->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperY() const
{
    return getGroupItem(P_YAXIS)->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
}

double IntensityDataItem::getYmin() const
{
    Q_ASSERT(m_data);
    return m_data->getAxis(BornAgain::Y_AXIS_INDEX)->getMin();
}

double IntensityDataItem::getYmax() const
{
    Q_ASSERT(m_data);
        return m_data->getAxis(BornAgain::Y_AXIS_INDEX)->getMax();
}

double IntensityDataItem::getLowerZ() const
{
    return getGroupItem(P_ZAXIS)->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperZ() const
{
    return getGroupItem(P_ZAXIS)->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble();
}

QString IntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getRegisteredProperty(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool IntensityDataItem::isLogz() const
{
    return getGroupItem(P_ZAXIS)->getRegisteredProperty(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

bool IntensityDataItem::isInterpolated() const
{
    return getRegisteredProperty(P_IS_INTERPOLATED).toBool();
}

QString IntensityDataItem::getXaxisTitle() const
{
    return getGroupItem(P_XAXIS)->getRegisteredProperty(BasicAxisItem::P_TITLE).toString();
}

QString IntensityDataItem::getYaxisTitle() const
{
    return getGroupItem(P_YAXIS)->getRegisteredProperty(BasicAxisItem::P_TITLE).toString();
}

bool IntensityDataItem::isZAxisLocked() const
{
    return getGroupItem(P_ZAXIS)->getRegisteredProperty(AmplitudeAxisItem::P_LOCK_MIN_MAX).toBool();
}

void IntensityDataItem::setZAxisLocked(bool state)
{
    return getGroupItem(P_ZAXIS)->setRegisteredProperty(AmplitudeAxisItem::P_LOCK_MIN_MAX, state);
}

//! Sets the name of intensity data item from proposed name. This name will be used to save file
//! on disk, so special characters should be removed.
void IntensityDataItem::setNameFromProposed(const QString &proposed_name)
{
    QString valid_name = GUIHelpers::getValidFileName(proposed_name);
    setItemName(QString("data_%1_%2.int").arg(valid_name, QString::number(0)));
}

QString IntensityDataItem::getSelectedAxesUnits() const
{
    ComboProperty combo= getRegisteredProperty(IntensityDataItem::P_AXES_UNITS)
              .value<ComboProperty>();
    return combo.getValue();
}

void IntensityDataItem::setLowerX(double xmin)
{
    getGroupItem(P_XAXIS)->setRegisteredProperty(BasicAxisItem::P_MIN, xmin);
}

void IntensityDataItem::setUpperX(double xmax)
{
    getGroupItem(P_XAXIS)->setRegisteredProperty(BasicAxisItem::P_MAX, xmax);
}

void IntensityDataItem::setLowerY(double ymin)
{
    getGroupItem(P_YAXIS)->setRegisteredProperty(BasicAxisItem::P_MIN, ymin);
}

void IntensityDataItem::setUpperY(double ymax)
{
    getGroupItem(P_YAXIS)->setRegisteredProperty(BasicAxisItem::P_MAX, ymax);
}

void IntensityDataItem::setLowerAndUpperZ(double zmin, double zmax)
{
    if(getLowerZ() != zmin) {
        getGroupItem(P_ZAXIS)->setRegisteredProperty(BasicAxisItem::P_MIN, zmin);
    }
    if(getUpperZ() != zmax) {
        getGroupItem(P_ZAXIS)->setRegisteredProperty(BasicAxisItem::P_MAX, zmax);
    }
}

void IntensityDataItem::setLowerZ(double zmin)
{
    getGroupItem(P_ZAXIS)->setRegisteredProperty(BasicAxisItem::P_MIN, zmin);
}

void IntensityDataItem::setUpperZ(double zmax)
{
    getGroupItem(P_ZAXIS)->setRegisteredProperty(BasicAxisItem::P_MAX, zmax);
}

void IntensityDataItem::setLogz(bool logz)
{
    getGroupItem(P_ZAXIS)->setRegisteredProperty(AmplitudeAxisItem::P_IS_LOGSCALE, logz);
}

void IntensityDataItem::setInterpolated(bool interp)
{
    setRegisteredProperty(P_IS_INTERPOLATED, interp);
}

void IntensityDataItem::setXaxisTitle(QString xtitle)
{
    getGroupItem(P_XAXIS)->setRegisteredProperty(BasicAxisItem::P_TITLE, xtitle);
}

void IntensityDataItem::setYaxisTitle(QString ytitle)
{
    getGroupItem(P_YAXIS)->setRegisteredProperty(BasicAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void IntensityDataItem::setAxesRangeToData()
{
    setLowerX(getXmin());
    setUpperX(getXmax());
    setLowerY(getYmin());
    setUpperY(getYmax());
}
