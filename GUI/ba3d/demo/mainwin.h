// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_MAINWIN_H
#define BA3D_MAINWIN_H

#include <ba3d/widget.h>
#include <ba3d/model/particles.h>
#include <QMainWindow>

//------------------------------------------------------------------------------

class QSlider;

class MainWin : public QMainWindow { BASE(QMainWindow)
  Q_OBJECT
public:
  MainWin();

  ba3d::Widget3D& widg3t() {
    return *w3d;
  }

private:
  void closeEvent(QCloseEvent*);
  void keyPressEvent(QKeyEvent*);
  void mouseDoubleClickEvent(QMouseEvent*);

  void createLayout();
  ba3d::Widget3D *w3d;
  QWidget *controls;
  QSlider *sigmaSlider;
};

//------------------------------------------------------------------------------
#endif
// eof
