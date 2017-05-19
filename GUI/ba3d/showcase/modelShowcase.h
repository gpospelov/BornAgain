// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_MODEL_SHOWCASE_H
#define BA3D_MODEL_SHOWCASE_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>

//------------------------------------------------------------------------------

class ModelShowcase : public ba3d::Model {
public:
  using Particle = ba3d::particle::Particle;
  using kind     = ba3d::particle::kind;

  ModelShowcase();
  void showKind(kind);

  static Particle* newParticle(kind k, ba3d::flp R);

private:
  Particle *p;
};

//------------------------------------------------------------------------------
#endif
// eof
