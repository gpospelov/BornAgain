#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancymainwindow.h"

namespace Manhattan {
    class FancyTabWidget;
}

class TaskSelectorWidget;
class WelcomeView;
class InstrumentView;
class SampleView;
class PyScriptView;
class SimulationView;
class JobView;
class FitView;
class SimulationDataModel;
class Instrument;
class ISample;
class ActionManager;


//class MainWindow : public QMainWindow
class MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SimulationDataModel *getSimulationDataModel() { return mp_sim_data_model; }

public slots:
    void onChangeTabWidget(int index);
    void newProject();
    void openProject();


private:
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    PyScriptView *m_scriptView;
    SimulationView *m_simulationView;
    JobView *m_jobView;
    FitView * m_fitView;
    ActionManager *m_actionManager;

    SimulationDataModel *mp_sim_data_model;
    // dummy simulation model initializer for test purposes
    void initSimModel();
    // dummy instrument creator
    Instrument *createDefaultInstrument();
    ISample *createDefaultSample();

};

#endif // MAINWINDOW_H

