#include "SimulationView.h"

#include "SimulationDataModel.h"
#include "Simulation.h"
#include "mainwindow.h"
#include "PythonScriptSampleBuilder.h"
#include "JobQueueModel.h"
#include "JobItem.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QtCore>
#include <QMenu>

SimulationView::SimulationView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
    , m_jobQueueModel(0)
{
    // selection of input parameters
    QGroupBox *inputDataGroup = new QGroupBox(tr("Data selection"));
      // instrument selection
    QLabel *instrumentSelectionLabel = new QLabel(tr("Select Instrument:"));
    instrumentSelectionBox = new QComboBox;
      // sample selection
    QLabel *sampleSelectionLabel = new QLabel(tr("Select Sample:"));
    sampleSelectionBox = new QComboBox;
      // layout
    QGridLayout *dataSelectionLayout = new QGridLayout;
    dataSelectionLayout->addWidget(instrumentSelectionLabel, 0, 0);
    dataSelectionLayout->addWidget(instrumentSelectionBox, 0, 1);
    dataSelectionLayout->addWidget(sampleSelectionLabel, 1, 0);
    dataSelectionLayout->addWidget(sampleSelectionBox, 1, 1);
    inputDataGroup->setLayout(dataSelectionLayout);
    updateViewElements();

    // selection of simulation parameters
    QGroupBox *simulationParametersGroup = new QGroupBox(tr("Simulation Parameters"));
       // framework (DWBA - BA)
    QLabel *frameworkLabel = new QLabel(tr("Framework:"));
    QComboBox *frameworkSelectionBox = new QComboBox;
    frameworkSelectionBox->addItem(tr("DWBA"));
    frameworkSelectionBox->addItem(tr("BA"));
      // interference function (DA - LMA - SSCA - ISGISAXSMOR)
    QLabel *interferenceLabel = new QLabel(tr("Interference Function Approximation:"));
    QComboBox *interferenceFunctionSelectionBox = new QComboBox;
    interferenceFunctionSelectionBox->addItem(tr("DA"));
    interferenceFunctionSelectionBox->addItem(tr("LMA"));
    interferenceFunctionSelectionBox->addItem(tr("SSCA"));
      // lattice type (None - Lattice - Para1D - Para1DFinite)
    QLabel *latticeTypeLabel = new QLabel(tr("Lattice Type:"));
    QComboBox *latticeTypeSelectionBox = new QComboBox;
    latticeTypeSelectionBox->addItem(tr("None"));
    latticeTypeSelectionBox->addItem(tr("Lattice"));
    latticeTypeSelectionBox->addItem(tr("Para1D"));
    latticeTypeSelectionBox->addItem(tr("Para1DFinite"));
    // run policy
    QLabel *runPolicyLabel = new QLabel(tr("Run Policy:"));
    runPolicySelectionBox = new QComboBox;
    runPolicySelectionBox->addItem(tr("Immediately"));
    runPolicySelectionBox->addItem(tr("In background"));
    runPolicySelectionBox->addItem(tr("Submit only"));
    runPolicySelectionBox->addItem(tr("Real time"));

      // layout
    QGridLayout *simulationParametersLayout = new QGridLayout;
    simulationParametersLayout->addWidget(frameworkLabel, 0, 0);
    simulationParametersLayout->addWidget(frameworkSelectionBox, 0, 1);
    simulationParametersLayout->addWidget(interferenceLabel, 1, 0);
    simulationParametersLayout->addWidget(interferenceFunctionSelectionBox, 1, 1);
    simulationParametersLayout->addWidget(latticeTypeLabel, 2, 0);
    simulationParametersLayout->addWidget(latticeTypeSelectionBox, 2, 1);
    simulationParametersLayout->addWidget(runPolicyLabel, 3, 0);
    simulationParametersLayout->addWidget(runPolicySelectionBox, 3, 1);
    simulationParametersGroup->setLayout(simulationParametersLayout);

    QHBoxLayout *simButtonLayout = new QHBoxLayout;
    // run simulation button
    runSimulationButton = new QPushButton(tr("Run Simulation"));
    runSimulationButton->setIcon(QIcon(":/images/main_simulation.png"));
    runSimulationButton->setMinimumWidth(100);
    runSimulationButton->setMinimumHeight(50);

    simButtonLayout->addStretch();
    simButtonLayout->addWidget(runSimulationButton);
    simButtonLayout->addStretch();


    // run simulation with python script sample builder
    //runPyScriptSimulation = new QPushButton(tr("Run Simulation with Python Sample"));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputDataGroup);
    mainLayout->addWidget(simulationParametersGroup);
    //mainLayout->addWidget(runSimulationButton);
    //mainLayout->addWidget(runPyScriptSimulation);
    mainLayout->addLayout(simButtonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    //connect(runPyScriptSimulation, SIGNAL(clicked()), this, SLOT(onPythonJobLaunched()));
}


void SimulationView::setJobQueueModel(JobQueueModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
    }
}


