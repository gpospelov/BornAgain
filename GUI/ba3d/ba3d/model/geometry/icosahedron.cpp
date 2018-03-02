// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/icosahedron.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"
#include <qmath.h>
#include <QQuaternion>

namespace RealSpace {

Geometry::Mesh Geometry::meshIcosahedron() {
    const float GR = GoldenRatio;

    auto q = QQuaternion::rotationTo(-Vector3D::_z, Vector3D(0,1,-GR));

    Vertices vs_; vs_.reserve(12);
    for (float _1 : {-1, +1})
        for (float g : {-GR, +GR}) {
            vs_.append(q.rotatedVector(Vector3D(0, _1, g)));
            vs_.append(q.rotatedVector(Vector3D(_1, g, 0)));
            vs_.append(q.rotatedVector(Vector3D(g, 0, _1)));
        }

    Q_ASSERT(12 == vs_.count());

    // scale to circumscribed sphere
    float const F = .5f / vs_.at(0).length();
    for (auto& v : vs_)
        v = v*F;

    Vertices vs; vs.reserve(60);

    vs.addFan(vs_, {0, 1, 2, 6, 5, 7, 1});
    vs.addFan(vs_, {9, 3, 11, 10, 4, 8, 3});
    vs.addStrip(vs_, {1, 3, 7, 11, 5, 10, 6, 4, 2, 8, 1, 3});

    Q_ASSERT(60 == vs.count());

    return makeMesh(vs);
}

}  // namespace RealSpace
