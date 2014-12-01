#ifndef FITTOOLBAR_H
#define FITTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;


class BA_CORE_API_ FitToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit FitToolBar(QWidget *parent = 0);

};


#endif // SIMULATIONTOOLBAR_H
