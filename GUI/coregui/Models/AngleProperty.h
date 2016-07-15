// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/AngleProperty.h
//! @brief     Declares class AngleProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ANGLEPROPERTY_H
#define ANGLEPROPERTY_H

#include <QVariant>
#include <QStringList>

//! The AngleProperty keeps angle value together with units (radians, degrees)
//! in which the angle should be presented to the user.
class BA_CORE_API_ AngleProperty
{
public:
    AngleProperty(double angle_value = 0.0, const QString &angle_units = QString());
    ~AngleProperty(){}

    QString getUnits() const;
    void setUnits(const QString &units);

    bool inRadians() const;

    void setInRadians();

    bool inDegrees() const;

    void setInDegrees();

    double getValue() const;

    void setValue(double value);

    double getValueInRadians() const;

    QStringList getLabels() const;

    static QVariant Degrees(double value = 0.0);
    static QVariant Radians(double value = 0.0);

    QVariant getVariant() const;

private:
    double m_angle_in_radians;
    QString m_angle_units;
    static QStringList m_labels;
};

Q_DECLARE_METATYPE(AngleProperty)

#endif // ANGLEPROPERTY_H
