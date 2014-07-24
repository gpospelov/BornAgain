#ifndef QUICKSIMULATIONVIEW_H
#define QUICKSIMULATIONVIEW_H

#include <QWidget>
#include "SessionModel.h"
#include "TestView.h"
#include "PlotWidget.h"

class QuickSimulationView : public QWidget
{
    Q_OBJECT

public:
    QuickSimulationView(SessionModel *sessionModel, QWidget *parent = 0);
    void updateViews();

private:
    SessionModel *m_sessionModel;
    TestView *m_testView;
    PlotWidget *m_plotWidget;

};


#endif
