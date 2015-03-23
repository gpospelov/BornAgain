// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ComboProperty.h
//! @brief     Defines class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMBO_PROPERTY_H
#define COMBO_PROPERTY_H

#include "WinDllMacros.h"
#include <QStringList>
#include <QMetaType>
#include <QVariant>

//! The ComboProperty defines ParameterizedItem's property with a value
//! from predefined list.
//!
//! This is a light version of GroupProperty without SubItem mechanism
class BA_CORE_API_ ComboProperty
{
public:

    ComboProperty(const QStringList &values = QStringList(),
                  const QString &current_value = QString("Undefined"));
    virtual ~ComboProperty(){}
    QString getValue() const { return m_current_value; }

    void setValue(const QString &name);
    bool operator!=(const ComboProperty &other) {
        return (getValue() != other.getValue());
    }
    bool isDefined() { return m_current_value != QStringLiteral("Undefined"); }

    QStringList getValues() const { return m_values;}

    int index() const;
    int toIndex(const QString &value) const;
    QString toString(int index) const;

    inline ComboProperty &operator<<(const QString &str)
    {
        m_values.append(str);
        if(m_values.size()) m_current_value=m_values.at(0);
        return *this;
    }

    QVariant getVariant() const {
        QVariant result;
        result.setValue(*this);
        return result;
    }

    int getIndex() const { return toIndex(m_current_value); }

    QString getCachedValue() const { return m_cached_value; }
    void setCachedValue(const QString &name);

private:
    QStringList m_values;
    QString m_current_value;
    QString m_cached_value;  // for comboboxes with dynamically generated value lists
};

Q_DECLARE_METATYPE(ComboProperty)



#endif
