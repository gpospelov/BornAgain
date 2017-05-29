// GPL3; https://github.com/jburle/ba3d

#include <ba3d/def.h>
#include <ba3d/view/camera.h>

#include "mainwin.h"
#include "demo_model.h"
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

  QScopedPointer<DemoModel> model(new DemoModel);
  win.widg3t().setModel(model.data());

  return base::exec();
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  App(argc, argv).exec();
}

//------------------------------------------------------------------------------
// eof
