// GPL3; https://github.com/jburle/ba3d

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
// eof
