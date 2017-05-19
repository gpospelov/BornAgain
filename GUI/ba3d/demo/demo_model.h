// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_DEMOMODEL_LAYERS_H
#define BA3D_DEMOMODEL_LAYERS_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>
#include <QAtomicInteger>

//------------------------------------------------------------------------------

class DemoModel : public ba3d::Model {
public:
  DemoModel();
  void calc(float sigma);
  void flip();

  bool ready() {
    return 0 == busy;
  }

private:
  uint n; float spacing;
  QVector<ba3d::particle::Particle*> ps;
  QVector<ba3d::xyz> activeMesh;
  QAtomicInteger<int> busy;
};

//------------------------------------------------------------------------------
#endif
// eof
