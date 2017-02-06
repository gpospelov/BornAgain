// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/HashKVector.cpp
//! @brief     Implements class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "HashKVector.h"

// Simple exclusive or of the std::hash<double> of its components
size_t HashKVector::operator()(kvector_t kvec) const noexcept
{
    return m_double_hash(kvec.x()) ^ m_double_hash(kvec.y()) ^ m_double_hash(kvec.z());
}

size_t Hash2Doubles::operator()(std::pair<double, double> doubles) const noexcept
{
    return m_double_hash(doubles.first) ^ m_double_hash(doubles.second);
}
