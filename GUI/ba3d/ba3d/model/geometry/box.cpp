// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/box.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"

namespace RealSpace {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshBox() {
  float const D = .5f;

  xyz_vec vs_; vs_.reserve(8);
  for (float x : {-D, +D})
    for (float y : {-D, +D})
      for (float z : {-D, +D})
        vs_.append(Vector3D(x,y,z));

  Q_ASSERT(8 == vs_.count());

  xyz_vec vs; vs.reserve(36);

  vs.addQuad(vs_, 0, 2, 6, 4);
  vs.addQuad(vs_, 1, 5, 7, 3);
  vs.addQuad(vs_, 0, 1, 3, 2);
  vs.addQuad(vs_, 4, 6, 7, 5);
  vs.addQuad(vs_, 0, 4, 5, 1);
  vs.addQuad(vs_, 2, 3, 7, 6);

  Q_ASSERT(36 == vs.count());

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
