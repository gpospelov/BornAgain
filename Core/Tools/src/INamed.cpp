// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamed.cpp
//! @brief     Implements INamed interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "INamed.h"

#include <utility>

INamed::INamed()
    : m_name {}
{
}

INamed::INamed(std::string name)
    : m_name { std::move(name) }
{
}

INamed::~INamed()
{
}

void INamed::setName(std::string name)
{
    m_name = std::move(name);
}

std::string INamed::getName() const
{
    return m_name;
}
