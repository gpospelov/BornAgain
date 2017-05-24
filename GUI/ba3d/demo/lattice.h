// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_LATTICE_H
#define BA3D_LATTICE_H

#include <ba3d/def.h>
#include <QVector>

//------------------------------------------------------------------------------

class Lattice : public QVector<ba3d::xyz> {
public:
  using super = QVector<ba3d::xyz>;

  Lattice();
  Lattice(uint n, uint nn);

  uint index(int ix, int iy);
  int ix(uint);
  int iy(uint);
  uint n;
};

Lattice squareLattice(uint n, float sigma); // n half-size

//------------------------------------------------------------------------------
#endif
// eof
