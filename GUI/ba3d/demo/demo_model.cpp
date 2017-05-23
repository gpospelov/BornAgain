// GPL3; https://github.com/jburle/ba3d

#include "demo_model.h"
#include "lattice.h"
#include <ba3d/model/layer.h>
#include <QApplication>
#include <thread>
#include <qmath.h>

//------------------------------------------------------------------------------

using namespace ba3d;

DemoModel::DemoModel() {
  setCameraSide();

  addSubstrate();
  addLayer();

  calc(0);
}

void DemoModel::switchBack() {
  switch (back) {
  case hasNONE:
    addSubstrate(); back = hasSUBSTRATE;
    break;
  case hasSUBSTRATE:
    addLayer(); back = hasLAYER;
    break;
  case hasLAYER:
    super::clear(true); back = hasNONE;
    break;
  }

  snooze();
}

void DemoModel::calc(float sigma) {
  uint n = qFloor(szSample / spacing / 2 - 1);
  auto mesh = squareLattice(n, sigma);
  for (auto& m: mesh)
    m = m  * spacing + xyz(0, 0, -20);

  if (ps.empty()) { // first time - init
    ps.resize(mesh.count());
    flt R = 6;
    for (auto& p: ps)
      add((p = new particle::TruncatedSphere(R, R)));
  }

  EXPECT (ps.count() == mesh.count())

  if (activeMesh.empty()) {
    activeMesh = mesh;
    for (uint i=0; i < ps.count(); ++i)
      ps.at(i)->transform(xyz::_0, activeMesh.at(i));
  } else {
    float const step = .1; bool go = true;
    while (go) {
      go = false;
      for (uint i=0; i < ps.count(); ++i) {
        auto& p = ps.at(i);
        auto& newPos = mesh.at(i);
        auto& pos = activeMesh[i];
        if (step > (pos - newPos).length())
          pos = newPos;
        else {
          pos = pos + (newPos - pos).normalized() * step;
          go = true;
        }
        p->transform(xyz::_0, pos);
      }

      snooze();
    }
  }

  snooze();
}

void DemoModel::flip() {
  if (!activeMesh.empty()) {
    for (int deg=0; deg <=360; deg += 5) {
      for (uint i=0; i < ps.count(); ++i) {
        auto& p = ps.at(i);
        auto& pos = activeMesh[i];
        p->transform(xyz(0,deg,0), pos);
      }

      snooze();
    }
  }

  snooze();
}

static flt const hgtLayer = 20, hgtSubstrate = 35;

void DemoModel::setCameraTop(bool animate) {
  setCamera(Camera::pos_t(xyz(10, 10, szSample), xyz(0, 0, -20), xyz::_y), animate);
}

void DemoModel::setCameraSide(bool animate) {
  setCamera(Camera::pos_t(xyz(-10, -szSample*1.1, 2*hgtLayer), xyz(0, 0, -20), xyz::_z), animate);
}

void DemoModel::setCamera(Camera::pos_t::rc to, bool animate) {
  if (animate) {
    auto from = camPos;

    uint const frames = 45;
    for_i (frames) {
      defCamPos = from.interpolateTo(flt(i) / frames, to);
      snooze();
    }
  } else {
    defCamPos = to;
    snooze();
  }
}

void DemoModel::cameraUpdated(DemoModel::Camera const& cam) {
  camPos = cam.getPos();
}

void DemoModel::addSubstrate() {
  addLayer(dr(-hgtLayer, -hgtLayer - hgtSubstrate), Qt::gray);
}

void DemoModel::addLayer() {
  addLayer(dr(0, -hgtLayer), Qt::green);
}

void DemoModel::addLayer(dr z, QColor clr) {
  flt s2 = szSample / 2;
  auto l = new Layer(dxyz(dr(-s2,+s2), dr(-s2,+s2), z));
  clr.setAlphaF(.3);
  l->color = clr;
  addBlend(l);
}

void DemoModel::snooze() {
  emit updated();
  qApp->processEvents();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

//------------------------------------------------------------------------------
// eof
