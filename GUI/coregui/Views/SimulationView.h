#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include "qstandarditemmodel.h"
#include "SimulationSetupWidget.h"
#include "QuickSimulationWidget.h"
#include <QTabWidget>

class MainWindow;
class SimulationDataModel;
class JobQueueModel;
class SampleModel;
class InstrumentModel;

class SimulationView : public QWidget
{
    Q_OBJECT

public:
    enum TabViewId { SimulationSetupTab, QuickSimulationTab};
    SimulationView(MainWindow *mainWindow);

    void updateSimulationViewElements();

public slots:
    void onChangeTabWidget(int index);

private:
    SimulationDataModel *mp_simulation_data_model;
    JobQueueModel *m_jobQueueModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    SimulationSetupWidget *m_simulationSetupWidget;
    QuickSimulationWidget *m_quickSimulationWidget;
    QTabWidget *m_tabWidget;

};


#endif // SIMULATIONVIEW_H

