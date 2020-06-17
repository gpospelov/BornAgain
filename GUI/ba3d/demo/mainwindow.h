// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/demo/mainwindow.h
//! @brief     Defines MainWin class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MAINWINDOW_H
#define BA3D_MAINWINDOW_H

#include "demo_model.h"
#include <QMainWindow>
#include <ba3d/model/particles.h>
#include <ba3d/widget.h>

class QSlider;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    RealSpace::Widget3D& widget3d() { return *w3d; }

private:
    void closeEvent(QCloseEvent*);
    void keyPressEvent(QKeyEvent*);

    void createLayout();
    RealSpace::Widget3D* w3d;

    class DemoModel* model();
};

#endif // BA3D_MAINWINDOW_H
