// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Configurable.h
//! @brief     Declares class Configurable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

#include "WinDllMacros.h"
#include "MinimizerOption.h"
#include <map>
#include <vector>
#include <memory>
#include <exception>

//! @class Configurable
//! @ingroup fitting_internal
//! @brief The Configurable class is a base for storing (int,double,string) options.

class BA_CORE_API_ Configurable {

public:
    typedef std::shared_ptr<MinimizerOption> option_t;

    Configurable(){}
    Configurable(const Configurable &other);
    Configurable& operator=(const Configurable& other);

    template<class T>
    option_t addOption(const std::string &optionName, T value,
                       const std::string &description = std::string());

    option_t option(const std::string &optionName);
    const option_t option(const std::string &optionName) const;

    template<class T>
    T optionValue(const std::string &optionName) const;

    //! Sets the value of option. Option should hold same value type already.
    template<class T>
    void setOptionValue(const std::string& optionName, T value);

    //! Returns string with all options using given delimeter
    std::string toOptionString(const std::string &delimeter=";") const;

private:
    bool exists(const std::string &name);
    void swapContent(Configurable& other);
    std::vector<std::shared_ptr<MinimizerOption>> m_options;
};

template<class T>
Configurable::option_t Configurable::addOption(const std::string &optionName, T value,
                                 const std::string &description)
{
    if(exists(optionName))
        throw std::runtime_error("Configurable::addOption() -> Error. Option '" + optionName +
                                 "' exists.");

    option_t result(new MinimizerOption(optionName, value, description));
    m_options.push_back(result);
    return result;
}

template<class T>
T Configurable::optionValue(const std::string &optionName) const
{
    return option(optionName)->get<T>();
}

template<class T>
void Configurable::setOptionValue(const std::string& optionName, T value)
{
    option(optionName)->value() = value;
    if(option(optionName)->value().which() != option(optionName)->defaultValue().which())
        throw std::runtime_error("Configurable::setOptionValue() -> Error. Attempt to set different"
                                 "type to option '"+optionName+"'");
}


#endif
