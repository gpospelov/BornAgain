// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.h
//! @brief     Defines class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMBOPROPERTY_H
#define COMBOPROPERTY_H

#include "WinDllMacros.h"
#include <QStringList>
#include <QVariant>

//! The ComboProperty defines SessionItem's property with a value
//! from predefined list.
//!
//! This is a light version of GroupProperty without SubItem mechanism
class BA_CORE_API_ ComboProperty
{
public:
    ComboProperty();
    ComboProperty(const QStringList& values, const QString& current_value);

    QString getValue() const;
    void setValue(const QString& name);

    QStringList getValues() const;
    void setValues(const QStringList& values);

    QStringList toolTips() const;
    void setToolTips(const QStringList& tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    ComboProperty& operator<<(const QString& str);
    ComboProperty& operator<<(const QStringList& str);
    bool operator==(const ComboProperty& other) const;
    bool operator!=(const ComboProperty& other) const;
    bool operator<(const ComboProperty& other) const;

    QString stringOfValues() const;
    void setStringOfValues(const QString& values);

    QVariant getVariant() const;

private:
    QStringList m_values;
    QStringList m_tooltips;
    int m_current_index;
};

Q_DECLARE_METATYPE(ComboProperty)

#endif // COMBOPROPERTY_H
