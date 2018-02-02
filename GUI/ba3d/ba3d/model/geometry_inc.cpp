// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry_inc.cpp
//! @brief     Implements geometry namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "geometry_inc.h"
#include <qmath.h>

namespace RealSpace {
//------------------------------------------------------------------------------

const float GoldenRatio     = float(1 + qSqrt(5)) / 2;
const float IcosahedronL2R  = float(4 / (10 + 2*qSqrt(5)));
const float DodecahedronL2R = float(4 / qSqrt(3) / (1+qSqrt(5)));

//------------------------------------------------------------------------------

GeometricID::Key::Key(GeometricID::BaseShape id) : Key(id, 0, 0) {}

GeometricID::Key::Key(GeometricID::BaseShape id, float p1) : Key(id, p1, 0) {}

GeometricID::Key::Key(BaseShape id_, float p1_, float p2_)
  : id(id_), p1(p1_), p2(p2_) {
}

bool GeometricID::Key::operator==(Key const& that) const {
  return id == that.id && p1 == that.p1 && p2 == that.p2;
}

uint GeometricID::qHash(GeometricID::Key const& key) {
  // the hash is simply a bitwise superposition of id, p1, p2
  union {
    float         f;
    quint32       u;
    GeometricID::BaseShape i;
  } id, p1, p2;

  id.i = key.id; p1.f = key.p1; p2.f = key.p2;
  return id.u | p1.u | p2.u;
}

//------------------------------------------------------------------------------
}
