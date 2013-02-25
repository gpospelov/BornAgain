#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "taskselectorwidget.h"
#include "WelcomeView.h"
#include "SampleView.h"
#include "InstrumentView.h"
#include "SimulationView.h"
#include "FitView.h"
#include "stylehelper.h"
#include "ba_stylehelper.h"
#include "SimulationDataModel.h"
#include "Instrument.h"
#include "Units.h"

#include <QApplication>
#include <iostream>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_simulationView(0)
    , m_fitView(0)
    , mp_sim_data_model(0)
{
    // initialize simulation data model first:
    initSimModel();

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));

//    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Manhattan::Utils::StyleHelper::DEFAULT_BASE_COLOR));
//    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0xCC6600));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0x086FA1));


    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    //m_tabWidget = new TaskSelectorWidget(this);
    m_tabWidget = new Manhattan::FancyTabWidget(this);
    m_welcomeView = new WelcomeManager(this);
    m_instrumentView = new InstrumentView(mp_sim_data_model, this);
    m_sampleView = new SampleManager(this);
    m_simulationView = new SimulationManager(mp_sim_data_model, this);
    m_fitView = new FitManager(this);

    m_tabWidget->insertTab(0, m_welcomeView, QIcon(":/images/mode_welcome.png"), "Welcome");
    m_tabWidget->insertTab(1, m_instrumentView, QIcon(":/images/mode_exp.png"), "Instrument");
    m_tabWidget->insertTab(2, m_sampleView, QIcon(":/images/mode_sample.png"), "Sample");
    m_tabWidget->insertTab(3, m_simulationView, QIcon(":/images/mode_simul.png"), "Simulation");
    m_tabWidget->insertTab(4, m_fitView, QIcon(":/images/mode_fit.png"), "Fit");

    setCentralWidget(m_tabWidget);

//    m_tabWidget->statusBar()->setProperty("p_styled", true);
    setAcceptDrops(true);

    // signals/slots
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onChangeTabWidget(int index)
{
    // update views which depend on others
    m_simulationView->updateViewElements();
}

void MainWindow::initSimModel()
{
    if (mp_sim_data_model) delete mp_sim_data_model;
    mp_sim_data_model = new SimulationDataModel;
    mp_sim_data_model->addInstrument(tr("Default GISAS"), createDefaultInstrument());
}

Instrument *MainWindow::createDefaultInstrument()
{
    Instrument *p_result = new Instrument;
    p_result->setBeamParameters(0.1*Units::nanometer, 0.4*Units::degree, 0.0);
    p_result->setBeamIntensity(1e7);
    p_result->setDetectorParameters(100, 0.0, 6.0*Units::degree,
                                    100, 0.0, 3.0*Units::degree);
    return p_result;
}
