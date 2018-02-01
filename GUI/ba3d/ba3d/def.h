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

// 32b float as in GL; 3 letters as in 'int'
using flt = float;

#ifndef NDEBUG

// in debug version checked, non-negative flt >= 0: (fl)t (p)ositive
struct flp {
  flp(flt);
  operator flt() const { return f; }
private:
  flt f;
};

#else

typedef flt flp;

#endif

//------------------------------------------------------------------------------

struct xyz {
  flt x, y, z;

  typedef xyz const& rc;

  xyz();
  xyz(flt);
  xyz(flt, flt, flt);

  xyz(rc) = default;

  xyz(QVector3D const&);
  operator QVector3D() const;

  flt length()     const;
  xyz normalized() const;

  xyz interpolateTo(rc, flt) const;

  static xyz const _0, _1, _x, _y, _z;
};

// products
xyz cross(xyz::rc, xyz::rc);
flt dot(xyz::rc, xyz::rc);

xyz operator+(xyz::rc);
xyz operator-(xyz::rc);
xyz operator*(xyz::rc, flt);

xyz operator+(xyz::rc, xyz::rc);
xyz operator-(xyz::rc, xyz::rc);

//------------------------------------------------------------------------------

// (d)ifference or (r)ange
struct dr {
  flt min, max;
  dr(flt, flt);

  flt size() const;
  flt mid()  const;
};

// dr of coordinates
struct dxyz {
  dr x, y, z;
  dxyz(dr, dr, dr);
  dxyz(xyz, xyz);

  xyz size()   const;
  xyz mid()    const;

  flt length() const;
};

//------------------------------------------------------------------------------
}
#endif
// eof
