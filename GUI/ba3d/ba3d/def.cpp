// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/def.cpp
//! @brief     Definitions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "def.h"

static_assert(QT_VERSION >= QT_VERSION_CHECK(5,5,1),
              "requires Qt >= 5.5.1, have " QT_VERSION_STR);

namespace ba3d {
//------------------------------------------------------------------------------

xyz::xyz() : xyz(0,0,0) {}

xyz::xyz(float v) : xyz(v,v,v) {}

xyz::xyz(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

xyz::xyz(QVector3D const& v) : xyz(v.x(), v.y(), v.z()) {}

float xyz::length() const {
  return QVector3D(*this).length();
}

xyz xyz::normalized() const {
  return QVector3D(*this).normalized();
}

xyz xyz::interpolateTo(rc to, float rat) const {
  return *this * (1 - rat) + to * rat;
}

ba3d::xyz::operator QVector3D() const {
  return QVector3D(x, y, z);
}

xyz const xyz::_0(0,0,0), xyz::_1(1,1,1),
          xyz::_x(1,0,0), xyz::_y(0,1,0), xyz::_z(0,0,1);

xyz cross(xyz::rc v1, xyz::rc v2) {
  return QVector3D::crossProduct(v1, v2);
}

float dot(xyz::rc v1, xyz::rc v2) {
  return QVector3D::dotProduct(v1, v2);
}

xyz operator+(xyz::rc v) {
  return v;
}

xyz operator-(xyz::rc v) {
  return xyz::_0 - v;
}

xyz operator*(xyz::rc v, float f) {
  return xyz(v.x*f, v.y*f, v.z*f);
}

xyz operator+(xyz::rc _1, xyz::rc _2) {
  return xyz(_1.x+_2.x, _1.y+_2.y, _1.z+_2.z);
}

xyz operator-(xyz::rc _1, xyz::rc _2) {
  return xyz(_1.x-_2.x, _1.y-_2.y, _1.z-_2.z);
}

//------------------------------------------------------------------------------

dr::dr(float r1, float r2) : min(qMin(r1,r2)), max(qMax(r1,r2)) {}

float dr::size() const {
  return max - min;
}

float dr::mid() const {
  return (min + max) / 2;
}

//------------------------------------------------------------------------------

dxyz::dxyz(dr x_, dr y_, dr z_) : x(x_), y(y_), z(z_) {}

dxyz::dxyz(xyz _1, xyz _2)
: x(dr(_1.x,_2.x)), y(dr(_1.y,_2.y)), z(dr(_1.z,_2.z)) {}

xyz dxyz::size() const {
  return xyz(x.size(), y.size(), z.size());
}

xyz dxyz::mid() const {
  return xyz(x.mid(), y.mid(), z.mid());
}

float dxyz::length() const {
  return xyz(x.size(), y.size(), z.size()).length();
}

//------------------------------------------------------------------------------
}
// eof
