// GPL3; https://github.com/jburle/ba3d

#include "demo_model.h"
#include "lattice.h"
#include <ba3d/model/layer.h>
#include <QApplication>
#include <thread>
#include <qmath.h>

//------------------------------------------------------------------------------

using namespace ba3d;

DemoModel::DemoModel() : busy(0) {
  flt const sz = 1200;
  spacing = 20; // of particles

  defEye = xyz(10, 10, sz);
  defCtr = xyz(0, 0, -20);
  defUp  = xyz::_y;

  auto layer = [&](int z1, int z2, QColor color) {
    flt s2 = sz /2;
    auto l = new Layer(dxyz(dr(-s2,+s2), dr(-s2,+s2), dr(z1, z2)));
    color.setAlphaF(.3);
    l->color = color;

    addBlend(l);
  };

  layer(  0, -20, Qt::green);
  layer(-20, -55, Qt::gray);

  n = qFloor(sz / spacing / 2 - 1);

  calc(0);
}

void DemoModel::calc(float sigma) {
  ++busy;

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

      emit updated();
      qApp->processEvents();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }

  emit updated();
  --busy;
}

void DemoModel::flip() {
  ++busy;

  if (!activeMesh.empty()) {
    for (int deg=0; deg <=360; deg += 5) {
      for (uint i=0; i < ps.count(); ++i) {
        auto& p = ps.at(i);
        auto& pos = activeMesh[i];
        p->transform(xyz(0,deg,0), pos);
      }

      emit updated();
      qApp->processEvents();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }

  emit updated();
  --busy;
}

//------------------------------------------------------------------------------
// eof
