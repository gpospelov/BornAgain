#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancymainwindow.h"
#include "mainwindow_constants.h"


namespace Manhattan {
    class FancyTabWidget;
    class ProgressBar;
}

class TaskSelectorWidget;
class WelcomeView;
class InstrumentView;
class SampleView;
class PyScriptView;
class SimulationView;
class JobView;
class FitView;
class JobQueueView;
class SimulationDataModel;
class Instrument;
class ISample;
class ActionManager;
class ProjectManager;
class QCloseEvent;
class QSettings;
class JobQueueModel;
class SessionModel;


//class MainWindow : public QMainWindow
class MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SimulationDataModel *getSimulationDataModel() { return mp_sim_data_model; }
    SessionModel *getSessionModel() { return m_sessionModel; }
    JobQueueModel *getJobQueueModel() { return m_jobQueueModel; }

    Manhattan::ProgressBar *getProgressBar() { return m_progressBar; }

public slots:
    void onChangeTabWidget(int index);
    void openRecentProject();
    void readSettings();
    void writeSettings();
    QSettings *getSettings() const;
    ActionManager *getActionManager() { return m_actionManager; }
    ProjectManager *getProjectManager() { return m_projectManager; }

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    PyScriptView *m_scriptView;
    SimulationView *m_simulationView;
    FitView * m_fitView;
    JobQueueView * m_jobQueueView;
    Manhattan::ProgressBar *m_progressBar;

    ActionManager *m_actionManager; //!< responsible for menus and actions
    ProjectManager *m_projectManager; //!< handles activity related to opening/saving projects
    QSettings *m_settings; //!< application wide settings

    SimulationDataModel *mp_sim_data_model;
    JobQueueModel *m_jobQueueModel; //!< model for all jobs
    SessionModel *m_sessionModel; //!< model for all samples

    // dummy simulation model initializer for test purposes
    void initSimModel();
    void initJobQueueModel();
    void initSessionModel();
    // dummy instrument creator
    Instrument *createDefaultInstrument();
    ISample *createDefaultSample();

};

#endif // MAINWINDOW_H

