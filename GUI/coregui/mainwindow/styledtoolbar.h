#ifndef STYLEDTOOLBAR_H
#define STYLEDTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class BA_CORE_API_ StyledToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit StyledToolBar(QWidget *parent = 0);

};


#endif // STYLEDTOOLBAR_H

