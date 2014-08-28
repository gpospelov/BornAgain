#ifndef SIMULATIONTOOLBAR_H
#define SIMULATIONTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class BA_CORE_API_ SimulationToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SimulationToolBar(QWidget *parent = 0);

};


#endif // SIMULATIONTOOLBAR_H
