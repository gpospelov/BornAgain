// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/canvas.cpp
//! @brief     Implements Canvas class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "canvas.h"
#include "buffer.h"
#include "camera.h"
#include "program.h"
#include "../model/geometry.h"
#include "../model/model.h"

#include <QMouseEvent>
#include <qmath.h>
#include <QMessageBox>
#include <math.h>

namespace {
    const float zoom_in_scale = 1.25f;
    const float zoom_out_scale = 0.8f;

    const float rot_speed_h = 0.4f; // camera rotation speed in horizontal direction
    const float rot_speed_v = 0.4f; // camera rotation speed in vertical direction
}

namespace RealSpace {

Canvas::Canvas()
    : aspectRatio(1), colorBgR(1), colorBgG(1), colorBgB(1)
    , camera(nullptr), program(nullptr), model(nullptr) {
    connect(&geometryStore(), &GeometryStore::deletingGeometry,
            this, &Canvas::releaseBuffer);
}

Canvas::~Canvas() {
    releaseBuffers();
}

void Canvas::setBgColor(QColor const& c) {
    colorBgR = float(c.redF());
    colorBgG = float(c.greenF());
    colorBgB = float(c.blueF());
    update();
}

void Canvas::setCamera(Camera* c) {
    camera = c;
    setCamera();
}

void Canvas::setProgram(Program* p) {
    program = p;
    if (program)
        program->needsInit();
    update();
}

void Canvas::setModel(Model* m) {
    releaseBuffers();

    disconnect(modelUpdated);
    model = m;
    modelUpdated = connect(model, &Model::updated, [this](bool withEye) {
        if (withEye)
            setCamera();
        else
            update();
    });

    setCamera();
}

Model* Canvas::getModel() {
    return model;
}

void Canvas::setCamera(bool full) {
    if (camera) {
        camera->setAspectRatio(aspectRatio);
        if (full && model)
            camera->lookAt(model->defCamPos);
    }

    update();
}

void Canvas::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Canvas::resizeGL(int w, int h) {
    int w1 = qMax(1, w), h1 = qMax(1, h);
    viewport.setRect(0, 0, w1, h1);
    aspectRatio = float(w1) / float(h1);
    setCamera(false);
}

void Canvas::paintGL() {
    glClearColor(colorBgR, colorBgG, colorBgB, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera && program && model) {
        program->init();
        program->bind();
        program->set(*camera);

        // opaque objects
        model->draw(*this);

        // transparent objects
        glEnable(GL_BLEND); glDepthMask(false);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model->drawBlend(*this);
        glDisable(GL_BLEND); glDepthMask(true);

        program->release();
    }
}

QVector3D Canvas::unproject(QPoint const& p) {
    float x = p.x(), y = viewport.height() - p.y();
    return QVector3D(x, y, 1).unproject(matModel, matProj, viewport);
}

void Canvas::mousePressEvent(QMouseEvent* e) {
    switch (e->button())  {
    case Qt::LeftButton:
        mouseButton = btnTURN;
        break;
    case Qt::RightButton:
        mouseButton = btnZOOM;
        break;
    default:
        mouseButton = btnNONE;
        break;
    }

    if (camera) {
        matModel = camera->matModel;
        matProj  = camera->matProj;
        e_last = e->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* e) {
    if (camera) {
        float delta_x = e->pos().x() - e_last.x();
        float delta_y = e->pos().y() - e_last.y();

        switch (mouseButton) {
        case btnTURN: {
            if(delta_x != 0)
                horizontalCameraTurn(-delta_x*rot_speed_h); // -ve for consistency with Blender

            if(delta_y != 0)
                verticalCameraTurn(-delta_y*rot_speed_v); // -ve for consistency with Blender

            e_last = e->pos();
            break;
        }
        case btnZOOM: {
            float d = (e->y() - e_last.y()) / float(viewport.height());
            camera->zoomBy(1+d);
            break;
        }
        default:
            break;
        }

        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent*) {
    if (camera) {
        camera->endTransform(true);
        update();
    }
}

void Canvas::wheelEvent(QWheelEvent* e)
{
    if (camera)
    {
        if(e->delta() < 0)
        {
            //Zoom in
            camera->zoomBy(zoom_in_scale);
        }
        else
        {
            //Zoom out
            camera->zoomBy(zoom_out_scale);
        }
        camera->endTransform(true);
        update();
    }
    e->accept(); // disabling the event from propagating further to the parent widgets
}

void Canvas::releaseBuffer(Geometry const* g) {
    delete buffers.take(g);
}

void Canvas::releaseBuffers() {
    for (auto b: buffers.values())
        delete b;
    buffers.clear();
}

void Canvas::draw(QColor const& color, QMatrix4x4 const& mat, Geometry const& geo) {
    auto it = buffers.find(&geo);
    Buffer* buf;
    if (buffers.end() == it)
        buffers.insert(&geo, buf = new Buffer(geo));  // created on demand
    else
        buf = *it;

    Q_ASSERT(program);
    program->set(color);
    program->set(mat);
    buf->draw();
}

void Canvas::defaultView()
{
    if (model){
        // Default view
        camera->lookAt(RealSpace::Camera::Position(RealSpace::Vector3D(0, -140, 90),  // eye
                                                   RealSpace::Vector3D(0, 0, 0),      // center
                                                   RealSpace::Vector3D::_z));         // up
        camera->endTransform(true);
        update();
    }
    else{
        canvasHintMessageBox();
    }
}

void Canvas::sideView()
{
    if (model){
        // Edge view
        camera->lookAt(RealSpace::Camera::Position(
                                   RealSpace::Vector3D(0, -140, 0),   // eye
                                   RealSpace::Vector3D(0, 0, 0),      // center
                                   RealSpace::Vector3D::_z));         // up
        camera->endTransform(true);
        update();
    }
    else{
        canvasHintMessageBox();
    }
}

void Canvas::topView()
{
    if (model){
        // Top view
        // Setting a tiny offset in x value of eye such that eye and up vectors are not parallel
        camera->lookAt(RealSpace::Camera::Position(
                                   RealSpace::Vector3D(0.5, 0, 140),   // eye
                                   RealSpace::Vector3D(0, 0, 0),       // center
                                   RealSpace::Vector3D::_z));          // up
        camera->endTransform(true);
        update();
    }
    else{
        canvasHintMessageBox();
    }
}

// Display message when no Sample is selected and a ToolBar action is clicked
void Canvas::canvasHintMessageBox()
{
    QMessageBox box;
    box.setIcon(QMessageBox::Information);
    box.setText("Sample not selected! Nothing to display!");
    box.setDetailedText("Hint:"
                        "\n1. Build the sample."
                        "\n2. Select it from the panel on the right.");
    box.setWindowFlags(box.windowFlags() & ~Qt::WindowCloseButtonHint); // Hide Close Button
    box.exec();
}

void Canvas::horizontalCameraTurn(float angle)
{
    if (model){

        float theta = angle*static_cast<float>(M_PI/180.0); // in radians

        Camera::Position initial_pos = camera->getPos();

        RealSpace::Vector3D v_eye = initial_pos.eye; // camera's position vector
        RealSpace::Vector3D v_ctr = initial_pos.ctr;
        RealSpace::Vector3D v_up = initial_pos.up;

        RealSpace::Vector3D v_axis = v_up.normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about up vector
        RealSpace::Vector3D v_rot_eye = v_up*(1-std::cos(theta))*dot(v_axis,v_eye) +
                v_eye*std::cos(theta) + cross(v_axis,v_eye)*std::sin(theta);

        Camera::Position rotated_pos(v_rot_eye, v_ctr, v_up);

        camera->lookAt(rotated_pos);
        camera->endTransform(true);
    }
}

void Canvas::verticalCameraTurn(float angle)
{
    if (model){

        float theta = angle*static_cast<float>(M_PI/180.0); // in radians

        Camera::Position initial_pos = camera->getPos();

        RealSpace::Vector3D v_eye = initial_pos.eye; // camera's position vector
        RealSpace::Vector3D v_ctr = initial_pos.ctr;
        RealSpace::Vector3D v_up = initial_pos.up;

        RealSpace::Vector3D v_axis = cross(v_up, v_eye).normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about an axis perpendicular to up and eye vectors
        RealSpace::Vector3D v_rot_eye = v_up*(1-std::cos(theta))*dot(v_axis,v_eye) +
                v_eye*std::cos(theta) + cross(v_axis,v_eye)*std::sin(theta);

        Camera::Position rotated_pos(v_rot_eye, v_ctr, v_up);

        camera->lookAt(rotated_pos);
        camera->endTransform(true);
    }
}

}  // namespace RealSpace
