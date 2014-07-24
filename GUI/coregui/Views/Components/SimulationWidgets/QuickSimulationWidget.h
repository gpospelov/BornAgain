#ifndef QUICKSIMULATIONWIDGET_H
#define QUICKSIMULATIONWIDGET_H

#include <QWidget>
#include "SessionModel.h"
#include "SampleTuningWidget.h"
#include "PlotWidget.h"

class QuickSimulationWidget : public QWidget
{
    Q_OBJECT

public:
    QuickSimulationWidget(SessionModel *sessionModel, QWidget *parent = 0);
    void updateViews();

private:
    SessionModel *m_sessionModel;
    SampleTuningWidget *m_testView;
    PlotWidget *m_plotWidget;

};


#endif // QUICKSIMULATIONWIDGET_H

