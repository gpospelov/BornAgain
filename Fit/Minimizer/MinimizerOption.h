// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerOption.h
//! @brief     Declares class MinimizerOption
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZEROPTION_H
#define MINIMIZEROPTION_H

#include "WinDllMacros.h"
#include <variant.hpp>
#include <string>

//! @class MinimizerOption
//! @ingroup fitting_internal
//! @brief The MinimizerOption class is intended to store a single option for minimization
//! algorithm. Int, double, string values are available.
//! Relies on https://github.com/mapbox/variant, will be switched to std::variant in C++-17.

class BA_CORE_API_ MinimizerOption
{
public:
    typedef mapbox::util::variant<int, double, std::string> variant_t;

    explicit MinimizerOption(const std::string &name = std::string());

    template<typename T>
    explicit MinimizerOption(const std::string &name, const T &t,
                             const std::string &descripion = std::string());

    std::string name() const;

    std::string description() const;
    void setDescription(const std::string &description);

    variant_t& value();
    variant_t& defaultValue();

    //! Returns the option's value
    template<typename T>
    T get() const;

    //! Returns the option's default value (i.e. used during construction)
    template<typename T>
    T getDefault() const;

private:
    std::string m_name;
    std::string m_description;
    variant_t m_value;
    variant_t m_default_value;
};


template<typename T>
MinimizerOption::MinimizerOption(const std::string &name, const T &t, const std::string &descripion)
{
    m_name = name;
    m_description = descripion;
    m_value = t;
    m_default_value = t;
}

template<typename T>
T MinimizerOption::get() const
{
    return m_value.get<T>();
}

template<typename T>
T MinimizerOption::getDefault() const
{
    return m_default_value.get<T>();
}

#endif // MINIMIZEROPTION_H