void SimulationView::updateViewElements()
{
    instrumentSelectionBox->clear();
    if(mp_simulation_data_model->getInstrumentList().isEmpty()) {
        instrumentSelectionBox->addItem("No instrument defined yet");
        instrumentSelectionBox->setEnabled(false);
    } else {
        instrumentSelectionBox->setEnabled(true);
        instrumentSelectionBox->addItems(mp_simulation_data_model->getInstrumentList().keys());
    }

    sampleSelectionBox->clear();
    if(mp_simulation_data_model->getSampleList().isEmpty()) {
        sampleSelectionBox->addItem("No sample to simulate yet");
        sampleSelectionBox->setEnabled(false);
    } else {
        sampleSelectionBox->setEnabled(true);
        sampleSelectionBox->addItems(mp_simulation_data_model->getSampleList().keys());
    }
}

void SimulationView::onRunSimulation()
{
    qDebug() << "SimulationView::onRunSimulation()";
    Instrument *p_instrument = mp_simulation_data_model->getInstrumentList().value(
                instrumentSelectionBox->currentText(), 0);
    if (!p_instrument) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }
    ISample *p_sample = mp_simulation_data_model->getSampleList().value(
                sampleSelectionBox->currentText(), 0);
    if (!p_sample) {
        QMessageBox::warning(this, tr("No Sample Selected"),
                             tr("You must select a sample first."));
        return;
    }
    Simulation *p_sim = new Simulation;
    p_sim->setSample(*p_sample);
    p_sim->setInstrument(*p_instrument);

    if(runPolicySelectionBox->currentText() == "Immediately") {
        m_jobQueueModel->addJob(p_sample->getName().c_str(), p_sim, JobItem::RunImmediately);
    } else if(runPolicySelectionBox->currentText() == "In background") {
        m_jobQueueModel->addJob(p_sample->getName().c_str(), p_sim, JobItem::RunInBackground);
    } else if(runPolicySelectionBox->currentText() == "Submit only") {
        m_jobQueueModel->addJob(p_sample->getName().c_str(), p_sim, JobItem::SubmitOnly);
    } else {
        m_jobQueueModel->addJob(p_sample->getName().c_str(), p_sim, JobItem::SubmitOnly);
    }
}

void SimulationView::onPythonJobLaunched()
{
    Instrument *p_instrument = mp_simulation_data_model->getInstrumentList().value(
                instrumentSelectionBox->currentText(), 0);
    if (!p_instrument) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }
    QString file_name = QFileDialog::getOpenFileName(this, tr("Select Python Script"),
                            QDir::homePath(), tr("Python scripts (*.py)"),
                            0, QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);
    if (file_name.isNull()) {
        return;
    }
    PythonScriptSampleBuilder builder(file_name);
    ISample *p_sample = builder.buildSample();
    Simulation *p_sim = new Simulation;
    p_sim->setSample(*p_sample);
    p_sim->setInstrument(*p_instrument);

    QString identifier = m_jobQueueModel->addJob("PythonScript", p_sim);
    m_jobQueueModel->runJob(identifier);
}

void SimulationView::onJobFinished()
{
    QMessageBox::information(this, tr("Simulation Job Finished"),
                             tr("A simulation job has finished."));
}

