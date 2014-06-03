#include "mainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "actionmanager.h"
#include "WelcomeView.h"
#include "SampleView.h"
#include "PyScriptView.h"
#include "InstrumentView.h"
#include "SimulationView.h"
#include "FitView.h"
#include "JobQueueView.h"
#include "TestView.h"
#include "MaterialEditorWidget.h"
#include "stylehelper.h"
#include "SimulationDataModel.h"
#include "JobQueueModel.h"
#include "MaterialModel.h"
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

#include <QApplication>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(0)
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_scriptView(0)
    , m_simulationView(0)
    , m_fitView(0)
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
{
//    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
//    QCoreApplication::setApplicationVersion(QLatin1String(Constants::APPLICATION_VERSION));
//    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    // initialize material model first
    initMaterialModel();

    // initialize simulation data model first:
    initSimModel();

    initJobQueueModel();

    initSampleModel();

    initInstrumentModel();


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
    m_scriptView = new PyScriptView(mp_sim_data_model);
    m_simulationView = new SimulationView(mp_sim_data_model);
    m_simulationView->setJobQueueModel(m_jobQueueModel);
    m_fitView = new FitView();
    m_jobQueueView = new JobQueueView(m_jobQueueModel);

    m_tabWidget->insertTab(WelcomeTab, m_welcomeView, QIcon(":/images/main_home.png"), "Welcome");
    m_tabWidget->insertTab(InstrumentTab, m_instrumentView, QIcon(":/images/main_instrument.png"), "Instrument");
    m_tabWidget->insertTab(SampleTab, m_sampleView, QIcon(":/images/main_sample.png"), "Sample");
    //m_tabWidget->insertTab(3, m_scriptView, QIcon(":/images/mode_script.png"), "Python scripts");
    m_tabWidget->insertTab(SimulationTab, m_simulationView, QIcon(":/images/main_simulation.png"), "Simulation");
    //m_tabWidget->insertTab(6, m_fitView, QIcon(":/images/mode_fit.png"), "Fit");
    m_tabWidget->insertTab(JobTab, m_jobQueueView, QIcon(":/images/main_jobqueue.png"), "Jobs");

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

    //testGUIObjectBuilder();

}


MainWindow::~MainWindow()
{
    delete m_materialEditor;
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
        m_simulationView->updateViewElements();
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
    writeSettings();
    event->accept();
}


void MainWindow::initSimModel()
{
    if (mp_sim_data_model) delete mp_sim_data_model;
    mp_sim_data_model = new SimulationDataModel;
    //mp_sim_data_model->addInstrument(tr("Default GISAS"), createDefaultInstrument());
    //mp_sim_data_model->addSample(tr("Default cylinder single layer"), createDefaultSample());
}

//Instrument *MainWindow::createDefaultInstrument()
//{
//    Instrument *p_result = new Instrument;
//    p_result->setBeamParameters(0.1*Units::nanometer, 0.2*Units::degree, 0.0);
//    p_result->setBeamIntensity(1e7);
////    p_result->setDetectorParameters(100, -1.0*Units::degree, 1.0*Units::degree,
////                                    100, 0.0*Units::degree, 2.0*Units::degree);
//    p_result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
//                                    100, 0.0*Units::degree, 2.0*Units::degree, true);
//    return p_result;
//}


void MainWindow::initJobQueueModel()
{
    delete m_jobQueueModel;
    m_jobQueueModel = new JobQueueModel(this);
    SimulationRegistry registry;
    m_jobQueueModel->addJob("isgisaxs01",registry.createItem("isgisaxs01"));
    m_jobQueueModel->addJob("isgisaxs02",registry.createItem("isgisaxs02"));
    m_jobQueueModel->addJob("isgisaxs04_2ddl",registry.createItem("isgisaxs04_2DDL"));
    //m_jobQueueModel->addJob("mesocrystal01",registry.createItem("mesocrystal01"));
}


