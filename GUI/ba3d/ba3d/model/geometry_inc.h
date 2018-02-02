// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry_inc.h
//! @brief     Defines geometry namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_GEOMETRY_INC_H
#define BA3D_GEOMETRY_INC_H

#include "../def.h"
#include <QSharedPointer>

// include to use geometry basics, without details

namespace RealSpace {
//------------------------------------------------------------------------------

class Geometry;

typedef QSharedPointer<Geometry> shGeo;
typedef QWeakPointer<Geometry>   wkGeo;

// some useful constants:
extern const float GoldenRatio;
extern const float IcosahedronL2R;  // L/R conversion
extern const float DodecahedronL2R;

namespace GeometricID {

// Enum id for basic shapes
enum class BaseShape { Plane, Box, Sphere, Column,
                 Icosahedron, Dodecahedron, TruncatedBox,
                 Cuboctahedron };


// Real shapes will be parameterized by BaseShape enum and possibly two floats
struct Key {
    Key(BaseShape, float=0.0f, float=0.0f);

    bool operator==(Key const&) const;

    BaseShape id;
    float p1, p2;
};

// Hash functor for Key objects
struct KeyHash
{
    std::size_t operator()(const Key& key) const noexcept;
};

} // namespace GeometricID

//------------------------------------------------------------------------------
}
#endif
