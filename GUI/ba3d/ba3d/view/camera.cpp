// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/camera.cpp
//! @brief     Implements Camera class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "camera.h"

namespace RealSpace {

const Vector3D LIGHT1 = Vector3D(0.5f, 1.0f, 1.0f)*1000.0f;
const Vector3D LIGHT2 = Vector3D(1.0f, 0.0f, 1.0f)*1000.0f;
const Vector3D LIGHT3 = Vector3D(1.0f, 1.0f, 0.0f)*1000.0f;

Camera::Camera()
    : pos(Vector3D::_z, Vector3D::_0, Vector3D::_x)
    , zoom(1), vertAngle(60), nearPlane(1), farPlane(10000)
    , lightPos1(LIGHT1), lightPosRotated1(lightPos1)
{
    setAspectRatio(1);
}

Camera::Position::Position() : eye(), ctr(), up()
{}

Camera::Position::Position(const Vector3D& eye_, const Vector3D& ctr_, const Vector3D& up_,
                     QQuaternion const& rot_)
    : eye(eye_), ctr(ctr_), up(up_), rot(rot_)
{}

Camera::Position Camera::Position::interpolateTo(const Position& to, float r) const
{
    return Position(eye.interpolateTo(to.eye, r),
                 ctr.interpolateTo(to.ctr, r),
                 up.interpolateTo(to.up, r),
                 QQuaternion::slerp(rot, to.rot, r) );
}

void Camera::lookAt(const Position& pos_)
{
    pos = pos_;
//    lightPos = pos.eye;
    set();
}

// recalculate dependent params
void Camera::set()
{
    matModel.setToIdentity();
    matModel.lookAt((pos.eye-pos.ctr)*zoom + pos.ctr, pos.ctr, pos.up);

    QQuaternion rt(pos.rot * addRot);
    matModel.translate(+pos.ctr);
    matModel.rotate(rt);
    matModel.translate(-pos.ctr);

    lightPosRotated1 = rt.inverted().rotatedVector(lightPos1);

    emit updated(*this);
}

void Camera::setAspectRatio(float ratio)
{
    matProj.setToIdentity();
    matProj.perspective(vertAngle, ratio, nearPlane, farPlane);
}

void Camera::turnBy(QQuaternion const& rot)
{
    addRot = rot;
    set();
}

void Camera::zoomBy(float zoom_)
{
    zoom = zoom_;
    set();
}

void Camera::endTransform(bool keep)
{
    if (keep) {
        pos.rot = (pos.rot * addRot).normalized();
        pos.eye = pos.eye * zoom; // TODO limit
    }
    addRot = QQuaternion();
    zoom = 1;
    set();
}

}  // namespace RealSpace
