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
#include <sstream>
#include <cmath>

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

std::vector<double> Parameters::values() const
{
    std::vector<double> result;
    for (const auto& par: m_parameters)
        result.push_back(par.value());
    return result;
}

void Parameters::setValues(const std::vector<double>& values)
{
    check_array_size(values);

    size_t index = 0;
    for (auto& par: m_parameters) {
        if (std::isnan(values[index]))
            throw std::runtime_error("Parameters::setValues() -> Error."
                                     " Attempt to set nan '"+par.name() + std::string("'."));
        if (std::isinf(values[index]))
            throw std::runtime_error("Parameters::setValues() -> Error. Attempt to set inf '"+
                                      par.name()  + std::string("'."));
        par.setValue(values[index]);
        ++index;
    }
}

std::vector<double> Parameters::errors() const
{
    std::vector<double> result;
    for (const auto& par: m_parameters)
        result.push_back(par.error());
    return result;
}

void Parameters::setErrors(const std::vector<double>& errors)
{
    check_array_size(errors);
    size_t index = 0;
    for (auto& par: m_parameters)
        par.setError(errors[++index]);
}

bool Parameters::exists(const std::string& name) const
{
    for (const auto& par: m_parameters)
        if (par.name() == name)
            return true;
    return false;
}

void Parameters::check_array_size(const std::vector<double>& values) const
{
    if (values.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "Parameters::check_array_size() -> Error. Size of input array "
             << values.size() << " doesn't mach number of fit parameters "
             << m_parameters.size() << "." << std::endl;
        throw std::runtime_error(ostr.str());
    }
}
