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
  auto btnOne   = new QPushButton("one");
  auto btn0     = new QPushButton("=");
  auto btn1     = new QPushButton("1|n");
  auto btnP     = new QPushButton("p");
  auto sldSigma = new QSlider(Qt::Horizontal);
  auto btnSq    = new QPushButton("><");

  hb->addWidget(btnSide);
  hb->addWidget(btnTop);
  hb->addWidget(btnOne);
  hb->addStretch();
  hb->addWidget(btn0);
  hb->addWidget(btn1);
  hb->addWidget(btnP);
  hb->addStretch();
  hb->addWidget(sldSigma);
  hb->addWidget(btnSq);

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

  connect(btnOne, &QPushButton::clicked, [this]() {
    model()->setCameraOne(true);
  });

  connect(btn0, &QPushButton::clicked, [this]() {
    model()->switchBack();
  });

  connect(btn1, &QPushButton::clicked, [this]() {
    model()->switchFront();
  });

  connect(btnP, &QPushButton::clicked, [this]() {
    model()->switchOne();
  });

  connect(btnSq, &QPushButton::clicked, [this, sldSigma]() {
    model()->square(sldSigma->value() / 100.f);
  });
}

DemoModel* MainWin::model() {
  auto model = dynamic_cast<DemoModel*>(w3d->getModel());
  EXPECT(model)
  return model;
}

//------------------------------------------------------------------------------
// eof
