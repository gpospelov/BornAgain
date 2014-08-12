#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "actionmanager.h"
#include "WelcomeView.h"
#include "SampleView.h"
#include "PyScriptView.h"
#include "InstrumentView.h"
#include "SimulationView.h"
#include "JobQueueView.h"
#include "MaterialEditorWidget.h"
#include "stylehelper.h"
#include "SimulationDataModel.h"
#include "JobQueueModel.h"
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
#include "FancyGroupProperty.h"
#include "ScientificDoubleProperty.h"
#include "SampleModel.h"
//#include "TestView.h"
#include <boost/scoped_ptr.hpp>

#include <QApplication>
#include <QStatusBar>
#include <QSettings>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_scriptView(0)
    , m_simulationView(0)
    , m_jobQueueView(0)
    , m_progressBar(0)
    , m_actionManager(0)
    , m_projectManager(0)
    , m_settings(new QSettings(Constants::APPLICATION_NAME, Constants::APPLICATION_NAME, this))
    , mp_sim_data_model(0)
    , m_jobQueueModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_materialModel(0)
    , m_materialEditor(0)
    , m_toolTipDataBase(new ToolTipDataBase(this))
{
//    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
//    QCoreApplication::setApplicationVersion(QLatin1String(Constants::APPLICATION_VERSION));
//    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    initModels();

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(0x086FA1));

    setDockNestingEnabled(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    m_projectManager = new ProjectManager(this);
    m_actionManager = new ActionManager(this);
    readSettings();

    m_tabWidget = new Manhattan::FancyTabWidget();
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(m_instrumentModel);
    m_sampleView = new SampleView(m_sampleModel, m_instrumentModel);
    //m_scriptView = new PyScriptView(mp_sim_data_model);
    m_simulationView = new SimulationView(this);
    m_jobQueueView = new JobQueueView(m_jobQueueModel);
    //m_testView = new TestView(m_sampleModel, this);

    m_tabWidget->insertTab(WelcomeTab, m_welcomeView, QIcon(":/images/main_home.png"), "Welcome");
    m_tabWidget->insertTab(InstrumentTab, m_instrumentView, QIcon(":/images/main_instrument.png"), "Instrument");
    m_tabWidget->insertTab(SampleTab, m_sampleView, QIcon(":/images/main_sample.png"), "Sample");
    //m_tabWidget->insertTab(3, m_scriptView, QIcon(":/images/mode_script.png"), "Python scripts");
    m_tabWidget->insertTab(SimulationTab, m_simulationView, QIcon(":/images/main_simulation.png"), "Simulation");
    m_tabWidget->insertTab(JobTab, m_jobQueueView, QIcon(":/images/main_jobqueue.png"), "Jobs");
    //m_tabWidget->insertTab(TestViewTab, m_testView, QIcon(":/images/main_simulation.png"), "Test");


    m_tabWidget->setCurrentIndex(InstrumentTab);

    m_progressBar = new Manhattan::ProgressBar(this);
    m_tabWidget->addBottomCornerWidget(m_progressBar);
    m_progressBar->hide();
    m_jobQueueView->setProgressBar(m_progressBar);

    setCentralWidget(m_tabWidget);


    setAcceptDrops(true);

    // signals/slots
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
    connect(m_jobQueueView, SIGNAL(focusRequest(int)), this, SLOT(onFocusRequest(int)));


    m_projectManager->createNewProject();

    testGUIObjectBuilder();
}


MainWindow::~MainWindow()
{
    delete m_materialEditor;
    delete mp_sim_data_model;
}


void MainWindow::readSettings()
{
    if(m_settings->childGroups().contains("MainWindow")) {
        m_settings->beginGroup("MainWindow");
        resize(m_settings->value("size", QSize(400, 400)).toSize());
        move(m_settings->value("pos", QPoint(200, 200)).toPoint());
        m_settings->endGroup();
    }
    assert(m_projectManager);
    m_projectManager->readSettings(m_settings);
}


void MainWindow::writeSettings()
{
    m_settings->beginGroup("MainWindow");
    m_settings->setValue("size", size());
    m_settings->setValue("pos", pos());
    m_settings->endGroup();

    m_projectManager->writeSettings(m_settings);

    m_settings->sync();
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
    if(index == SimulationTab) {
        updateSimModel();
        m_simulationView->updateSimulationViewElements();
    }
    else if(index == WelcomeTab)
    {
        m_welcomeView->updateRecentProjectPanel();
    }
}


void MainWindow::onFocusRequest(int index)
{
    m_tabWidget->setCurrentIndex(index);
}



