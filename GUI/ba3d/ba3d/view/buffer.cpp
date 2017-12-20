// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/buffer.cpp
//! @brief     Implements Buffer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "buffer.h"
#include "../model/geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Buffer::Buffer(Geometry const& geometry) {
  initializeOpenGLFunctions();

  auto &mesh  = geometry.mesh;
  vertexCount = mesh.count();

  QOpenGLVertexArrayObject::Binder __(&vao);

  glBuffer.create();
  glBuffer.bind();
  glBuffer.allocate(mesh.constData(), vertexCount * int(sizeof(Geometry::vn_t)));

  glEnableVertexAttribArray(0); // vertices
  glEnableVertexAttribArray(1); // normals

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(xyz), nullptr);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*sizeof(xyz), reinterpret_cast<void *>(sizeof(xyz)));
}

void Buffer::draw() {
  QOpenGLVertexArrayObject::Binder __(&vao);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

//------------------------------------------------------------------------------
}
