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

ComboProperty::ComboProperty()
    : m_current_index(-1)
{}

ComboProperty::ComboProperty(const QStringList& values, const QString& current_value)
    : m_values(values), m_current_index(-1)
{
    if (!m_values.contains(current_value))
        throw GUIHelpers::Error("ComboProperty::ComboProperty() -> Error. Attempt to construct "
                                "property with initial values not from the list.");
    m_current_index = m_values.indexOf((current_value));
}

QString ComboProperty::getValue() const
{
    return m_current_index < 0 ? QString() : m_values.at(m_current_index);
}

void ComboProperty::setValue(const QString& name)
{
    if (!m_values.contains(name))
        throw GUIHelpers::Error("ComboProperty::setValue() -> Error. Combo doesn't contain "
                                "value " + name);
    m_current_index = m_values.indexOf(name);
}

QStringList ComboProperty::getValues() const
{
    return m_values;
}

//! Sets new list of values. Current value will be preserved, if exists in a new list.

void ComboProperty::setValues(const QStringList& values)
{
    Q_ASSERT(values.size());
    QString current = getValue();
    m_values = values;
    m_current_index = m_values.contains(current) ? m_values.indexOf(current) : 0;
}

//! returns list of tool tips for all values
QStringList ComboProperty::toolTips() const
{
    return m_tooltips;
}

void ComboProperty::setToolTips(const QStringList& tooltips)
{
    m_tooltips = tooltips;
}

int ComboProperty::currentIndex() const
{
    return m_current_index;
}

void ComboProperty::setCurrentIndex(int index)
{
    if(index <0 || index >= m_values.size())
        throw GUIHelpers::Error("ComboProperty::setCurrentIndex(int index) -> Error. "
                                "Invalid index");
    m_current_index = index;
}

ComboProperty&ComboProperty::operator<<(const QString& str)
{
    m_values.append(str);
    if (m_values.size())
        m_current_index = 0;
    return *this;
}

ComboProperty&ComboProperty::operator<<(const QStringList& str)
{
    m_values.append(str);
    if (m_values.size())
        m_current_index = 0;
    return *this;
}

bool ComboProperty::operator==(const ComboProperty& other) const
{
    if (m_current_index != other.m_current_index)
        return false;
    if (m_values != other.m_values)
        return false;
    return true;
}

bool ComboProperty::operator!=(const ComboProperty& other) const
{
    return !(*this == other);
}

bool ComboProperty::operator<(const ComboProperty& other) const
{
    return m_current_index < other.m_current_index && m_values.size() < other.m_values.size();
}

//! Returns a single string containing values delimited with ';'.

QString ComboProperty::stringOfValues() const
{
    return m_values.join(QStringLiteral(";"));
}

//! Sets values from the string containing delimeter ';'.

void ComboProperty::setStringOfValues(const QString& values)
{
    QString current = getValue();
    m_values = values.split(QStringLiteral(";"));
    m_current_index = m_values.contains(current) ? m_values.indexOf(current) : 0;
}

QVariant ComboProperty::getVariant() const
{
    QVariant result;
    result.setValue(*this);
    return result;
}
