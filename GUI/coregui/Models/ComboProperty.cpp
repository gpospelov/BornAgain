// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.cpp
//! @brief     Implements class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComboProperty.h"
#include "GUIHelpers.h"

ComboProperty::ComboProperty(const QStringList& values, const QString& current_value)
    : m_values(values), m_current_value(current_value)
{
    if (!m_values.contains(m_current_value))
        throw GUIHelpers::Error("ComboProperty::ComboProperty() -> Error. Attempt to construct "
                                "property with initial values not from the list.");
}

void ComboProperty::setValue(const QString& name)
{
    if (!m_values.contains(name))
        throw GUIHelpers::Error("ComboProperty::setValue() -> Error. Combo doesn't contain "
                                "value " + name);
    m_current_value = name;
}

//! Sets new list of values. Current value will be preserved, if exists in a new list.

void ComboProperty::setValues(const QStringList& values)
{
    QString current = getValue();

    m_values = values;

    // if no currentValue in the new list of values, take first value from the list
    if(!m_values.contains(current) && !current.isEmpty())
        setValue(m_values.front());
}

//! returns list of tool tips for all values
QStringList ComboProperty::getToolTips() const
{
    return m_values_tooltips;
}

void ComboProperty::setToolTips(const QStringList& tooltips)
{
    m_values_tooltips = tooltips;
}

int ComboProperty::index() const
{
    return toIndex(m_current_value);
}

int ComboProperty::toIndex(const QString& value) const
{
    QStringList name_list = getValues();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString ComboProperty::toString(int index) const
{
    QStringList name_list = getValues();
    if (index < 0 || index >= name_list.size()) {
        return QString();
    }
    return name_list[index];
}

bool ComboProperty::operator==(const ComboProperty& other) const
{
    if (m_current_value != other.m_current_value)
        return false;
    if (!GUIHelpers::isTheSame(m_values, other.m_values))
        return false;
    return true;
}

bool ComboProperty::operator<(const ComboProperty& other) const
{
    return m_current_value < other.m_current_value && m_values.size() < other.m_values.size();
}

//! Sets values from the string containing delimeter ';'.

void ComboProperty::setStringOfValues(const QString& values)
{
    QString currentValue = getValue();

    m_values = values.split(QStringLiteral(";"));

    // if no currentValue in the new list of values, take first value from the list
    if(!m_values.contains(currentValue) && !currentValue.isEmpty())
        setValue(m_values.front());
}

//! Returns a single string containing values delimited with ';'.

QString ComboProperty::stringOfValues() const
{
    return m_values.join(QStringLiteral(";"));
}
