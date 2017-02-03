// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/HashKVector.h
//! @brief     Defines class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HASHKVECTOR_H
#define HASHKVECTOR_H

#include "Vectors3D.h"
#include <functional>

class HashKVector
{
public:
    HashKVector() {}
    ~HashKVector() {}

    size_t operator()(kvector_t kvec) const noexcept;
private:
    std::hash<double> m_double_hash;
};

#endif // HASHKVECTOR_H
