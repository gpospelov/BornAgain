// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_DEF_H
#define BA3D_DEF_H

#if defined(__GNUC__) && !defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

// debug support
#ifndef NDEBUG

// trace print
#include <QDebug>
#define TR(what) qDebug() << what;

#else

#define TR(what) ;

#endif

// trace print
#define WT(what) TR(#what << what)

// precondition
#define EXPECT(cond) Q_ASSERT(cond);
// invariant
#define ENSURE(cond) Q_ASSERT(cond);

// a handy iteration support
#ifdef __GNUC__

template <typename T> struct mut_typ          { typedef T typ; };
template <typename T> struct mut_typ<T const> { typedef T typ; };

#define for_int(i, n) \
  for (mut_typ<decltype(n)>::typ i = decltype(n)(0), i##End = (n); i < i##End; ++i)

#else // msvc fails the above

#define for_int(i, n) \
  for (int i = 0, i##End = (n); i < i##End; ++i)

#endif

#define for_i(n) for_int (i, n)

// typedef for a base class
#define BASE(cls) using base = cls;

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
