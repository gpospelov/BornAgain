#include "SimulationToolBar.h"
#include "styledbar.h"

#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <iostream>


SimulationToolBar::SimulationToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    QAction *action = new QAction(QIcon(":/SampleDesigner/images/refresh.png"), tr("Reset View, Ctrl+R"), this);
    this->addAction(action);

}
