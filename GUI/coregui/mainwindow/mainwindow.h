#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fancymainwindow.h"

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
class JobQueueView;
class SimulationDataModel;
class Instrument;
class ISample;
class ActionManager;
class ProjectManager;
class QCloseEvent;
class QSettings;
class JobQueueModel;
class InstrumentModel;
class MaterialEditor;
class ToolTipDataBase;
class MaterialModel;
class SampleModel;


class MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT
    
public:
    enum TabViewId { WelcomeTab, InstrumentTab, SampleTab, SimulationTab, JobTab, TestViewTab};

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SimulationDataModel *getSimulationDataModel() { return mp_sim_data_model; }
    MaterialModel *getMaterialModel() { return m_materialModel; }
    InstrumentModel *getInstrumentModel() { return m_instrumentModel; }
    SampleModel *getSampleModel() { return m_sampleModel; }
    JobQueueModel *getJobQueueModel() { return m_jobQueueModel; }
    Manhattan::ProgressBar *getProgressBar() { return m_progressBar; }
    QSettings *getSettings() const { return m_settings; }
    ActionManager *getActionManager() { return m_actionManager; }
    ProjectManager *getProjectManager() { return m_projectManager; }

public slots:
    void onChangeTabWidget(int index);
    void onFocusRequest(int index);
    void openRecentProject();
    void readSettings();
    void writeSettings();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    PyScriptView *m_scriptView;
    SimulationView *m_simulationView;
    JobQueueView * m_jobQueueView;
    Manhattan::ProgressBar *m_progressBar;

    ActionManager *m_actionManager; //!< responsible for menus and actions
    ProjectManager *m_projectManager; //!< handles activity related to opening/saving projects
    QSettings *m_settings; //!< application wide settings

    SimulationDataModel *mp_sim_data_model;
    JobQueueModel *m_jobQueueModel; //!< model for all jobs
    SampleModel *m_sampleModel; //!< model for all samples
    InstrumentModel *m_instrumentModel; //!< model for all instruments
    MaterialModel *m_materialModel; //!< model for all materials
    MaterialEditor *m_materialEditor;
    ToolTipDataBase *m_toolTipDataBase;

    void initModels();
    void initMaterialModel();
    void initSampleModel();
    void initJobQueueModel();
    void initSimModel();
    void initInstrumentModel();

    void updateSimModel();
    void updateSamples();
    void updateInstruments();

    void testGUIObjectBuilder();
};

#endif // MAINWINDOW_H

