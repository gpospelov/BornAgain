// GPL3; https://github.com/jburle/ba3d

#include "mainwin.h"
#include "demo_model.h"

#include <QApplication>
#include <QBoxLayout>
#include <QSlider>
#include <QSettings>
#include <QPushButton>
#include <QKeyEvent>

//------------------------------------------------------------------------------

static QString const MAINWIN_GEOMETRY("MainWin Geometry");

MainWin::MainWin() {
  setWindowTitle(qApp->applicationName());
  createLayout();

  QSettings s;
  restoreGeometry(s.value(MAINWIN_GEOMETRY).toByteArray());
}

void MainWin::closeEvent(QCloseEvent*) {
  QSettings s;
  s.setValue(MAINWIN_GEOMETRY, saveGeometry());
}

void MainWin::keyPressEvent(QKeyEvent* e) {
  if ("q" == e->text())
    close();
}

void MainWin::mouseDoubleClickEvent(QMouseEvent*) {

}

void MainWin::createLayout() {
  setCentralWidget(new QWidget);

  auto vb = new QVBoxLayout;
  centralWidget()->setLayout(vb);

  vb->addWidget((w3d = new ba3d::Widget3D));
  w3d->setBackground(palette().color(QPalette::Background));

  auto hb = new QHBoxLayout;
  vb->addLayout(hb);

  auto btnSide  = new QPushButton("side");
  auto btnTop   = new QPushButton("top");
  auto btn0     = new QPushButton("0");
  auto btn1     = new QPushButton("1");
  auto sldSigma = new QSlider(Qt::Horizontal);
  auto btnCalc  = new QPushButton("Calc");
  auto btnFlip  = new QPushButton("Flip");

  hb->addWidget(btnSide);
  hb->addWidget(btnTop);
  hb->addStretch();
  hb->addWidget(btn0);
  hb->addWidget(btn1);
  hb->addStretch();
  hb->addWidget(sldSigma);
  hb->addWidget(btnCalc);
  hb->addWidget(btnFlip);

  sldSigma->setRange(0,30);
  sldSigma->setSingleStep(5);
  sldSigma->setTickInterval(5);
  sldSigma->setTickPosition(QSlider::TicksBelow);

  connect(btnSide, &QPushButton::clicked, [this]() {
    model()->setCameraSide(true);
  });

  connect(btnTop, &QPushButton::clicked, [this]() {
    model()->setCameraTop(true);
  });

  connect(btn0, &QPushButton::clicked, [this]() {
    model()->switchBack();
  });

  auto calc = [this, sldSigma]() {
    model()->calc(sldSigma->value() / 100.f);
  };

  auto flip = [this]() {
    model()->flip();
  };

  connect(btnCalc, &QPushButton::clicked, [calc]() {
    calc();
  });

  connect(btnFlip, &QPushButton::clicked, [flip]() {
    flip();
  });
}

DemoModel* MainWin::model() {
  auto model = dynamic_cast<DemoModel*>(w3d->getModel());
  EXPECT(model)
  return model;
}

//------------------------------------------------------------------------------
// eof
