#ifndef OUTPUTDATATOOLBAR_H
#define OUTPUTDATATOOLBAR_H

#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class OutputDataToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit OutputDataToolBar(QWidget *parent = 0);

signals:
    void togglePropertyPanel();
    void savePlot();


private:

    QAction *m_togglePropertyPanelAction;
    QAction *m_savePlotAction;
};


#endif // OUTPUTDATATOOLBAR_H
