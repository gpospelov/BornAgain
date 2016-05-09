// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.cpp
//! @brief     Implements class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "actionmanager.h"
#include "WelcomeView.h"
#include "SampleView.h"
#include "JobQueueData.h"
#include "InstrumentView.h"
#include "SimulationView.h"
#include "stylehelper.h"
#include "JobModel.h"
#include "ApplicationModels.h"
#include "mainwindow_constants.h"
#include "hostosinfo.h"
#include "projectmanager.h"
#include "progressbar.h"
#include "tooltipdatabase.h"
#include "mainwindow_constants.h"
#include "JobView.h"
#include "aboutapplicationdialog.h"
#include "ObsoleteFitView.h"
#include "TestView.h"
#include "GUIHelpers.h"
#include "UpdateNotifier.h"
#include "TestFitWidgets.h"

#include <QApplication>
#include <QStatusBar>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(new Manhattan::FancyTabWidget(this))
    , m_progressBar(new Manhattan::ProgressBar(this))
    , m_applicationModels(new ApplicationModels(this))
    , m_projectManager(new ProjectManager(this))
    , m_actionManager(new ActionManager(this))
    , m_toolTipDataBase(new ToolTipDataBase(this))
    , m_updateNotifier(new UpdateNotifier(this))
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_simulationView(0)
    , m_jobView(0)
    , m_fitView(0)
{
    initApplication();
    readSettings();
    initProgressBar();
    initViews();
    initConnections();

    //m_applicationModels->createTestJob();
}

MaterialModel *MainWindow::materialModel()
{
    return models()->materialModel();
}

InstrumentModel *MainWindow::instrumentModel()
{
    return models()->instrumentModel();
}

SampleModel *MainWindow::sampleModel()
{
    return models()->sampleModel();
}

JobModel *MainWindow::jobModel()
{
    return models()->jobModel();
}

ObsoleteFitModel *MainWindow::fitModel()
{
    Q_ASSERT(0);
    return 0;
}

ApplicationModels *MainWindow::models()
{
    return m_applicationModels;
}

Manhattan::ProgressBar *MainWindow::progressBar()
{
    return m_progressBar;
}

QStatusBar *MainWindow::statusBar()
{
    return m_tabWidget->statusBar();
}

ActionManager *MainWindow::getActionManager()
{
    return m_actionManager;
}

ProjectManager *MainWindow::projectManager()
{
    return m_projectManager;
}

UpdateNotifier *MainWindow::getUpdateNotifier()
{
    return m_updateNotifier;
}

//! updates views which depend on others
void MainWindow::onChangeTabWidget(int index)
{
    if(index == WELCOME)
    {
        m_welcomeView->updateRecentProjectPanel();
    }
    else if (index == INSTRUMENT) {
        m_instrumentView->updateView();
    }
    else if(index == SIMULATION) {
        m_simulationView->updateSimulationViewElements();
    }
}

void MainWindow::onFocusRequest(int index)
{
    m_tabWidget->setCurrentIndex(index);
}

void MainWindow::openRecentProject()
{
    if (const QAction *action = qobject_cast<const QAction*>(sender())) {
        QString file = action->data().value<QString>();
        qDebug() << "MainWindow::openRecentProject() -> " << file;
        m_projectManager->openProject(file);
    }
}

void MainWindow::onRunSimulationShortcut()
{
    m_simulationView->onRunSimulationShortcut();
}

void MainWindow::onAboutApplication()
{
    AboutApplicationDialog dialog(this);
    dialog.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(jobModel()->hasUnfinishedJobs()) {
        QMessageBox::warning(this, tr("Can't quite the application."),
                             "Can't quite the application while jobs are running.\n"
                             "Cancel running jobs or wait until they are completed.");
        event->ignore();
        return;
    }

    if(m_projectManager->closeCurrentProject())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//! Launch update notifier after main window appears
void MainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent( event );
    QTimer::singleShot(100, m_updateNotifier, SLOT(askForUpdates()));
}

void MainWindow::initApplication()
{
    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
    QCoreApplication::setApplicationVersion(GUIHelpers::getBornAgainVersionString());
    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    if (!Utils::HostOsInfo::isMacHost())
        QApplication::setWindowIcon(QIcon(":/images/BornAgain.ico"));

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Constants::MAIN_THEME_COLOR));

    setDockNestingEnabled(true);
    setAcceptDrops(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
}

void MainWindow::initProgressBar()
{
    m_tabWidget->addBottomCornerWidget(m_progressBar);
    m_progressBar->hide();
}

void MainWindow::initViews()
{
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(instrumentModel());
    m_sampleView = new SampleView(sampleModel(), instrumentModel());
    m_simulationView = new SimulationView(this);

    m_jobView = new JobView(this);
    TestView *testView = new TestView(this);
    TestFitWidgets *testFitWidgets = new TestFitWidgets(this);
    //m_fitView = new FitView(this);

    m_tabWidget->insertTab(WELCOME, m_welcomeView, QIcon(":/images/main_home.png"), "Welcome");
    m_tabWidget->insertTab(INSTRUMENT, m_instrumentView, QIcon(":/images/main_instrument.png"), "Instrument");
    m_tabWidget->insertTab(SAMPLE, m_sampleView, QIcon(":/images/main_sample.png"), "Sample");
    m_tabWidget->insertTab(SIMULATION, m_simulationView, QIcon(":/images/main_simulation.png"), "Simulation");
    m_tabWidget->insertTab(JOB, m_jobView, QIcon(":/images/main_jobqueue.png"), "Jobs");
    //m_tabWidget->insertTab(FIT, m_fitView, QIcon(":/images/main_jobqueue.png"), "Fit");
    m_tabWidget->insertTab(FIT, testView, QIcon(":/images/main_jobqueue.png"), "Test");
    m_tabWidget->insertTab(TESTVIEW, testFitWidgets, QIcon(":/images/main_jobqueue.png"), "TestView");

    m_tabWidget->setCurrentIndex(WELCOME);

    setCentralWidget(m_tabWidget);
}

void MainWindow::readSettings()
{
    QSettings settings;
    if(settings.childGroups().contains(Constants::S_MAINWINDOW)) {
        settings.beginGroup(Constants::S_MAINWINDOW);
        resize(settings.value(Constants::S_WINDOWSIZE, QSize(400, 400)).toSize());
        move(settings.value(Constants::S_WINDOWPOSITION, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
    m_projectManager->readSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_MAINWINDOW);
    settings.setValue(Constants::S_WINDOWSIZE, size());
    settings.setValue(Constants::S_WINDOWPOSITION, pos());
    settings.endGroup();
    m_projectManager->writeSettings();
    settings.sync();
}

void MainWindow::initConnections()
{
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
    connect(m_jobView, SIGNAL(focusRequest(int)), this, SLOT(onFocusRequest(int)));
    connect(m_updateNotifier, SIGNAL(onUpdateNotification(const QString &)),
            m_welcomeView, SLOT(setNotificationText(const QString &)));
}
