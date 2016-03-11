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

template class INamedTemplate<ICloneable>;
template class INamedTemplate<IShareable>;

template <typename T>
INamedTemplate<T>::INamedTemplate()
    : m_name {}
{
}

template <typename T>
INamedTemplate<T>::INamedTemplate(std::string name)
    : m_name ( std::move(name) )
{
}

template <typename T>
INamedTemplate<T>::~INamedTemplate()
{
}

template <typename T>
void INamedTemplate<T>::setName(std::string name)
{
    m_name = std::move(name);
}

template <typename T>
std::string INamedTemplate<T>::getName() const
{
    return m_name;
}

