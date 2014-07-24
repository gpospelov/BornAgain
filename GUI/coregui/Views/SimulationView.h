#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include "qstandarditemmodel.h"
#include "SessionModel.h"
#include "SimulationSetupWidget.h"
#include "QuickSimulationWidget.h"
#include <QTabWidget>

class SimulationDataModel;
class JobQueueModel;


class SimulationView : public QWidget
{
    Q_OBJECT

public:
    enum TabViewId { SimulationSetupTab, QuickSimulationTab};
    SimulationView(SimulationDataModel *p_simulation_data_model, JobQueueModel *jobQueueModel, SessionModel *sessionModel, QWidget *parent = 0);
    void updateSimulationViewElements();

public slots:
    void onChangeTabWidget(int index);

private:
    SimulationDataModel *mp_simulation_data_model;
    JobQueueModel *m_jobQueueModel;
    SessionModel *m_sessionModel;

    SimulationSetupWidget *m_simulationSetupWidget;
    QuickSimulationWidget *m_quickSimulationWidget;
    QTabWidget *m_tabWidget;

};


#endif // SIMULATIONVIEW_H

