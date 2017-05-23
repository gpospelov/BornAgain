// GPL3; https://github.com/jburle/ba3d

#include "mainwin.h"

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QMenuBar>
#include <QComboBox>
#include <QKeyEvent>
#include <QSettings>

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

  auto hb = new QHBoxLayout;
  centralWidget()->setLayout(hb);

  // the thing
  hb->addWidget((w3d_1 = new ba3d::Widget3D));
  hb->setStretchFactor(w3d_1, 2);
  w3d_1->setBackground(palette().color(QPalette::Background));

  auto vb = new QVBoxLayout;
  hb->addLayout(vb);
  hb->setStretchFactor(vb, 1);

  vb->addWidget((w3d_2 = new ba3d::Widget3D));
  vb->setStretchFactor(w3d_2, 1);

  vb->addWidget((w3d_3 = new ba3d::Widget3D));
  vb->setStretchFactor(w3d_3, 1);

  vb->addWidget((combo = new QComboBox));

  {
    using namespace ba3d::particle;
    connect(combo, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), [&](int i) {
      emit showKind(kind(int(Particle::firstKind)+i));
    });

    for (kind k=Particle::firstKind; k <= Particle::lastKind; k = kind(uint(k)+1))
      combo->addItem(name(k));
  }
}

//------------------------------------------------------------------------------
// eof
