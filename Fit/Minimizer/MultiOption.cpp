// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MultiOption.cpp
//! @brief     Implements class MultiOption
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiOption.h"

MultiOption::MultiOption(const std::string &name)
    : m_name(name)
{

}

std::string MultiOption::name() const
{
    return m_name;
}

std::string MultiOption::description() const
{
    return m_description;
}

void MultiOption::setDescription(const std::string &description)
{
    m_description = description;
}

MultiOption::variant_t& MultiOption::value()
{
    return m_value;
}

MultiOption::variant_t &MultiOption::defaultValue()
{
    return m_default_value;
}
