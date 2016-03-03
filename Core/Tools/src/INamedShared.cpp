// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamedShared.cpp
//! @brief     Implements INamedShared interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "INamedShared.h"
#include <utility>

INamedShared::INamedShared()
    : m_name {}
{
}

INamedShared::INamedShared(std::string name)
    : m_name ( std::move(name) )
{
}

INamedShared::~INamedShared()
{
}

void INamedShared::setName(std::string name)
{
    m_name = std::move(name);
}

std::string INamedShared::getName() const
{
    return m_name;
}