void MainWindow::closeEvent(QCloseEvent *event)
{


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

void MainWindow::initModels()
{
    initMaterialModel(); // should be first

    initSampleModel();

    initJobQueueModel();

    initInstrumentModel();

    initSimModel();
}


void MainWindow::initMaterialModel()
{
    delete m_materialModel;

    m_materialModel = new MaterialModel(this);
    m_materialModel->addMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addMaterial("Air", 0.0, 0.0);
    m_materialModel->addMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addMaterial("Substrate", 6e-6, 2e-8);

    m_materialEditor = new MaterialEditor(m_materialModel);
}


void MainWindow::initSampleModel()
{
    Q_ASSERT(m_materialModel);

    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);

    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), m_sampleModel, SLOT(onMaterialModelChanged(QModelIndex,QModelIndex)));

    //m_sampleModel->insertNewItem(Constants::MultiLayerType);
    //ParameterizedItem *multilayer = m_sampleModel->insertNewItem(Constants::MultiLayerType);
    //m_sampleModel->insertNewItem(Constants::MultiLayerType);
}



void MainWindow::initJobQueueModel()
{
    delete m_jobQueueModel;
    m_jobQueueModel = new JobQueueModel(this);
    SimulationRegistry registry;
    m_jobQueueModel->addJob("isgisaxs01",registry.createItem("isgisaxs01"));
    //m_jobQueueModel->addJob("isgisaxs02",registry.createItem("isgisaxs02"));
    m_jobQueueModel->addJob("isgisaxs04_1ddl",registry.createItem("isgisaxs04_1DDL"));
    m_jobQueueModel->addJob("isgisaxs04_2ddl",registry.createItem("isgisaxs04_2DDL"));
    m_jobQueueModel->addJob("isgisaxs11",registry.createItem("isgisaxs11"));
    m_jobQueueModel->addJob("LayerWithRoughness",registry.createItem("LayerWithRoughness"));
    //m_jobQueueModel->addJob("mesocrystal01",registry.createItem("mesocrystal01"));
}


void MainWindow::initInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    m_instrumentModel->setIconProvider(new IconProvider());

    ParameterizedItem *instrument1 = m_instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("Default GISAS");
    ParameterizedItem *detector1 = m_instrumentModel->insertNewItem(Constants::DetectorType, m_instrumentModel->indexOfItem(instrument1));
    ParameterizedItem *beam1 = m_instrumentModel->insertNewItem(Constants::BeamType, m_instrumentModel->indexOfItem(instrument1));
    Q_UNUSED(detector1);
    Q_UNUSED(beam1);

    //m_instrumentModel->save("instrument.xml");
}


void MainWindow::initSimModel()
{
    if (mp_sim_data_model) delete mp_sim_data_model;
    mp_sim_data_model = new SimulationDataModel;
}


void MainWindow::updateSimModel()
{
    Q_ASSERT(mp_sim_data_model);
    Q_ASSERT(m_sampleModel);
    Q_ASSERT(m_instrumentModel);
    qDebug() << " ";
    qDebug() << "MainWindow::updateSimModel()" << m_sampleModel->rowCount( QModelIndex() );
    mp_sim_data_model->clear();
    updateSamples();
    updateInstruments();
}


void MainWindow::updateSamples()
{
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < m_sampleModel->rowCount( parentIndex); ++i_row) {
         QModelIndex itemIndex = m_sampleModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_sampleModel->itemForIndex(itemIndex)){
             qDebug() << item->itemName() << item->modelType();
             if(item->modelType() == Constants::MultiLayerType) {
                 DomainObjectBuilder builder;
                 MultiLayer *multilayer = builder.buildMultiLayer(*item);
                 multilayer->printSampleTree();
                 if(multilayer) {
                     mp_sim_data_model->addSample(item->itemName(), multilayer);
                 }
             }
         }
    }
}


void MainWindow::updateInstruments()
{
    qDebug() << "MainWindow::updateInstruments()";
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < m_instrumentModel->rowCount( parentIndex); ++i_row) {
         QModelIndex itemIndex = m_instrumentModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_instrumentModel->itemForIndex(itemIndex)){
             qDebug() << "      MainWindow::updateInstruments()" << item->itemName() << item->modelType();
             if(item->modelType() == Constants::InstrumentType) {
                 DomainObjectBuilder builder;
                 Instrument *instrument = builder.buildInstrument(*item);
                 std::cout << *instrument << std::endl;
                 if(instrument) {
                     mp_sim_data_model->addInstrument(item->itemName(), instrument);
                 }
             }
         }
    }
}


void MainWindow::testGUIObjectBuilder()
{
    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> sample(factory.createSample("isgisaxs01"));

    sample->printSampleTree();

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sampleModel, sample.get());
}

