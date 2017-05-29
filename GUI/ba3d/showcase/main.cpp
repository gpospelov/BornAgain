// GPL3; https://github.com/jburle/ba3d

#include <ba3d/def.h>
#include <ba3d/view/camera.h>

#include "mainwin.h"
#include "modelLayers.h"
#include "modelShowcase.h"
#include <QApplication>

//------------------------------------------------------------------------------

class App : public QApplication { BASE(QApplication)
public:
  App(int& argc, char* argv[]);
 ~App();

  int exec();
};

App::App(int& argc, char* argv[]) : base(argc, argv) {
  setOrganizationName("c53");
  setApplicationName("ba3d");
}

App::~App() {}

int App::exec() {
  MainWin win;
  win.show();

  QScopedPointer<ModelLayers>   ml(new ModelLayers);
  QScopedPointer<ModelShowcase> ms(new ModelShowcase);

  auto &w1(win.widg3t_1()), &w2(win.widg3t_2()), &w3(win.widg3t_3());

  w1.setModel(ml.data());
  w2.setModel(ml.data());
  w3.setModel(ms.data());

  w2.cam().lookAt(ba3d::Camera::pos_t(
    ba3d::xyz::_z*90, ba3d::xyz(0,0,0), ba3d::xyz::_y));

  connect(&win, &MainWin::showKind, [&](ba3d::particle::kind kind) {
    ml->showKind(kind); ms->showKind(kind);
  });

  return base::exec();
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  App(argc, argv).exec();
}

//------------------------------------------------------------------------------
// eof
