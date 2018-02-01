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

  typedef xyz const& rc;

  xyz();
  xyz(float);
  xyz(float, float, float);

  xyz(rc) = default;

  xyz(QVector3D const&);
  operator QVector3D() const;

  float length()     const;
  xyz normalized() const;

  xyz interpolateTo(rc, float) const;

  static xyz const _0, _1, _x, _y, _z;
};

// products
xyz cross(xyz::rc, xyz::rc);
float dot(xyz::rc, xyz::rc);

xyz operator+(xyz::rc);
xyz operator-(xyz::rc);
xyz operator*(xyz::rc, float);

xyz operator+(xyz::rc, xyz::rc);
xyz operator-(xyz::rc, xyz::rc);

//------------------------------------------------------------------------------

// (d)ifference or (r)ange
struct dr {
  float min, max;
  dr(float, float);

  float size() const;
  float mid()  const;
};

// dr of coordinates
struct dxyz {
  dr x, y, z;
  dxyz(dr, dr, dr);
  dxyz(xyz, xyz);

  xyz size()   const;
  xyz mid()    const;

  float length() const;
};

//------------------------------------------------------------------------------
}
#endif
