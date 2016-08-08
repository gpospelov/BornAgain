// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Configurable.cpp
//! @brief     Implements class Configurable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Configurable.h"

//! Returns true if option with such name already exists.
Configurable::Configurable(const Configurable &other)
{
    for(auto option: other.m_options)
        m_options.push_back(option_t(new MinimizerOption(*option)));
}

Configurable &Configurable::operator=(const Configurable &other)
{
    if (this != &other) {
        Configurable tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

Configurable::option_t Configurable::option(const std::string &optionName)
{
    for(auto option: m_options) {
        if(option->name() == optionName)
            return option;
    }

    throw std::runtime_error("Configurable::getOption() -> Error. No option with name '"
                             + optionName + "'.");
}

bool Configurable::exists(const std::string &name)
{
    for(auto option: m_options) {
        if(option->name() == name)
            return true;
    }
    return false;
}

void Configurable::swapContent(Configurable &other)
{
    std::swap(m_options, other.m_options);
}
