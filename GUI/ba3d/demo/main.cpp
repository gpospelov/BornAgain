// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/demo/main.cpp
//! @brief     Main program
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include <ba3d/def.h>
#include <ba3d/view/camera.h>

#include "mainwin.h"
#include "demo_model.h"
#include <QApplication>

//------------------------------------------------------------------------------

class App : public QApplication
{
public:
  App(int& argc, char* argv[]);
 ~App();

  int exec();
};

App::App(int& argc, char* argv[]) : QApplication(argc, argv) {
  setOrganizationName("c53");
  setApplicationName("ba3d");
}

App::~App() {}

int App::exec() {
  MainWin win;
  win.show();

  QScopedPointer<DemoModel> model(new DemoModel);
  win.widg3t().setModel(model.data());

  return QApplication::exec();
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  App(argc, argv).exec();
}

//------------------------------------------------------------------------------
