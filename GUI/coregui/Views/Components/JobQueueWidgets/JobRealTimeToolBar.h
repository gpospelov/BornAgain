#ifndef JOBREALTIMETOOLBAR_H
#define JOBREALTIMETOOLBAR_H

#include <QToolBar>
#include "WinDllMacros.h"

class QToolButton;


//! The ModelTuningToolBar contains buttons needed for ModelTuningWidget
class BA_CORE_API_ JobRealTimeToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit JobRealTimeToolBar(QWidget *parent = 0);

signals:
    void resetParameters();
    //void exportParameters();

private:
    QToolButton *m_resetParametersButton;
    QToolButton *m_exportParametersButton;
};


#endif

