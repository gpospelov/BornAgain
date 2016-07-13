// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/mainwindow.h
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
class ImportDataView;
class SimulationView;
class JobView;
class SessionModelView;

class MaterialModel;
class MaterialSvc;
class SampleModel;
class InstrumentModel;
class RealDataModel;
class JobModel;
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
    enum ETabViewId {WELCOME, INSTRUMENT, SAMPLE, IMPORT, SIMULATION, JOB, MAXVIEWCOUNT};

    explicit MainWindow(QWidget *parent = 0);

    MaterialModel *materialModel();
    InstrumentModel *instrumentModel();
    SampleModel *sampleModel();
    RealDataModel *realDataModel();
    JobModel *jobModel();
    ApplicationModels *models();

    Manhattan::ProgressBar *progressBar();
    QStatusBar *statusBar();

    ActionManager *getActionManager();
    ProjectManager *projectManager();
    UpdateNotifier *getUpdateNotifier();

public slots:
    void onChangeTabWidget(int index);
    void onFocusRequest(int index);
    void openRecentProject();
    void onRunSimulationShortcut();
    void onAboutApplication();
    void onSessionModelViewActive(bool isActive);

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent(QShowEvent *event);

private:
    void initApplication();
    void initProgressBar();
    void initViews();

    void readSettings();
    void writeSettings();
    void initConnections();

    Manhattan::FancyTabWidget  *m_tabWidget;
    Manhattan::ProgressBar *m_progressBar;

    ApplicationModels *m_applicationModels;
    ProjectManager *m_projectManager;
    ActionManager *m_actionManager;
    ToolTipDataBase *m_toolTipDataBase;
    UpdateNotifier *m_updateNotifier;

    WelcomeView *m_welcomeView;
    InstrumentView *m_instrumentView;
    SampleView *m_sampleView;
    ImportDataView *m_importDataView;
    SimulationView *m_simulationView;
    JobView *m_jobView;
    SessionModelView *m_sessionModelView;
};

#endif // MAINWINDOW_H

