// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationSetupWidget.cpp
//! @brief     Implements class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationSetupWidget.h"
#include "GISASSimulation.h"
#include "mainwindow.h"
#include "JobModel.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "JobItem.h"
#include "SampleValidator.h"
#include "Utils.h"
#include "PyGenTools.h"
#include "mainwindow_constants.h"
#include "PythonScriptWidget.h"
#include "IntensityDataIOFactory.h"
#include "IHistogram.h"
#include "IntensityDataItem.h"
#include "projectmanager.h"
#include "SimulationOptionsWidget.h"
#include "ApplicationModels.h"
#include "DocumentModel.h"
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
#include <DomainSimulationBuilder.h>

SimulationSetupWidget::SimulationSetupWidget(QWidget *parent)
    : QWidget(parent)
    , m_applicationModels(0)
    , m_projectManager(0)
    , instrumentSelectionBox(0)
    , sampleSelectionBox(0)
    , runSimulationButton(0)
    , selectRealData(0)
    , pathLabel(0)
    , runPolicySelectionBox(0)
    , cpuUsageSelectionBox(0)
    , exportToPyScriptButton(0)
    , m_simOptionsWidget(0)
{
    m_simOptionsWidget = new SimulationOptionsWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(createDataSelectorWidget());
    mainLayout->addWidget(createSimulationParametersWidget());
    mainLayout->addWidget(m_simOptionsWidget);
    mainLayout->addWidget(createButtonWidget());
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    connect(exportToPyScriptButton, SIGNAL(clicked()), this, SLOT(onExportToPythonScript()));
    connect(selectRealData, SIGNAL(clicked(bool)), this, SLOT(onOpenFile()));
}

void SimulationSetupWidget::setApplicationModels(ApplicationModels *model)
{
    Q_ASSERT(model);
    if(model != m_applicationModels) {
        m_applicationModels = model;
        updateViewElements();
    }
}

void SimulationSetupWidget::setProjectManager(ProjectManager *projectManager)
{
    m_projectManager = projectManager;
}

void SimulationSetupWidget::updateViewElements()
{
    updateSelectionBox(instrumentSelectionBox,
                       m_applicationModels->instrumentModel()->getInstrumentMap().keys());
    updateSelectionBox(sampleSelectionBox,
                       m_applicationModels->sampleModel()->getSampleMap().keys());

    m_simOptionsWidget->setItem(m_applicationModels->documentModel()->getSimulationOptionsItem());
}

QString SimulationSetupWidget::getSelectedInstrumentName() const
{
    return instrumentSelectionBox->currentText();
}

int SimulationSetupWidget::getSelectedInstrumentIndex() const
{
    return instrumentSelectionBox->currentIndex();
}

QString SimulationSetupWidget::getSelectedSampleName() const
{
    return sampleSelectionBox->currentText();
}

int SimulationSetupWidget::getSelectedSampleIndex() const
{
    return sampleSelectionBox->currentIndex();
}



void SimulationSetupWidget::onRunSimulation()
{
    InstrumentModel *jobInstrumentModel = getJobInstrumentModel();
    if (!jobInstrumentModel) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }

    SampleModel *jobSampleModel = getJobSampleModel();
    if (!jobSampleModel) {
        QMessageBox::warning(this, tr("No Sample Selected"), tr("You must select a sample first."));
        return;
    }

    SampleValidator sampleValidator;
    if (!sampleValidator.isValidSampleModel(jobSampleModel)) {
        QMessageBox::warning(this, tr("Not suitable MultiLayer"),
                             sampleValidator.getValidationMessage());
        return;
    }

//    JobItem *jobItem = m_applicationModels->jobModel()->addJob(getSelectedMultiLayerItem(), getSelectedInstrumentItem(),
//                       runPolicySelectionBox->currentText(), getNumberOfThreads());

    JobItem *jobItem = m_applicationModels->jobModel()->addJob(getSelectedMultiLayerItem(), getSelectedInstrumentItem(),
                       m_applicationModels->documentModel()->getSimulationOptionsItem());


    // load real data
    if (!pathLabel->text().isEmpty()) {
        try {
            IHistogram *data = IntensityDataIOFactory::readIntensityData(pathLabel->text().toStdString());
            dynamic_cast<IntensityDataItem*>(jobItem->getItem(JobItem::T_REALDATA))
                    ->setOutputData(data->createOutputData());
            jobItem->setItemValue(JobItem::P_WITH_FITTING, true);
        } catch (...) {
            QMessageBox::warning(this, "IO Problem", "Real data can not be loaded.");
        }
    }

    if (jobItem->runImmediately() || jobItem->runInBackground())
        m_applicationModels->jobModel()->runJob(jobItem->index());
}

