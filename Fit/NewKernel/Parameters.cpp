// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Parameters.h
//! @brief     Defines class Parameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Parameters.h"
#include <stdexcept>

using namespace Fit;

void Parameters::add(const Parameter& par)
{
    if (exists(par.name()))
        throw std::runtime_error("Parameters::add() -> Error. Parameter with the name '"
                                 +par.name()+"' already exists.");

    m_parameters.push_back(par);
}

Parameters::const_iterator Parameters::begin() const
{
    return m_parameters.begin();
}

Parameters::const_iterator Parameters::end() const
{
    return m_parameters.end();
}

Parameters::iterator Parameters::begin()
{
    return m_parameters.begin();
}

Parameters::iterator Parameters::end()
{
    return m_parameters.end();
}

size_t Parameters::size() const
{
    return m_parameters.size();
}

bool Parameters::exists(const std::string& name) const
{
    for (const auto& par: m_parameters)
        if (par.name() == name)
            return true;
    return false;
}
