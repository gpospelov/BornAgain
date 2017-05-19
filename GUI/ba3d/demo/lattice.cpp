// GPL3; https://github.com/jburle/ba3d

#include "lattice.h"
#include <QtGlobal>
#include <QTime>
#include <qmath.h>

//------------------------------------------------------------------------------

QVector<ba3d::xyz> squareLattice(uint n, float sigma) {
  using flt = ba3d::flt;
  using xyz = ba3d::xyz;

  auto rand01 = [&]() -> float {
    static bool seeded = false;
    if (!seeded) {
      seeded = true;
      qsrand(QTime::currentTime().msec());
    }
    return qrand() / float(RAND_MAX);
  };

  auto place00 = [&]() -> xyz {
    // https://www.taygeta.com/random/gaussian.html
    float x01, y01, w;

    do {
      x01 = 2.f * rand01() - 1.f;
      y01 = 2.f * rand01() - 1.f;
      w   = x01 * x01 + y01 * y01;
    } while (w >= 1.f);

    w = sqrt(-2.f * qLn(w) / w);
    return ba3d::xyz(x01 * w * sigma, y01 * w * sigma, 0);
  };

  auto placeHere = [&](xyz::rc here) -> xyz {
    return place00() + here;
  };

  auto placeXY = [&](flt x, flt y) -> xyz {
    return placeHere(xyz(x, y, 0));
  };

  uint nn = (2*n + 1) * (2*n + 1); // total number

  auto mesh = QVector<xyz>(nn);

  auto index = [&](int ix, int iy) -> uint {
    int nx = n, ny = n;
    EXPECT (-nx <= ix && ix <= +nx)
    EXPECT (-ny <= iy && iy <= +ny)
    uint i = (2*nx + 1) * (iy + ny) + (ix + nx);
    ENSURE (i < nn)
    return i;
  };

  auto get = [&](int ix, int iy) -> xyz::rc {
    return mesh.at(index(ix, iy));
  };

  auto isMade = [&](int ix, int iy) -> bool {
    return xyz::_0 != mesh.at(index(ix, iy));
  };

  auto put = [&](int ix, int iy) {
    if (!isMade(ix, iy))
      mesh[index(ix, iy)] = placeXY(ix, iy);
  };

  auto growBy1Quadrant = [&](uint n, int mx, int my) {
    EXPECT (n > 0)
    EXPECT (1 == qAbs(mx) && 1 == qAbs(my))

    put(0*mx, n*my); put(n*mx, 0*my);

    for (uint i = 1; i < n; ++i) {
      put(i*mx, n*my); put(n*mx, i*my);
    }

    put(n*mx, n*my);
  };

  auto growBy1 = [&](uint n) {
    EXPECT (n > 0)
    growBy1Quadrant(n, +1, +1);
    growBy1Quadrant(n, +1, -1);
    growBy1Quadrant(n, -1, +1);
    growBy1Quadrant(n, -1, -1);
  };

  auto growTo = [&](uint n) {
    for (uint i = 1; i <= n; ++i)
      growBy1(i);
  };

  growTo(n);
  return mesh;
};

//------------------------------------------------------------------------------
// eof
