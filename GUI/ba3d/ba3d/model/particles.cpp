// GPL3; https://github.com/jburle/ba3d

#include "particles.h"
#include <qmath.h>
#include <math.h>

namespace ba3d { namespace particle {
//------------------------------------------------------------------------------

QString const& name(kind k) {
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

Particle::Particle(key key) : base(key), scale(xyz::_1) {}

void Particle::set() {
  transform(xyz::_0, xyz::_0);
}

void Particle::transform(xyz rotate, xyz translate) {
  base::transform(turn, scale, rotate, offset + translate);
}

//------------------------------------------------------------------------------

static flt const pi2f   = flt(M_PI_2);
static flt const sqrt2f = flt(qSqrt(2));
static flt const sqrt3f = flt(qSqrt(3));

FullSphere::FullSphere(flp R)
: Particle(key(eid::Sphere, 0)) {
  isNull = (R <= 0);
  scale  = xyz(R*2); offset = xyz(0, 0, R); set();
}

FullSpheroid::FullSpheroid(flp R, flp H)
: Particle(key(eid::Sphere, 0)) {
  isNull = (R <= 0 || H <= 0);
  scale  = xyz(R*2, R*2, H); offset = xyz(0, 0, H/2); set();
}

Cylinder::Cylinder(flp R, flp H)
: Particle(key(eid::Column, pi2f, 0)) {
  isNull = (R <= 0 || H <= 0);
  scale  = xyz(R*2, R*2, H); offset = xyz(0, 0, H/2); set();
}

TruncatedSphere::TruncatedSphere(flp R, flp H)
: Particle(key(eid::Sphere, 1 - H/R/2)) {
  isNull = (R <= 0 || H <= 0);
  scale  = xyz(R*2); offset = xyz(0, 0, H-R); set();
}

TruncatedSpheroid::TruncatedSpheroid(flp R, flp H, flp fp)
: Particle(key(eid::Sphere, 1 - H/fp/R/2)) {
  isNull = (R <= 0 || H <= 0 || fp <= 0);
  scale  = xyz(R*2, R*2, fp*R*2); offset = xyz(0, 0, H-fp*R); set();
}

Cone::Cone(flp R, flp H, flp alpha)
: Particle(key(eid::Column, alpha, 0)) {
  isNull = (R <= 0 || H <= 0 || alpha <= 0);
  scale  = xyz(R*2, R*2, H); offset = xyz(0, 0, H/2); set();
}

Icosahedron::Icosahedron(flp L)
: Particle(key(eid::Icosahedron)) {
  isNull = (L <= 0);
  flp R = L / icosahedronL2R;
  scale  = xyz(R*2, R*2, R*2); offset = xyz(0, 0, R); set();
}

Dodecahedron::Dodecahedron(flp L)
: Particle(key(eid::Dodecahedron)) {
  isNull = (L <= 0);
  flp R = L / dodecahedronL2R;
  scale  = xyz(R*2, R*2, R*2); offset = xyz(0, 0, R); set();
}

TruncatedCube::TruncatedCube(flp L, flp t)
: Particle(key(eid::TruncatedBox, 2*t/L)) {
  isNull = (L <= 0);
  scale  = xyz(L,L,L); offset = xyz(0, 0, L/2); set();
}

Prism6::Prism6(flp R, flp H)
: Particle(key(eid::Column, pi2f, 6)) {
  isNull = (R <= 0 || H <= 0);
  scale  = xyz(R*2, R*2, H); offset = xyz(0, 0, H/2); set();
}

Cone6::Cone6(flp R, flp H, flp alpha)
: Particle(key(eid::Column, alpha, 6)) {
  isNull = (R <= 0 || H <= 0 || alpha <= 0);
  scale  = xyz(R*2, R*2, H); offset = xyz(0, 0, H/2); set();
}

Pyramid::Pyramid(flp L, flp H, flp alpha)
: Particle(key(eid::Column, alpha, 4)) {
  isNull = (L <= 0 || H <= 0 || alpha <= 0);
  flt L2 = L * sqrt2f;
  turn = xyz(0,0,45); scale  = xyz(L2, L2, H); offset = xyz(0, 0, H/2); set();
}

Cuboctahedron::Cuboctahedron(flp L, flp H, flp rH, flp alpha)
: Particle(key(eid::Cuboctahedron, rH, alpha)) {
  isNull = (L <= 0 || H <= 0 || rH <= 0 || alpha <= pi2f);
  scale  = xyz(L, L, L); offset = xyz(0, 0, L/2); set();
}

Prism3::Prism3(flp L, flp H)
: Particle(key(eid::Column, pi2f, 3)) {
  isNull = (L <= 0 || H <= 0);
  flt D = L*2 / sqrt3f;
  scale = xyz(D*2, D*2, H); offset = xyz(0, 0, H/2); set();
}

Tetrahedron::Tetrahedron(flp L, flp H, flp alpha)
: Particle(key(eid::Column, alpha, 3)) {
  isNull = (L <= 0 || H <= 0 || alpha <= 0);
  flt D = L*2 / sqrt3f;
  scale = xyz(D*2, D*2, H); offset = xyz(0, 0, H/2); set();
}

EllipsoidalCylinder::EllipsoidalCylinder(flp Ra, flp Rb, flp H)
: Particle(key(eid::Column, pi2f, 0)) {
  isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
  scale  = xyz(Ra*2, Rb*2, H); offset = xyz(0, 0, H/2); set();
}

Box::Box(flp L, flp W, flp H)
: Particle(key(eid::Column, pi2f, 4)) {
  isNull = (L < 0 || W < 0 || H < 0) || (L <= 0 && W <= 0 && H <= 0);
  turn = xyz(0,0,45); scale  = xyz(L*sqrt2f, W*sqrt2f, H); offset = xyz(0, 0, H/2); set();
}

HemiEllipsoid::HemiEllipsoid(flp Ra, flp Rb, flp H)
: Particle(key(eid::Sphere, .5f)) {
  isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
  scale  = xyz(Ra*2, Rb*2, H*2); set();
}

AnisoPyramid::AnisoPyramid(flp L, flp W, flp H, flp alpha)
: Particle(key(eid::Column, alpha, 4)) {
  isNull = (L <= 0 || W <= 0  || H <= 0 || alpha <= 0);
  turn = xyz(0,0,45); scale  = xyz(L*sqrt2f, W*sqrt2f, H); offset = xyz(0, 0, H/2); set();
}

//------------------------------------------------------------------------------
}}
// eof
