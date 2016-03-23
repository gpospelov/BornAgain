// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ComboProperty.cpp
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


ComboProperty::ComboProperty(const QStringList &values, const QString &current_value)
    : m_values(values)
    , m_current_value(current_value)
    , m_cache_contains_GUI_value(true)
{
}

void ComboProperty::setValue(const QString &name)
{
    Q_ASSERT(m_values.contains(name));
    m_current_value = name;
}

int ComboProperty::index() const
{
    return toIndex(m_current_value);
}

int ComboProperty::toIndex(const QString &value) const
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
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}

void ComboProperty::setCachedValue(const QString &name)
{
    m_cached_value = name;
}
