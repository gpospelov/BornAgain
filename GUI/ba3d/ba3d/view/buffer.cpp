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

namespace RealSpace {
//------------------------------------------------------------------------------

Buffer::Buffer(Geometry const& geometry) {
  initializeOpenGLFunctions();

  auto &mesh  = geometry.m_mesh;
  vertexCount = mesh.count();

  QOpenGLVertexArrayObject::Binder __(&vao);

  glBuffer.create();
  glBuffer.bind();
  glBuffer.allocate(mesh.constData(), vertexCount * int(sizeof(Geometry::Vert_Normal)));

  glEnableVertexAttribArray(0); // vertices
  glEnableVertexAttribArray(1); // normals

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(Vector3D), nullptr);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*sizeof(Vector3D), reinterpret_cast<void *>(sizeof(Vector3D)));
}

void Buffer::draw() {
  QOpenGLVertexArrayObject::Binder __(&vao);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

//------------------------------------------------------------------------------
}
