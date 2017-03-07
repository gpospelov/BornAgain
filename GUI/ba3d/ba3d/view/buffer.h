// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_BUFFER_H
#define BA3D_BUFFER_H

#include "../def.h"
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

namespace ba3d {
//------------------------------------------------------------------------------

class Geometry;

// GL buffer
class Buffer final : protected QOpenGLFunctions {
public:
  Buffer(Geometry const&);
  void draw();

private:
  int vertexCount;
  QOpenGLVertexArrayObject vao; QOpenGLBuffer glBuffer;
};

//------------------------------------------------------------------------------
}
#endif
// eof
