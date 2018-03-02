// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/HashKVector.cpp
//! @brief     Implements class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "HashKVector.h"

// Simple exclusive or of the std::hash<double> of its components
size_t HashKVector::operator()(kvector_t kvec) const noexcept
{
    return m_double_hash(kvec.x()) ^ m_double_hash(kvec.y()) ^ m_double_hash(kvec.z());
}
