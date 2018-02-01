// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/demo/mainwin.h
//! @brief     Defines MainWin class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MAINWIN_H
#define BA3D_MAINWIN_H

#include "demo_model.h"
#include <ba3d/widget.h>
#include <ba3d/model/particles.h>
#include <QMainWindow>

//------------------------------------------------------------------------------

class QSlider;

class MainWin : public QMainWindow
{
  Q_OBJECT
public:
  MainWin();

  ba3d::Widget3D& widg3t() {
    return *w3d;
  }

private:
  void closeEvent(QCloseEvent*);
  void keyPressEvent(QKeyEvent*);

  void createLayout();
  ba3d::Widget3D *w3d;

  class DemoModel* model();
};

//------------------------------------------------------------------------------
#endif
