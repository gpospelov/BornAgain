#ifndef JOBLISTTOOLBAR_H
#define JOBLISTTOOLBAR_H


#include <QToolBar>
#include "WinDllMacros.h"

class QToolButton;


//! The JobListToolBar contains buttons (add, remove jobs) needed for JobListView
class BA_CORE_API_ JobListToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit JobListToolBar(QWidget *parent = 0);

signals:
    void runJob();
    void removeJob();

private:
    QToolButton *m_runJobButton;
    QToolButton *m_removeJobButton;
};


#endif

