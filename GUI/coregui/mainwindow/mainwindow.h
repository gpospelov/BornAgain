// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.h
//! @brief     Declares class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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

class WelcomeView;
class InstrumentView;
class SampleView;
class SimulationView;
class JobView;
class ObsoleteFitView;

class MaterialModel;
class MaterialSvc;
class SampleModel;
class InstrumentModel;
class JobModel;
class ObsoleteFitModel;
class ApplicationModels;
class ProjectManager;
class ActionManager;
class QSettings;
class ToolTipDataBase;
class UpdateNotifier;


class BA_CORE_API_ MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ETabViewId {WELCOME, INSTRUMENT, SAMPLE, SIMULATION, JOB, FIT, TESTVIEW};

    explicit MainWindow(QWidget *parent = 0);

    MaterialModel *materialModel();
    InstrumentModel *instrumentModel();
    SampleModel *sampleModel();
    JobModel *jobModel();
    ObsoleteFitModel *fitModel();
    ApplicationModels *models();

    Manhattan::ProgressBar *getProgressBar() { return m_progressBar; }
    ActionManager *getActionManager() { return m_actionManager; }
    ProjectManager *projectManager() { return m_projectManager; }
    UpdateNotifier *getUpdateNotifier() { return m_updateNotifier; }


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
    virtual void showEvent(QShowEvent *event);

private:
    ApplicationModels *m_applicationModels;
    ProjectManager *m_projectManager;
    ActionManager *m_actionManager;

    Manhattan::FancyTabWidget  *m_tabWidget;
    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    SimulationView *m_simulationView;
    JobView *m_jobView;
    ObsoleteFitView *m_fitView;
    Manhattan::ProgressBar *m_progressBar;
    ToolTipDataBase *m_toolTipDataBase;
    UpdateNotifier *m_updateNotifier;
};

#endif // MAINWINDOW_H