void MainWindow::initSampleModel()
{
    delete m_sampleModel;
    m_sampleModel = new SessionModel(SessionXML::SampleModelTag);

    //m_sampleModel->save("sample.xml");

//    ParameterizedItem *multilayer = m_sampleModel->insertNewItem("MultiLayer");
//    multilayer->setItemName("MultiLayer1");

//    ParameterizedItem *layer = m_sampleModel->insertNewItem("Layer", m_sampleModel->indexOfItem(multilayer));
//    layer->setMaterialProperty(MaterialEditor::getMaterialProperty("Air"));

//    ParameterizedItem *layout = m_sampleModel->insertNewItem("ParticleLayout",
//                   m_sampleModel->indexOfItem(layer));

//    ParameterizedItem *layout = m_sampleModel->insertNewItem("ParticleLayout");

//    ParameterizedItem *particle1 = m_sampleModel->insertNewItem("Particle", m_sampleModel->indexOfItem(layout));

//    ParameterizedItem *cylinder = particle1->getSubItems()[ParticleItem::P_FORM_FACTOR];
//    cylinder->setRegisteredProperty(CylinderItem::P_HEIGHT, 5.0);

//    m_sampleModel->moveParameterizedItem(particle1, 0);

//    ParameterizedItem *cylinder = particle1->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Cylinder");
//    particle1->setRegisteredProperty(ParticleItem::P_FORM_FACTOR, "Cylinder");
//    cylinder->setRegisteredProperty(CylinderItem::P_HEIGHT, 5.0);
//    particle1->setMaterialProperty(MaterialEditor::getMaterialProperty("Particle"));

//    ParameterizedItem *particle2 = m_sampleModel->insertNewItem("Particle", m_sampleModel->indexOfItem(layout));
//    particle2->setGroupProperty(ParticleItem::P_FORM_FACTOR, "Prism3");
//    particle2->setMaterialProperty(MaterialEditor::getMaterialProperty("Particle"));

//    ParameterizedItem *substrate = m_sampleModel->insertNewItem("Layer",
//                   m_sampleModel->indexOfItem(multilayer));
//    substrate->setMaterialProperty(MaterialEditor::getMaterialProperty("Substrate"));

}

void MainWindow::initInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new SessionModel(SessionXML::InstrumentModelTag);
    m_instrumentModel->setIconProvider(new IconProvider());

    ParameterizedItem *instrument1 = m_instrumentModel->insertNewItem("Instrument");
    instrument1->setItemName("Default GISAS");
    ParameterizedItem *detector1 = m_instrumentModel->insertNewItem("Detector", m_instrumentModel->indexOfItem(instrument1));
    ParameterizedItem *beam1 = m_instrumentModel->insertNewItem("Beam", m_instrumentModel->indexOfItem(instrument1));
    Q_UNUSED(detector1);
    Q_UNUSED(beam1);

//    ParameterizedItem *instrument2 = m_instrumentModel->insertNewItem("Instrument");
//    instrument2->setItemName("Instrument2");
//    ParameterizedItem *detector2 = m_instrumentModel->insertNewItem("Detector", m_instrumentModel->indexOfItem(instrument2));
//    ParameterizedItem *beam2 = m_instrumentModel->insertNewItem("Beam", m_instrumentModel->indexOfItem(instrument2));
    //    Q_UNUSED(detector2);
    //    Q_UNUSED(beam2);


    m_instrumentModel->save("instrument.xml");

}


void MainWindow::initMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
    m_materialModel->addMaterial("Default", MaterialItem::HomogeneousMaterial);

    MaterialItem *mAir = m_materialModel->addMaterial("Air", MaterialItem::HomogeneousMaterial);
    mAir->setRefractiveIndex(0,0);

    MaterialItem *mParticle = m_materialModel->addMaterial("Particle", MaterialItem::HomogeneousMaterial);
    mParticle->setRefractiveIndex(6e-4, 2e-8);

    MaterialItem *mSubstrate = m_materialModel->addMaterial("Substrate", MaterialItem::HomogeneousMaterial);
    mSubstrate->setRefractiveIndex(6e-6, 2e-8);

    m_materialEditor = new MaterialEditor(m_materialModel);
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
             if(item->modelType() == "MultiLayer") {
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
             if(item->modelType() == "Instrument") {
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

