// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/def.h
//! @brief     Definitions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_DEF_H
#define BA3D_DEF_H

#if defined(__GNUC__) && !defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

//------------------------------------------------------------------------------
// coordinates

#include <QVector3D>

namespace ba3d {
//------------------------------------------------------------------------------

struct xyz {
  float x, y, z;

  xyz();
  xyz(float);
  xyz(float, float, float);

  xyz(const xyz&) = default;

  xyz(QVector3D const&);
  operator QVector3D() const;

  float length()     const;
  xyz normalized() const;

  xyz interpolateTo(const xyz&, float) const;

  static xyz const _0, _1, _x, _y, _z;
};

// products
xyz cross(const xyz&, const xyz&);
float dot(const xyz&, const xyz&);

xyz operator+(const xyz&);
xyz operator-(const xyz&);
xyz operator*(const xyz&, float);

xyz operator+(const xyz&, const xyz&);
xyz operator-(const xyz&, const xyz&);

//------------------------------------------------------------------------------

// range of float
struct RangeFloat {
  float min, max;
  RangeFloat(float, float);

  float size() const;
  float mid()  const;
};

// range of coordinates
struct RangeXYZ {
  RangeFloat x, y, z;
  RangeXYZ(RangeFloat, RangeFloat, RangeFloat);
  RangeXYZ(xyz, xyz);

  xyz size()   const;
  xyz mid()    const;

  float length() const;
};

//------------------------------------------------------------------------------
}
#endif
