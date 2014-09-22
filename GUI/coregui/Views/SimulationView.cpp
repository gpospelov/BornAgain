#include "SimulationView.h"
#include "SimulationSetupWidget.h"
#include "QuickSimulationWidget.h"
#include "SimulationToolBar.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "JobQueueModel.h"
#include "qdebug.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>


SimulationView::SimulationView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_jobQueueModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    m_jobQueueModel = mainWindow->getJobQueueModel();
    m_sampleModel = mainWindow->getSampleModel();
    m_instrumentModel = mainWindow->getInstrumentModel();
    Q_ASSERT(m_sampleModel);
    Q_ASSERT(m_instrumentModel);

    m_simulationSetupWidget = new SimulationSetupWidget();
    m_simulationSetupWidget->setJobQueueModel(m_jobQueueModel);
    m_simulationSetupWidget->setSampleModel(m_sampleModel);
    m_simulationSetupWidget->setInstrumentModel(m_instrumentModel);

    m_quickSimulationWidget = new QuickSimulationWidget(m_sampleModel, m_instrumentModel);

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(SimulationSetupTab, m_simulationSetupWidget, tr("Simulation Params"));
    m_tabWidget->insertTab(QuickSimulationTab, m_quickSimulationWidget, tr("Quick Simulation"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));

    m_toolBar = new SimulationToolBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}


void SimulationView::updateSimulationViewElements()
{
    qDebug() << "SimulationView::updateSimulationViewElements()" << m_sampleModel << m_instrumentModel;
    m_simulationSetupWidget->updateViewElements();
}

void SimulationView::onChangeTabWidget(int index)
{
    if(index == SimulationSetupTab)
    {
        //m_simulationSetupWidget->updateViewElements();
    }
    else if(index == QuickSimulationTab)
    {
        m_quickSimulationWidget->updateViews(m_simulationSetupWidget->getInstrumentSelection(), m_simulationSetupWidget->getSampleSelection());
    }
}
