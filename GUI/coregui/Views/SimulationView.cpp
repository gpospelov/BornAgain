#include "SimulationView.h"

#include "SimulationDataModel.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

SimulationView::SimulationView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
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
      // layout
    QGridLayout *simulationParametersLayout = new QGridLayout;
    simulationParametersLayout->addWidget(frameworkLabel, 0, 0);
    simulationParametersLayout->addWidget(frameworkSelectionBox, 0, 1);
    simulationParametersLayout->addWidget(interferenceLabel, 1, 0);
    simulationParametersLayout->addWidget(interferenceFunctionSelectionBox, 1, 1);
    simulationParametersLayout->addWidget(latticeTypeLabel, 2, 0);
    simulationParametersLayout->addWidget(latticeTypeSelectionBox, 2, 1);
    simulationParametersGroup->setLayout(simulationParametersLayout);

    // run simulation button
    runSimulationButton = new QPushButton(tr("Run Simulation"));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputDataGroup);
    mainLayout->addWidget(simulationParametersGroup);
    mainLayout->addWidget(runSimulationButton);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
}

void SimulationView::updateViewElements()
{
    instrumentSelectionBox->clear();
    instrumentSelectionBox->addItems(mp_simulation_data_model->getInstrumentList().keys());
    sampleSelectionBox->clear();
    sampleSelectionBox->addItems(mp_simulation_data_model->getSampleList().keys());
}

void SimulationView::onRunSimulation()
{
    // initialize a Simulation object and run it
    QMessageBox::information(this, tr("Pushed \"Run Simulation\"-button"),
                             tr("You pushed a button."));
}
