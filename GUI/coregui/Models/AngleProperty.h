#ifndef ANGLEPROPERTY_H
#define ANGLEPROPERTY_H


#include <QStringList>
#include <QMetaType>
#include <QVariant>
#include "Units.h"

//! The AngleProperty keeps angle value together with units (radias, degrees)
//! in which the angle should be presented to the user.
class AngleProperty
{
public:
    enum AngleUnits { Radians, Degrees};

    AngleProperty(double angle_value = 0.0, AngleUnits angle_units = Radians);
    ~AngleProperty(){}

    bool inRadians() const;

    void setInRadians();

    bool inDegrees() const;

    void setInDegrees();

    double getValue() const;

    void setValue(double value);

    double getValueInRadians() const;

    QVariant getVariant() const;

private:
    double m_angle_in_radians;
    AngleUnits m_angle_units;
};


inline AngleProperty::AngleProperty(double angle_value, AngleUnits angle_units)
    : m_angle_in_radians(0)
    , m_angle_units(angle_units)
{
    if(m_angle_units == AngleProperty::Radians) {
        m_angle_in_radians = angle_value;
    }
    else {
        m_angle_in_radians = Units::deg2rad(angle_value);
    }
}

inline bool AngleProperty::inRadians() const
{
    return m_angle_units == Radians;
}

inline void AngleProperty::setInRadians()
{
    m_angle_units = Radians;
}

inline bool AngleProperty::inDegrees() const
{
    return m_angle_units == Degrees;
}

inline void AngleProperty::setInDegrees()
{
    m_angle_units = Degrees;
}

inline double AngleProperty::getValue() const
{
    return (m_angle_units == Radians ? m_angle_in_radians : Units::rad2deg(m_angle_in_radians));
}

inline void AngleProperty::setValue(double value)
{
    if(m_angle_units == Radians) {
        m_angle_in_radians = value;
    }
    else {
        m_angle_in_radians = Units::deg2rad(value);
    }
}

inline double AngleProperty::getValueInRadians() const
{
    return m_angle_in_radians;
}

inline QVariant AngleProperty::getVariant() const
{
    QVariant result;
    result.setValue(*this);
    return result;
}

Q_DECLARE_METATYPE(AngleProperty)



#endif
