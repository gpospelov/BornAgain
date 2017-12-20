// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/plane.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshPlane() {
  flt const D = .5f;

  xyz_vec vs; vs.reserve(4);
  vs.addQuad({+D,+D, 0}, {-D,+D, 0}, {-D,-D, 0}, {+D,-D, 0});

  ENSURE(4 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
