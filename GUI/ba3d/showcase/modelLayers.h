// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_MODEL_LAYERS_H
#define BA3D_MODEL_LAYERS_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>

//------------------------------------------------------------------------------

class ModelLayers : public ba3d::Model {
public:
  ModelLayers();
  void showKind(ba3d::particle::kind);

private:
  QVector<ba3d::particle::Particle*> ps;
};

//------------------------------------------------------------------------------
#endif
// eof
