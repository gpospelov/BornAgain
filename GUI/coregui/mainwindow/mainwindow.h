#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancymainwindow.h"

namespace Manhattan {
    class FancyTabWidget;
}

class TaskSelectorWidget;
class WelcomeManager;
class InstrumentView;
class SampleManager;
class SimulationManager;
class FitManager;
class SimulationDataModel;
class Instrument;

//class MainWindow : public QMainWindow
class MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SimulationDataModel *getSimulationDataModel() { return mp_sim_data_model; }
    
private:
    //TaskSelectorWidget *m_tabWidget;
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeManager *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleManager *m_sampleView;
    SimulationManager *m_simulationView;
    FitManager * m_fitView;

    SimulationDataModel *mp_sim_data_model;
    // dummy simulation model initializer for test purposes
    void initSimModel();
    // dummy instrument creator
    Instrument *createDefaultInstrument();
};

#endif // MAINWINDOW_H
