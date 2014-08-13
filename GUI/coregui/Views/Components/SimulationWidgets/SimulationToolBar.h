#ifndef SIMULATIONTOOLBAR_H
#define SIMULATIONTOOLBAR_H

#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class SimulationToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SimulationToolBar(QWidget *parent = 0);

};


#endif // SIMULATIONTOOLBAR_H
