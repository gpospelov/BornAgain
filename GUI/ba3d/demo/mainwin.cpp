// GPL3; https://github.com/jburle/ba3d

#include "mainwin.h"
#include "demo_model.h"

#include <QApplication>
#include <QBoxLayout>
#include <QSlider>
#include <QSettings>
#include <QPushButton>

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

void MainWin::createLayout() {
  setCentralWidget(new QWidget);

  auto vb = new QVBoxLayout;
  centralWidget()->setLayout(vb);

  vb->addWidget((w3d = new ba3d::Widget3D));
  w3d->setBackground(palette().color(QPalette::Background));

  auto hb = new QHBoxLayout;
  vb->addLayout(hb);

  sigmaSlider  = new QSlider(Qt::Horizontal);
  auto recalcButton = new QPushButton("Recalc");

  sigmaSlider->setRange(0,30);
  sigmaSlider->setSingleStep(5);
  sigmaSlider->setTickInterval(5);
  sigmaSlider->setTickPosition(QSlider::TicksBelow);

  hb->addStretch();
  hb->addWidget(sigmaSlider);
  hb->addWidget(recalcButton);

  connect(recalcButton, &QPushButton::clicked, [this]() {
    auto model = dynamic_cast<DemoModel*>(w3d->getModel());
    if (model)
      model->calc(sigmaSlider->value() / 100.f);
  });
}

//------------------------------------------------------------------------------
// eof
