// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/showcase/mainwindow.h
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

#include <ba3d/widget.h>
#include <ba3d/model/particles.h>
#include <QMainWindow>

//------------------------------------------------------------------------------

class QComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
  MainWindow();

  ba3d::Widget3D& widg3t_1() {
    return *w3d_1;
  }

  ba3d::Widget3D& widg3t_2() {
    return *w3d_2;
  }

  ba3d::Widget3D& widg3t_3() {
    return *w3d_3;
  }

signals:
  void showKind(ba3d::particle::EShape);

private:
  void closeEvent(QCloseEvent*);

  ba3d::Widget3D *w3d_1, *w3d_2, *w3d_3;
  QComboBox *combo;

  void createLayout();
};

//------------------------------------------------------------------------------
#endif
