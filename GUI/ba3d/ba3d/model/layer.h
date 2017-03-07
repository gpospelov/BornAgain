// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_LAYER_H
#define BA3D_LAYER_H

#include "object.h"

namespace ba3d {
//------------------------------------------------------------------------------

// particle layer: a transparent box
class Layer : public Object { BASE(Object)
public:
  Layer(dxyz);
};

//------------------------------------------------------------------------------
}
#endif
// eof
