#ifndef SIMULATIONTABVIEW_H
#define SIMULATIONTABVIEW_H

#include <QWidget>
#include "qstandarditemmodel.h"
#include "SessionModel.h"
#include "SimulationView.h"
#include "QuickSimulationView.h"
#include <QTabWidget>

class SimulationDataModel;
class JobQueueModel;



class SimulationTabView : public QWidget
{
    Q_OBJECT

public:
    enum TabViewId { SimulationParamsTab, QuickSimulationTab};
    SimulationTabView(SimulationDataModel *p_simulation_data_model, JobQueueModel *jobQueueModel, SessionModel *sessionModel, QWidget *parent = 0);
    void updateSimulationViewElements();

public slots:
    void onChangeTabWidget(int index);

private:
    SimulationDataModel *mp_simulation_data_model;
    JobQueueModel *m_jobQueueModel;
    SessionModel *m_sessionModel;

    SimulationView *m_simulationView;
    QuickSimulationView *m_quickSimulationView;
    QTabWidget *m_tabWidget;

};


#endif
