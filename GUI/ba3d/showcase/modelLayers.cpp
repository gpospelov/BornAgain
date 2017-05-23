// GPL3; https://github.com/jburle/ba3d

#include "modelLayers.h"
#include "modelShowcase.h"
#include <ba3d/model/layer.h>

//------------------------------------------------------------------------------

using namespace ba3d;

static flt const sz = 100; // half sz

ModelLayers::ModelLayers() {
  defCamPos = Camera::pos_t(xyz(-10, -140, 20), xyz(0, 0, -30), xyz::_z);

  auto layer = [&](int z1, int z2, QColor color) {
    flt s2 = sz /2;
    auto l = new Layer(dxyz(dr(-s2,+s2), dr(-s2,+s2), dr(z1, z2)));
    color.setAlphaF(.3);
    l->color = color;

    addBlend(l);
  };

  layer(  0, -10, Qt::blue);
  layer(-10, -30, Qt::green);
  layer(-30, -45, Qt::red);
  layer(-45, -55, Qt::gray);
}

void ModelLayers::showKind(particle::kind k) {
  for (auto p : ps)
    delete p;
  ps.clear();

  if (particle::kind::None == k)
    return;

  flt z[] = {-10, -30, -45};
  ps.reserve(3*9*9);
  for_int (i, 9)
    for_int (j, 9)
      for_int (zi, 3) {
        auto p = ModelShowcase::newParticle(k, 3);
        add(p); ps.append(p);
        p->transform(xyz::_0, xyz((i-4)*sz/10, (j-4)*sz/10, z[zi]+.001f));
      }

  emit updated();
}

//------------------------------------------------------------------------------
// eof
