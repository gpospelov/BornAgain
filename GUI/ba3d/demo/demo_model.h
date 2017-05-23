// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_DEMOMODEL_LAYERS_H
#define BA3D_DEMOMODEL_LAYERS_H

#include <ba3d/model/model.h>
#include <ba3d/model/particles.h>
#include <QAtomicInteger>

//------------------------------------------------------------------------------

class DemoModel : public ba3d::Model {
public:
  using super = ba3d::Model;

  using xyz = ba3d::xyz;
  using flt = ba3d::flt;
  using Particle = ba3d::particle::Particle;
  using Camera   = ba3d::Camera;

  DemoModel();
  void switchBack();

  void calc(float sigma);
  void flip();

  void setCameraTop(bool animate = false);
  void setCameraSide(bool animate = false);
  void setCamera(Camera::pos_t::rc, bool animate = false);

  void cameraUpdated(Camera const&);

private:
  void addSubstrate();
  void addLayer();

  enum {hasNONE, hasSUBSTRATE, hasLAYER } back = hasNONE;

  flt szSample = 400;
  flt spacing  = 20; // of particles

  Camera::pos_t camPos;

private:
  void addLayer(ba3d::dr, QColor);

  QVector<Particle*> ps;
  QVector<xyz> activeMesh;

private:
  void snooze();
};

//------------------------------------------------------------------------------
#endif
// eof