void SimulationSetupWidget::onExportToPythonScript()
{
    InstrumentModel *instrumentModel = getJobInstrumentModel();
    if(!instrumentModel) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }

    SampleModel *sampleModel = getJobSampleModel();
    if(!sampleModel) {
        QMessageBox::warning(this, tr("No Sample Selected"),
                             tr("You must select a sample first."));
        return;
    }

    SampleValidator sampleValidator;
    if(!sampleValidator.isValidSampleModel(sampleModel)) {
        QMessageBox::warning(this, tr("Not suitable MultiLayer"),
                             sampleValidator.getValidationMessage());
        return;
    }

    PythonScriptWidget *pythonWidget = new PythonScriptWidget(this);
    pythonWidget->show();
    pythonWidget->raise();
    pythonWidget->generatePythonScript(sampleModel, instrumentModel, m_projectManager->getProjectDir());
}

void SimulationSetupWidget::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Intensity File"), "", tr("Intensity File (*.int *.tif *.tiff *.tif.gz);;Other (*)"));
    pathLabel->setText(fileName);
}

void SimulationSetupWidget::updateSelectionBox(QComboBox *comboBox, QStringList itemList)
{
    QString previousItem = comboBox->currentText();

    comboBox->clear();
    if(itemList.isEmpty()) {
        comboBox->setEnabled(false);
        comboBox->addItem("Not yet defined");
    } else {
        comboBox->setEnabled(true);
        qSort(itemList.begin(), itemList.end());
        comboBox->addItems(itemList);
        if(itemList.contains(previousItem))
            comboBox->setCurrentIndex(itemList.indexOf(previousItem));
    }
}

//! returns list with number of threads to select
QStringList SimulationSetupWidget::getCPUUsageOptions()
{
    QStringList result;
    int nthreads = Utils::System::getThreadHardwareConcurrency();
    for(int i = nthreads; i>0; i--){
        if(i == nthreads) {
            result.append(QString("Max (%1 threads)").arg(QString::number(i)));
        } else if(i == 1) {
            result.append(QString("%1 thread").arg(QString::number(i)));
        } else {
            result.append(QString("%1 threads").arg(QString::number(i)));
        }
    }
    return result;
}

int SimulationSetupWidget::getNumberOfThreads()
{
    foreach(QChar ch, cpuUsageSelectionBox->currentText()) {
        if(ch.isDigit()) return ch.digitValue();
    }
    return 0;
}

//! Returns copy of InstrumentModel containing a single instrument according to the text selection
InstrumentModel *SimulationSetupWidget::getJobInstrumentModel()
{
    InstrumentModel *result(0);
    QMap<QString, SessionItem *> instruments = m_applicationModels->instrumentModel()->getInstrumentMap();
    if(instruments[getSelectedInstrumentName()]) {
        int index = getSelectedInstrumentIndex();
        QMap<QString, SessionItem *>::iterator it = instruments.begin()+index;
        result = m_applicationModels->instrumentModel()->createCopy(it.value());
    }

    return result;
}

//! Returns copy of SampleModel containing a single MultiLayer according to the text selection
SampleModel *SimulationSetupWidget::getJobSampleModel()
{
    SampleModel *result(0);
    QMap<QString, SessionItem *> samples = m_applicationModels->sampleModel()->getSampleMap();
    if(samples[getSelectedSampleName()]) {
        int index = getSelectedSampleIndex();
        QMap<QString, SessionItem *>::iterator it = samples.begin()+index;
        result = m_applicationModels->sampleModel()->createCopy(it.value());
    }
    return result;
}

//! Returns selected MultiLayerItem taking into account that there might be several
//! multilayers with same name
const MultiLayerItem *SimulationSetupWidget::getSelectedMultiLayerItem() const
{
    const MultiLayerItem *result(0);
    QMap<QString, SessionItem *> samples = m_applicationModels->sampleModel()->getSampleMap();
    if(samples[getSelectedSampleName()]) {
        int index = getSelectedSampleIndex();
        QMap<QString, SessionItem *>::const_iterator it = samples.begin()+index;
        result = dynamic_cast<MultiLayerItem *>(it.value());
    }
    return result;
}

//! Returns selected InstrumentItem taking into account that there might be several
//! insturments with same name
const InstrumentItem *SimulationSetupWidget::getSelectedInstrumentItem() const
{
    const InstrumentItem *result(0);
    QMap<QString, SessionItem *> instruments =m_applicationModels->instrumentModel()->getInstrumentMap();
    if(instruments[getSelectedInstrumentName()]) {
        int index = getSelectedInstrumentIndex();
        QMap<QString, SessionItem *>::const_iterator it = instruments.begin()+index;
        result = dynamic_cast<InstrumentItem *>(it.value());
    }
    return result;

}

