#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class JobQueueModel;
class SampleModel;
class InstrumentModel;
class SimulationSetupWidget;
class StyledToolBar;

class BA_CORE_API_ SimulationView : public QWidget
{
    Q_OBJECT

public:
    enum ETabViewId { SIMULATION_SETUP, QUICK_SIMULATION};
    SimulationView(MainWindow *mainWindow);

    void updateSimulationViewElements();

public slots:
    void onRunSimulationShortcut();

private:
    JobQueueModel *m_jobQueueModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    SimulationSetupWidget *m_simulationSetupWidget;
    StyledToolBar *m_toolBar;
};


#endif // SIMULATIONVIEW_H

