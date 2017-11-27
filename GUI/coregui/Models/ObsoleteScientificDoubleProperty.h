// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ObsoleteScientificDoubleProperty.h
//! @brief     Defines class ObsoleteScientificDoubleProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETESCIENTIFICDOUBLEPROPERTY_H
#define OBSOLETESCIENTIFICDOUBLEPROPERTY_H

#include "WinDllMacros.h"
#include <QString>
#include <QVariant>

//! The ScientificDoubleProperty for SessionItem and PropertyEditor
//!
//! The reason is to have simple editor for doubles in scientific notation
//! in PropertyEditor instead of inconvenient QDoubleSpinBox

class BA_CORE_API_ ObsoleteScientificDoubleProperty
{
public:
    explicit ObsoleteScientificDoubleProperty(double value = 0) : m_value(value) { }

    double getValue() const { return m_value; }

    void setValue(double value) { m_value = value; }

    QString getText() const { return QString::number(m_value, 'g'); }

    QVariant getVariant() const
    {
        QVariant result;
        result.setValue(*this);
        return result;
    }

private:
    double m_value;
};

Q_DECLARE_METATYPE(ObsoleteScientificDoubleProperty)

#endif // OBSOLETESCIENTIFICDOUBLEPROPERTY_H

