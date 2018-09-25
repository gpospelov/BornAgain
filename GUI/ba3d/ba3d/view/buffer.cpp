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

namespace
{
    const float cx = 180; // multiplication scale for controlling how long the axes shall be in xy
    const float cz = 100; // multiplication scale for controlling how long the axes shall be in z
}

namespace RealSpace {

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

Buffer3DAxes::Buffer3DAxes() {
    initializeOpenGLFunctions();

     QOpenGLVertexArrayObject::Binder __(&vao3DAxes);

    // vertices for drawing each line (also arrows) in the right-handed 3D coordinate axes
    const GLfloat vertices3DAxes[] = {
            0.00f,     0.00f,     0.00f,
         cx*1.00f,     0.00f,     0.00f,
         cx*1.00f,     0.00f,     0.00f,
         cx*0.95f,     0.00f,  cx*0.02f,
         cx*1.00f,     0.00f,     0.00f,
         cx*0.95f,     0.00f, cx*-0.02f,
         cx*1.00f,     0.00f,     0.00f,
         cx*0.95f,  cx*0.02f,     0.00f,
         cx*1.00f,     0.00f,     0.00f,
         cx*0.95f, cx*-0.02f,     0.00f,

            0.00f,     0.00f,     0.00f,
            0.00f,  cx*1.00f,     0.00f,
            0.00f,  cx*1.00f,     0.00f,
            0.00f,  cx*0.95f,  cx*0.02f,
            0.00f,  cx*1.00f,     0.00f,
            0.00f,  cx*0.95f, cx*-0.02f,
            0.00f,  cx*1.00f,     0.00f,
         cx*0.02f,  cx*0.95f,     0.00f,
            0.00f,  cx*1.00f,     0.00f,
        cx*-0.02f,  cx*0.95f,     0.00f,

            0.00f,     0.00f,     0.00f,
            0.00f,     0.00f,  cz*1.00f,
            0.00f,     0.00f,  cz*1.00f,
         cz*0.02f,     0.00f,  cz*0.95f,
            0.00f,     0.00f,  cz*1.00f,
        cz*-0.02f,     0.00f,  cz*0.95f,
            0.00f,     0.00f,  cz*1.00f,
            0.00f,  cz*0.02f,  cz*0.95f,
            0.00f,     0.00f,  cz*1.00f,
            0.00f, cz*-0.02f,  cz*0.95f,
    };

    vertexCount3DAxes = 30;

    glBuffer3DAxes.create();
    glBuffer3DAxes.bind();
    glBuffer3DAxes.allocate(vertices3DAxes, int(sizeof (vertices3DAxes)));

    glEnableVertexAttribArray(0); // vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
}

void Buffer3DAxes::draw3DAxes() {
    QOpenGLVertexArrayObject::Binder __(&vao3DAxes);
    glDrawArrays(GL_LINES, 0, vertexCount3DAxes);
}

}  // namespace RealSpace
