// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/particle.cpp
//! @brief     Implements Particle class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "particles.h"
#include <qmath.h>
#include <math.h>

namespace RealSpace { namespace Particles {
//------------------------------------------------------------------------------

QString const& name(EShape k) {
  static QString names[] = {
    "", "FullSphere", "FullSpheroid", "Cylinder", "TruncatedSphere",
    "TruncatedSpheroid", "Cone", "Icosahedron", "Dodecahedron", "TruncatedCube",
    "Prism6", "Cone6", "Pyramid", "Cuboctahedron", "Prism3", "Tetrahedron",
    "EllipsoidalCylinder", "Box", "HemiEllipsoid", "AnisoPyramid",
  };

  return names[uint(k)];
}

//------------------------------------------------------------------------------

using namespace geometry;

Particle::Particle(key key) : Object(key), scale(Vector3D::_1) {}

void Particle::set() {
  transform(Vector3D::_0, Vector3D::_0);
}

void Particle::transform(Vector3D rotate_, Vector3D translate_) {
  Object::transform(turn, scale,
                  (rotate = rotate_), offset + (translate = translate_));
}

void Particle::fancy(Vector3D rotate, float r) {
  Object::transform(turn, scale*r, rotate, offset + translate);
}

//------------------------------------------------------------------------------

static float const pi2f   = float(M_PI_2);
static float const sqrt2f = float(qSqrt(2));
static float const sqrt3f = float(qSqrt(3));

FullSphere::FullSphere(float R)
: Particle(key(eid::Sphere, 0)) {
  isNull = (R <= 0);
  scale  = Vector3D(R*2); offset = Vector3D(0, 0, R); set();
}

FullSpheroid::FullSpheroid(float R, float H)
: Particle(key(eid::Sphere, 0)) {
  isNull = (R <= 0 || H <= 0);
  scale  = Vector3D(R*2, R*2, H); offset = Vector3D(0, 0, H/2); set();
}

Cylinder::Cylinder(float R, float H)
: Particle(key(eid::Column, pi2f, 0)) {
  isNull = (R <= 0 || H <= 0);
  scale  = Vector3D(R*2, R*2, H); offset = Vector3D(0, 0, H/2); set();
}

TruncatedSphere::TruncatedSphere(float R, float H)
: Particle(key(eid::Sphere, 1 - H/R/2)) {
  isNull = (R <= 0 || H <= 0);
  scale  = Vector3D(R*2); offset = Vector3D(0, 0, H-R); set();
}

TruncatedSpheroid::TruncatedSpheroid(float R, float H, float fp)
: Particle(key(eid::Sphere, 1 - H/fp/R/2)) {
  isNull = (R <= 0 || H <= 0 || fp <= 0);
  scale  = Vector3D(R*2, R*2, fp*R*2); offset = Vector3D(0, 0, H-fp*R); set();
}

Cone::Cone(float R, float H, float alpha)
: Particle(key(eid::Column, alpha, 0)) {
  isNull = (R <= 0 || H <= 0 || alpha <= 0);
  scale  = Vector3D(R*2, R*2, H); offset = Vector3D(0, 0, H/2); set();
}

Icosahedron::Icosahedron(float L)
: Particle(key(eid::Icosahedron)) {
  isNull = (L <= 0);
  float R = L / IcosahedronL2R;
  scale  = Vector3D(R*2, R*2, R*2); offset = Vector3D(0, 0, R); set();
}

Dodecahedron::Dodecahedron(float L)
: Particle(key(eid::Dodecahedron)) {
  isNull = (L <= 0);
  float R = L / DodecahedronL2R;
  scale  = Vector3D(R*2, R*2, R*2); offset = Vector3D(0, 0, R); set();
}

TruncatedCube::TruncatedCube(float L, float t)
: Particle(key(eid::TruncatedBox, 2*t/L)) {
  isNull = (L <= 0);
  scale  = Vector3D(L,L,L); offset = Vector3D(0, 0, L/2); set();
}

Prism6::Prism6(float R, float H)
: Particle(key(eid::Column, pi2f, 6)) {
  isNull = (R <= 0 || H <= 0);
  scale  = Vector3D(R*2, R*2, H); offset = Vector3D(0, 0, H/2); set();
}

Cone6::Cone6(float R, float H, float alpha)
: Particle(key(eid::Column, alpha, 6)) {
  isNull = (R <= 0 || H <= 0 || alpha <= 0);
  scale  = Vector3D(R*2, R*2, H); offset = Vector3D(0, 0, H/2); set();
}

Pyramid::Pyramid(float L, float H, float alpha)
: Particle(key(eid::Column, alpha, 4)) {
  isNull = (L <= 0 || H <= 0 || alpha <= 0);
  float L2 = L * sqrt2f;
  turn = Vector3D(0,0,45); scale  = Vector3D(L2, L2, H); offset = Vector3D(0, 0, H/2); set();
}

Cuboctahedron::Cuboctahedron(float L, float H, float rH, float alpha)
: Particle(key(eid::Cuboctahedron, rH, alpha)) {
  isNull = (L <= 0 || H <= 0 || rH <= 0 || alpha <= pi2f);
  scale  = Vector3D(L, L, L); offset = Vector3D(0, 0, L/2); set();
}

Prism3::Prism3(float L, float H)
: Particle(key(eid::Column, pi2f, 3)) {
  isNull = (L <= 0 || H <= 0);
  float D = L*2 / sqrt3f;
  scale = Vector3D(D*2, D*2, H); offset = Vector3D(0, 0, H/2); set();
}

Tetrahedron::Tetrahedron(float L, float H, float alpha)
: Particle(key(eid::Column, alpha, 3)) {
  isNull = (L <= 0 || H <= 0 || alpha <= 0);
  float D = L*2 / sqrt3f;
  scale = Vector3D(D*2, D*2, H); offset = Vector3D(0, 0, H/2); set();
}

EllipsoidalCylinder::EllipsoidalCylinder(float Ra, float Rb, float H)
: Particle(key(eid::Column, pi2f, 0)) {
  isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
  scale  = Vector3D(Ra*2, Rb*2, H); offset = Vector3D(0, 0, H/2); set();
}

Box::Box(float L, float W, float H)
: Particle(key(eid::Column, pi2f, 4)) {
  isNull = (L < 0 || W < 0 || H < 0) || (L <= 0 && W <= 0 && H <= 0);
  turn = Vector3D(0,0,45); scale  = Vector3D(L*sqrt2f, W*sqrt2f, H); offset = Vector3D(0, 0, H/2); set();
}

HemiEllipsoid::HemiEllipsoid(float Ra, float Rb, float H)
: Particle(key(eid::Sphere, .5f)) {
  isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
  scale  = Vector3D(Ra*2, Rb*2, H*2); set();
}

AnisoPyramid::AnisoPyramid(float L, float W, float H, float alpha)
: Particle(key(eid::Column, alpha, 4)) {
  isNull = (L <= 0 || W <= 0  || H <= 0 || alpha <= 0);
  turn = Vector3D(0,0,45); scale  = Vector3D(L*sqrt2f, W*sqrt2f, H); offset = Vector3D(0, 0, H/2); set();
}

//------------------------------------------------------------------------------
}}
