// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/mainwindow.cpp
//! @brief     Implements class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
#include "MaterialEditorWidget.h"
#include "stylehelper.h"
#include "JobModel.h"
#include "MaterialModel.h"
#include "InstrumentModel.h"
#include "MaterialEditor.h"
#include "Instrument.h"
#include "Units.h"
#include "Samples.h"
#include "IconProvider.h"
#include "InterferenceFunctions.h"
#include "FormFactors.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "mainwindow_constants.h"
#include "hostosinfo.h"
#include "projectmanager.h"
#include "progressbar.h"
#include "SimulationRegistry.h"
#include "DomainObjectBuilder.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"
#include "GUIObjectBuilder.h"
#include "tooltipdatabase.h"
#include "mainwindow_constants.h"
#include "ParticleCoreShellItem.h"
#include "GroupProperty.h"
#include "ScientificDoubleProperty.h"
#include "SampleModel.h"
#include "JobView.h"
#include "aboutapplicationdialog.h"
#include "FitModel.h"
#include "FitProxyModel.h"
#include "FitView.h"
#include "TestView.h"
#include "GUIHelpers.h"
#include "UpdateNotifier.h"

#include <boost/scoped_ptr.hpp>

#include <QApplication>
#include <QStatusBar>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_simulationView(0)
    , m_jobView(0)
    , m_fitView(0)
    , m_progressBar(0)
    , m_actionManager(0)
    , m_projectManager(0)
    , m_jobModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_materialModel(0)
    , m_materialEditor(0)
    , m_toolTipDataBase(new ToolTipDataBase(this))
    , m_fitProxyModel(0)
    , m_updateNotifier(new UpdateNotifier(this))
{
    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
    QCoreApplication::setApplicationVersion(GUIHelpers::getBornAgainVersionString());
    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    createModels();
    testGUIObjectBuilder();


    if (!Utils::HostOsInfo::isMacHost())
        QApplication::setWindowIcon(QIcon(":/images/BornAgain.ico"));

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Constants::MAIN_THEME_COLOR));

    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    m_projectManager = new ProjectManager(this);
    m_actionManager = new ActionManager(this);
    readSettings();

    m_tabWidget = new Manhattan::FancyTabWidget(this);
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(m_instrumentModel);
    m_sampleView = new SampleView(m_sampleModel, m_instrumentModel);
    m_simulationView = new SimulationView(this);

//    TestView *testView = new TestView(this);
    //m_fitView = new FitView(m_fitProxyModel, this);

    m_jobView = new JobView(m_jobModel, m_projectManager);


    m_tabWidget->insertTab(WELCOME, m_welcomeView, QIcon(":/images/main_home.png"), "Welcome");
    m_tabWidget->insertTab(INSTRUMENT, m_instrumentView, QIcon(":/images/main_instrument.png"), "Instrument");
    m_tabWidget->insertTab(SAMPLE, m_sampleView, QIcon(":/images/main_sample.png"), "Sample");
    //m_tabWidget->insertTab(3, m_scriptView, QIcon(":/images/mode_script.png"), "Python scripts");
    m_tabWidget->insertTab(SIMULATION, m_simulationView, QIcon(":/images/main_simulation.png"), "Simulation");
    m_tabWidget->insertTab(JOB, m_jobView, QIcon(":/images/main_jobqueue.png"), "Jobs");
//    m_tabWidget->insertTab(TEST_VIEW, testView, QIcon(":/images/main_simulation.png"), "Test");
    //m_tabWidget->insertTab(FitViewTab, m_fitView, QIcon(":/images/main_simulation.png"), "Fit");
    //m_tabWidget->insertTab(FIT_VIEW, new TestView(this), QIcon(":/images/main_simulation.png"), "Test");


    m_tabWidget->setCurrentIndex(TEST_VIEW);

    m_progressBar = new Manhattan::ProgressBar(this);
    m_tabWidget->addBottomCornerWidget(m_progressBar);
    m_progressBar->hide();
    m_jobView->setProgressBar(m_progressBar);

    setCentralWidget(m_tabWidget);

    setAcceptDrops(true);

    // signals/slots
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
    connect(m_jobView, SIGNAL(focusRequest(int)), this, SLOT(onFocusRequest(int)));
    connect(m_updateNotifier, SIGNAL(onUpdateNotification(const QString &)),
            m_welcomeView, SLOT(setNotificationText(const QString &)));

    m_projectManager->createNewProject();
}

MainWindow::~MainWindow()
{
    delete m_materialEditor;
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
    assert(m_projectManager);
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

void MainWindow::onRunSimulationShortcut()
{
    m_simulationView->onRunSimulationShortcut();
}

void MainWindow::openRecentProject()
{
    if (const QAction *action = qobject_cast<const QAction*>(sender())) {
        QString file = action->data().value<QString>();
        qDebug() << "MainWindow::openRecentProject() -> " << file;
        m_projectManager->openProject(file);
    }
}

void MainWindow::onChangeTabWidget(int index)
{
    // update views which depend on others
    (void)index;

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

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_jobModel->getJobQueueData()->hasUnfinishedJobs()) {
        QMessageBox::warning(this, tr("Can't quite the application."),
                             "Can't quite the application while jobs are running.\nCancel running jobs or wait until they are completed.");
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

//! creates and initializes models
void MainWindow::createModels()
{
    // the order is important
    createMaterialModel();

    createSampleModel();

    createInstrumentModel();

    createJobModel();

    //createFitModel();

    resetModels();
}

void MainWindow::createMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
//    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
//    m_materialModel->addMaterial("Air", 0.0, 0.0);
//    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
//    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);
    m_materialEditor = new MaterialEditor(m_materialModel);
}

void MainWindow::createSampleModel()
{
    Q_ASSERT(m_materialModel);
    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);
    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            m_sampleModel, SLOT(onMaterialModelChanged(QModelIndex,QModelIndex)));
}

void MainWindow::createJobModel()
{
    delete m_jobModel;
    m_jobModel = new JobModel(this);
}

void MainWindow::createInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    m_instrumentModel->setIconProvider(new IconProvider());
}

void MainWindow::createFitModel()
{
    m_fitProxyModel = new FitProxyModel;
}

//! reset all models to initial state
void MainWindow::resetModels()
{
    m_materialModel->clear();
    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addMaterial("Air", 0.0, 0.0);
    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    ParameterizedItem *instrument = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument->setItemName("Default GISAS");
    m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument));
    m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument));
}

void MainWindow::testGUIObjectBuilder()
{
    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> P_sample(factory.createSample("CylindersAndPrismsBuilder"));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sampleModel, *P_sample);

//    SimulationRegistry simRegistry;
//    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("RectDetectorPerpToReflectedBeamDpos"));
//    guiBuilder.populateInstrumentModel(m_instrumentModel, *simulation);
}

void MainWindow::onAboutApplication()
{
    AboutApplicationDialog dialog(this);
    dialog.exec();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent( event );
    // Show message box after main window appears
    QTimer::singleShot(100,m_updateNotifier,SLOT(askForUpdates()));
}

