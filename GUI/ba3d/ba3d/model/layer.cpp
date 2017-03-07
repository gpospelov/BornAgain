// GPL3; https://github.com/jburle/ba3d

#include "layer.h"

namespace ba3d {
//------------------------------------------------------------------------------

Layer::Layer(dxyz d) : base(geometry::key(geometry::eid::Box)) {
  transform(d.size(), xyz::_0, d.mid());
}

//------------------------------------------------------------------------------
}
// eof
