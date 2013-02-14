#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "taskselectorwidget.h"
#include "welcomemanager.h"
#include "samplemanager.h"
#include "experimentmanager.h"
#include "simulationmanager.h"
#include "fitmanager.h"
#include "stylehelper.h"
#include "ba_stylehelper.h"

#include <QApplication>
#include <iostream>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
//    : FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeManager(0)
    , m_sampleManager(0)
    , m_expManager(0)
    , m_simulManager(0)
    , m_fitManager(0)
{
    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));

//    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Manhattan::Utils::StyleHelper::DEFAULT_BASE_COLOR));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0xCC6600));

//    BornAgain::Utils::StyleHelper::setBaseColor(QColor(0xCC6600));


    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    //m_tabWidget = new TaskSelectorWidget(this);
    m_tabWidget = new Manhattan::FancyTabWidget(this);
    m_welcomeManager = new WelcomeManager();
    m_sampleManager = new SampleManager();
    m_expManager = new ExperimentManager();
    m_simulManager = new SimulationManager();
    m_fitManager = new FitManager();

    m_tabWidget->insertTab(0, m_welcomeManager, QIcon("./images/mode_welcome.png"), "Welcome");
    m_tabWidget->insertTab(1, m_sampleManager, QIcon("./images/mode_sample.png"), "Sample");
    m_tabWidget->insertTab(2, m_expManager, QIcon("./images/mode_exp.png"), "Experiment");
    m_tabWidget->insertTab(3, m_simulManager, QIcon("./images/mode_simul.png"), "Simulation");
    m_tabWidget->insertTab(4, m_fitManager, QIcon("./images/mode_fit.png"), "Fit");

    setCentralWidget(m_tabWidget);

//    m_tabWidget->statusBar()->setProperty("p_styled", true);
    setAcceptDrops(true);

}

MainWindow::~MainWindow()
{

}
