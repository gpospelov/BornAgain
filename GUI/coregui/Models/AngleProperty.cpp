// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/AngleProperty.cpp
//! @brief     Implements class AngleProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "AngleProperty.h"
#include "Units.h"
#include "GUIHelpers.h"
#include "item_constants.h"

QStringList AngleProperty::m_labels = QStringList()
        << Constants::UnitsDegrees << Constants::UnitsRadians;

//AngleProperty::AngleProperty(double angle_value, AngleUnits angle_units)
//    : m_angle_in_radians(0)
//    , m_angle_units(angle_units)
//{
//    if(m_angle_units == AngleProperty::Radians) {
//        m_angle_in_radians = angle_value;
//    }
//    else {
//        m_angle_in_radians = Units::deg2rad(angle_value);
//    }
//}


AngleProperty::AngleProperty(double angle_value, const QString &angle_units)
    : m_angle_in_radians(0)
    , m_angle_units(angle_units)
{
    if(m_angle_units == Constants::UnitsRadians) {
        m_angle_in_radians = angle_value;
    }
    else if(m_angle_units == Constants::UnitsDegrees){
        m_angle_in_radians = Units::deg2rad(angle_value);
    }
    else {
        throw GUIHelpers::Error("AngleProperty::AngleProperty() -> Error. Unknown units");
    }
}


//AngleProperty::AngleUnits AngleProperty::getUnits() const
//{
//    return m_angle_units;
//}


//void AngleProperty::setUnits(AngleUnits units)
//{
//    m_angle_units = units;
//}


QString AngleProperty::getUnits() const
{
//    return m_labels[m_angle_units];
    return m_angle_units;
}

void AngleProperty::setUnits(const QString &units)
{
    if(!m_labels.contains(units))
        throw GUIHelpers::Error("AngleProperty::setUnitsString() -> Error. Unknown units");

    m_angle_units = units;
//    if(units == Constants::UnitsDegrees) {
//        m_angle_units = Degrees;
//    }
//    else {
//        m_angle_units = Radians;
//    }
}


bool AngleProperty::inRadians() const
{
    return m_angle_units == Constants::UnitsRadians;
}


void AngleProperty::setInRadians()
{
    m_angle_units = Constants::UnitsRadians;
}


bool AngleProperty::inDegrees() const
{
    return m_angle_units == Constants::UnitsDegrees;
}


void AngleProperty::setInDegrees()
{
    m_angle_units = Constants::UnitsDegrees;
}


double AngleProperty::getValue() const
{
//    return (m_angle_units == Radians ? m_angle_in_radians : Units::rad2deg(m_angle_in_radians));
    return (m_angle_units == Constants::UnitsRadians ? m_angle_in_radians : Units::rad2deg(m_angle_in_radians));
}


void AngleProperty::setValue(double value)
{
    if(m_angle_units == Constants::UnitsRadians) {
        m_angle_in_radians = value;
    }
    else {
        m_angle_in_radians = Units::deg2rad(value);
    }
}


double AngleProperty::getValueInRadians() const
{
    return m_angle_in_radians;
}


QStringList AngleProperty::getLabels() const
{
    return m_labels;
}

QVariant AngleProperty::Degrees(double value)
{
    AngleProperty angle(value, Constants::UnitsDegrees);
    QVariant result;
    result.setValue(angle);
    return result;
}

QVariant AngleProperty::Radians(double value)
{
    AngleProperty angle(value, Constants::UnitsRadians);
    QVariant result;
    result.setValue(angle);
    return result;
}


QVariant AngleProperty::getVariant() const
{
    QVariant result;
    result.setValue(*this);
    return result;
}
