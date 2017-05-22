// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_MAINWIN_H
#define BA3D_MAINWIN_H

#include <ba3d/widget.h>
#include <ba3d/model/particles.h>
#include <QMainWindow>

//------------------------------------------------------------------------------

class QComboBox;

class MainWin : public QMainWindow { BASE(QMainWindow)
  Q_OBJECT
public:
  MainWin();

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
  void showKind(ba3d::particle::kind);

private:
  void closeEvent(QCloseEvent*);
  void keyPressEvent(QKeyEvent*);

  ba3d::Widget3D *w3d_1, *w3d_2, *w3d_3;
  QComboBox *combo;

  void createLayout();
};

//------------------------------------------------------------------------------
#endif
// eof
