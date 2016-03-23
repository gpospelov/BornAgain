// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/IntensityDataItem.cpp
//! @brief     Implements class IntensityDataItem
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
const QString IntensityDataItem::T_MASKS = "Mask tag";


IntensityDataItem::IntensityDataItem()
    : SessionItem(Constants::IntensityDataType)
{
//    registerProperty(OBSOLETE_P_NAME, Constants::IntensityDataType).setHidden();
    setItemName(Constants::IntensityDataType);

    ComboProperty units;
    addProperty(P_AXES_UNITS, units.getVariant())->setVisible(false);

    addProperty(P_PROJECTIONS_FLAG, false)->setVisible(false);
    addProperty(P_IS_INTERPOLATED, true);

    ComboProperty gradient;

    gradient << Constants::GRADIENT_GRAYSCALE << Constants::GRADIENT_HOT
             << Constants::GRADIENT_COLD << Constants::GRADIENT_NIGHT
             << Constants::GRADIENT_CANDY << Constants::GRADIENT_GEOGRAPHY
             << Constants::GRADIENT_ION << Constants::GRADIENT_THERMAL
             << Constants::GRADIENT_POLAR << Constants::GRADIENT_SPECTRUM
             << Constants::GRADIENT_JET << Constants::GRADIENT_HUES;
    gradient.setValue(Constants::GRADIENT_JET);
    addProperty(P_GRADIENT, gradient.getVariant());

    addProperty(P_PROPERTY_PANEL_FLAG, false)->setVisible(false);

    addGroupProperty(P_XAXIS, Constants::BasicAxisType);
    getGroupItem(P_XAXIS)->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    addGroupProperty(P_YAXIS, Constants::BasicAxisType);
    getGroupItem(P_YAXIS)->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    addGroupProperty(P_ZAXIS, Constants::AmplitudeAxisType);
    getGroupItem(P_ZAXIS)->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    registerTag(T_MASKS, 0, -1, QStringList() << Constants::MaskContainerType);
    setDefaultTag(T_MASKS);
}

IntensityDataItem::~IntensityDataItem()
{

}

void IntensityDataItem::setOutputData(OutputData<double> *data)
{
    Q_ASSERT(data);
    m_data.reset(data);

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

    qDebug() << "Emmitting intensityModified();";
    emitDataChanged();
}

double IntensityDataItem::getLowerX() const
{
    return getGroupItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperX() const
{
    return getGroupItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
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
    return getGroupItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperY() const
{
    return getGroupItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
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
    return getGroupItem(P_ZAXIS)->getItemValue(BasicAxisItem::P_MIN).toDouble();
}

double IntensityDataItem::getUpperZ() const
{
    return getGroupItem(P_ZAXIS)->getItemValue(BasicAxisItem::P_MAX).toDouble();
}

QString IntensityDataItem::getGradient() const
{
    ComboProperty combo_property = getItemValue(P_GRADIENT).value<ComboProperty>();
    return combo_property.getValue();
}

bool IntensityDataItem::isLogz() const
{
    return getGroupItem(P_ZAXIS)->getItemValue(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

bool IntensityDataItem::isInterpolated() const
{
    return getItemValue(P_IS_INTERPOLATED).toBool();
}

QString IntensityDataItem::getXaxisTitle() const
{
    return getGroupItem(P_XAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString IntensityDataItem::getYaxisTitle() const
{
    return getGroupItem(P_YAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

bool IntensityDataItem::isZAxisLocked() const
{
    return getGroupItem(P_ZAXIS)->getItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX).toBool();
}

void IntensityDataItem::setZAxisLocked(bool state)
{
    return getGroupItem(P_ZAXIS)->setItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX, state);
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
    ComboProperty combo= getItemValue(IntensityDataItem::P_AXES_UNITS)
              .value<ComboProperty>();
    return combo.getValue();
}

void IntensityDataItem::setLowerX(double xmin)
{
    getGroupItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MIN, xmin);
}

void IntensityDataItem::setUpperX(double xmax)
{
    getGroupItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MAX, xmax);
}

void IntensityDataItem::setLowerY(double ymin)
{
    getGroupItem(P_YAXIS)->setItemValue(BasicAxisItem::P_MIN, ymin);
}

void IntensityDataItem::setUpperY(double ymax)
{
    getGroupItem(P_YAXIS)->setItemValue(BasicAxisItem::P_MAX, ymax);
}

void IntensityDataItem::setLowerAndUpperZ(double zmin, double zmax)
{
    if(getLowerZ() != zmin) {
        getGroupItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MIN, zmin);
    }
    if(getUpperZ() != zmax) {
        getGroupItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MAX, zmax);
    }
}

void IntensityDataItem::setLowerZ(double zmin)
{
    getGroupItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MIN, zmin);
}

void IntensityDataItem::setUpperZ(double zmax)
{
    getGroupItem(P_ZAXIS)->setItemValue(BasicAxisItem::P_MAX, zmax);
}

void IntensityDataItem::setLogz(bool logz)
{
    getGroupItem(P_ZAXIS)->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, logz);
}

void IntensityDataItem::setInterpolated(bool interp)
{
    setItemValue(P_IS_INTERPOLATED, interp);
}

void IntensityDataItem::setXaxisTitle(QString xtitle)
{
    getGroupItem(P_XAXIS)->setItemValue(BasicAxisItem::P_TITLE, xtitle);
}

void IntensityDataItem::setYaxisTitle(QString ytitle)
{
    getGroupItem(P_YAXIS)->setItemValue(BasicAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void IntensityDataItem::setAxesRangeToData()
{
    setLowerX(getXmin());
    setUpperX(getXmax());
    setLowerY(getYmin());
    setUpperY(getYmax());
}
