// GPL3; https://github.com/jburle/ba3d

#include "widget.h"
#include "model/model.h"
#include "view/camera.h"
#include "view/canvas.h"
#include "view/program.h"

#include <QBoxLayout>

namespace ba3d {
//------------------------------------------------------------------------------

Widget3D::Widget3D() : canvas(nullptr), camera(nullptr), program(nullptr) {
  auto box = new QHBoxLayout;
  setLayout(box);
  box->setMargin(0);
  box->addWidget((canvas = new Canvas));

  canvas->setCamera((camera = new Camera));
  canvas->setProgram((program = new Program));
}

Widget3D::~Widget3D() {
  delete program;
  delete camera;
}

void Widget3D::setBackground(QColor const& color) {
  canvas->setBgColor(color);
}

void Widget3D::setModel(Model* model) {
  canvas->setModel(model);
  connect(camera, &ba3d::Camera::updated, model, &Model::cameraUpdated);
  camera->set();
}

Model* Widget3D::getModel() {
  return canvas->getModel();
}

//------------------------------------------------------------------------------
}
// eof
