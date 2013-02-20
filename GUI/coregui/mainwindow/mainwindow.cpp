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
{
    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));

//    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Manhattan::Utils::StyleHelper::DEFAULT_BASE_COLOR));
//    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0xCC6600));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0x086FA1));

//    BornAgain::Utils::StyleHelper::setBaseColor(QColor(0xCC6600));


    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    //m_tabWidget = new TaskSelectorWidget(this);
    m_tabWidget = new Manhattan::FancyTabWidget(this);
    m_welcomeView = new WelcomeManager(this);
    m_instrumentView = new InstrumentManager(this);
    m_sampleView = new SampleManager(this);
    m_simulationView = new SimulationManager(this);
    m_fitView = new FitManager(this);

    m_tabWidget->insertTab(0, m_welcomeView, QIcon("./images/mode_welcome.png"), "Welcome");
    m_tabWidget->insertTab(1, m_instrumentView, QIcon("./images/mode_exp.png"), "Instrument");
    m_tabWidget->insertTab(2, m_sampleView, QIcon("./images/mode_sample.png"), "Sample");
    m_tabWidget->insertTab(3, m_simulationView, QIcon("./images/mode_simul.png"), "Simulation");
    m_tabWidget->insertTab(4, m_fitView, QIcon("./images/mode_fit.png"), "Fit");

    setCentralWidget(m_tabWidget);

//    m_tabWidget->statusBar()->setProperty("p_styled", true);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{

}