QWidget *SimulationSetupWidget::createDataSelectorWidget()
{
    // selection of input parameters
    QGroupBox *result = new QGroupBox(tr("Data selection"));

    // instrument selection
    QLabel *instrumentSelectionLabel = new QLabel(tr("Select Instrument:"));
    instrumentSelectionBox = new QComboBox;
    // sample selection
    QLabel *sampleSelectionLabel = new QLabel(tr("Select Sample:"));
    sampleSelectionBox = new QComboBox;
    // real data
    QLabel *readDataSelectionLabel = new QLabel(tr("Select Real Data:"));
    selectRealData = new QPushButton;
    selectRealData->setText("Load file ...");
    pathLabel = new QLabel(tr(""));
    QHBoxLayout *realDataSelection = new QHBoxLayout;
    realDataSelection->addWidget(selectRealData);
    realDataSelection->addWidget(pathLabel);
    // layout
    QGridLayout *dataSelectionLayout = new QGridLayout;
    dataSelectionLayout->addWidget(instrumentSelectionLabel, 0, 0);
    dataSelectionLayout->addWidget(instrumentSelectionBox, 0, 1);
    dataSelectionLayout->addWidget(sampleSelectionLabel, 1, 0);
    dataSelectionLayout->addWidget(sampleSelectionBox, 1, 1);
    dataSelectionLayout->addWidget(readDataSelectionLabel, 2, 0);
    dataSelectionLayout->addLayout(realDataSelection, 2, 1);
    result->setLayout(dataSelectionLayout);
    //updateViewElements();

    return result;
}

QWidget *SimulationSetupWidget::createSimulationParametersWidget()
{
    // selection of simulation parameters
    QGroupBox *result = new QGroupBox(tr("Simulation Parameters"));

    // run policy
    QLabel *runPolicyLabel = new QLabel(tr("Run Policy:"));
    runPolicyLabel->setToolTip("Defines run policy for the simulation");
    runPolicySelectionBox = new QComboBox;
    runPolicySelectionBox->setToolTip("Defines run policy for the simulation");
    runPolicySelectionBox->addItems(JobItem::getRunPolicies().keys());
    int index(0);
    foreach(QString descr, JobItem::getRunPolicies().values())
        runPolicySelectionBox->setItemData(index++, descr, Qt::ToolTipRole);

    // selection of number of threads
    QLabel *cpuUsageLabel = new QLabel(tr("CPU Usage:"));
    cpuUsageLabel->setToolTip("Defines number of threads to use for the simulation.");
    cpuUsageSelectionBox = new QComboBox;
    cpuUsageSelectionBox->setToolTip("Defines number of threads to use for the simulation.");
    cpuUsageSelectionBox->addItems(getCPUUsageOptions());
    cpuUsageSelectionBox->setEnabled(false);

    // layout
    QGridLayout *simulationParametersLayout = new QGridLayout;
    simulationParametersLayout->addWidget(runPolicyLabel, 0, 0);
    simulationParametersLayout->addWidget(runPolicySelectionBox, 0, 1);
    simulationParametersLayout->addWidget(cpuUsageLabel, 1, 0);
    simulationParametersLayout->addWidget(cpuUsageSelectionBox, 1, 1);

    result->setLayout(simulationParametersLayout);

    return result;
}

QWidget *SimulationSetupWidget::createButtonWidget()
{
    QWidget *result = new QWidget;

    QHBoxLayout *simButtonLayout = new QHBoxLayout;
    // run simulation button
    runSimulationButton = new QPushButton(tr("Run Simulation"));
    runSimulationButton->setIcon(QIcon(":/images/main_simulation.png"));
    runSimulationButton->setMinimumWidth(100);
    runSimulationButton->setMinimumHeight(50);
    runSimulationButton->setToolTip("Run the simulation using settings above.\n"
                                    " Global shortcut ctrl-r can be used to run from sample view.");
//    QPalette palette = runSimulationButton->palette();
//    palette.setColor(QPalette::Button, QColor(Constants::BUTTON_COLOR));
//    palette.setColor(QPalette::ButtonText, QColor(Constants::BUTTON_TEXT_COLOR));
//    runSimulationButton->setPalette(palette);

    // export simulation to a python script
    exportToPyScriptButton = new QPushButton(tr("Export to Python Script"));
    exportToPyScriptButton->setIcon(QIcon(":/images/mode_script.png"));
    exportToPyScriptButton->setMinimumWidth(100);
    exportToPyScriptButton->setMinimumHeight(50);
    exportToPyScriptButton->setToolTip("Export the simulation using settings above to "
                                       "a python script.\n");
//    exportToPyScriptButton->setPalette(palette);

    simButtonLayout->addStretch();
    simButtonLayout->addWidget(runSimulationButton);
    simButtonLayout->addWidget(exportToPyScriptButton);
    simButtonLayout->addStretch();

    result->setLayout(simButtonLayout);

    return result;
}
