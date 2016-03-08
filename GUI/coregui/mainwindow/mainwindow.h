// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.h
//! @brief     Defines class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"
#include <QMainWindow>

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
class InstrumentModel;
class MaterialSvc;
class ToolTipDataBase;
class MaterialModel;
class SampleModel;
class FitView;
class JobModel;
class UpdateNotifier;
class FitModel;

class BA_CORE_API_ MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ETabViewId { WELCOME, INSTRUMENT, SAMPLE, SIMULATION, JOB, FIT, TESTVIEW};

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    MaterialModel *getMaterialModel() { return m_materialModel; }
    InstrumentModel *getInstrumentModel() { return m_instrumentModel; }
    SampleModel *getSampleModel() { return m_sampleModel; }
    JobModel *getJobModel() { return m_jobModel; }
    FitModel *getFitModel() { return m_fitModel; }
    Manhattan::ProgressBar *getProgressBar() { return m_progressBar; }
    ActionManager *getActionManager() { return m_actionManager; }
    ProjectManager *getProjectManager() { return m_projectManager; }
    UpdateNotifier *getUpdateNotifier() { return m_updateNotifier; }

public slots:
    void onChangeTabWidget(int index);
    void onFocusRequest(int index);
    void openRecentProject();
    void readSettings();
    void writeSettings();
    void onRunSimulationShortcut();
    void onAboutApplication();
    void resetModels();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    SimulationView *m_simulationView;

    JobView *m_jobView;
    FitView *m_fitView;

    Manhattan::ProgressBar *m_progressBar;

    ActionManager *m_actionManager; //!< responsible for menus and actions
    ProjectManager *m_projectManager; //!< handles activity related to opening/saving projects

    JobModel *m_jobModel;  //!< model for all jobs
    SampleModel *m_sampleModel; //!< model for all samples
    InstrumentModel *m_instrumentModel; //!< model for all instruments
    MaterialModel *m_materialModel; //!< model for all materials
    FitModel *m_fitModel; //!< model for fitting
    MaterialSvc *m_materialEditor;
    ToolTipDataBase *m_toolTipDataBase;
    UpdateNotifier *m_updateNotifier;

    void createModels();
    void createMaterialModel();
    void createSampleModel();
    void createJobModel();
    void createInstrumentModel();
    void createFitModel();

    void testGUIObjectBuilder();
    virtual void showEvent(QShowEvent *event);
};

#endif // MAINWINDOW_H

