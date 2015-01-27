// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.h
//! @brief     Defines class MainWindow
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WinDllMacros.h"
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
class FitProxyModel;
class FitView;


class BA_CORE_API_ MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ETabViewId { WELCOME, INSTRUMENT, SAMPLE, SIMULATION, JOB, FIT_VIEW};

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void onRunSimulationShortcut();
    void onAboutApplication();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    PyScriptView *m_scriptView;
    SimulationView *m_simulationView;

    JobView *m_jobView;
    FitView *m_fitView;

    Manhattan::ProgressBar *m_progressBar;

    ActionManager *m_actionManager; //!< responsible for menus and actions
    ProjectManager *m_projectManager; //!< handles activity related to opening/saving projects
    QSettings *m_settings; //!< application wide settings

    JobQueueModel *m_jobQueueModel; //!< model for all jobs
    SampleModel *m_sampleModel; //!< model for all samples
    InstrumentModel *m_instrumentModel; //!< model for all instruments
    MaterialModel *m_materialModel; //!< model for all materials
    MaterialEditor *m_materialEditor;
    ToolTipDataBase *m_toolTipDataBase;
    FitProxyModel *m_fitProxyModel;

    void initModels();
    void initMaterialModel();
    void initSampleModel();
    void initJobQueueModel();
    void initInstrumentModel();
    void initFitModel();

    void updateSimModel();
    void updateSamples();
    void updateInstruments();

    void testGUIObjectBuilder();
};

#endif // MAINWINDOW_H

