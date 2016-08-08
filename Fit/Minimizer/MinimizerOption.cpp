// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOption.cpp
//! @brief     Implements class MinimizerOption
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOption.h"

MinimizerOption::MinimizerOption(const std::string &name)
    : m_name(name)
{

}

std::string MinimizerOption::name() const
{
    return m_name;
}

std::string MinimizerOption::description() const
{
    return m_description;
}

void MinimizerOption::setDescription(const std::string &description)
{
    m_description = description;
}

MinimizerOption::variant_t& MinimizerOption::value()
{
    return m_value;
}

MinimizerOption::variant_t &MinimizerOption::defaultValue()
{
    return m_default_value;
}
