#include "FitToolBar.h"
#include "styledbar.h"

#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <iostream>


FitToolBar::FitToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    this->addAction(new QAction(0));

}
