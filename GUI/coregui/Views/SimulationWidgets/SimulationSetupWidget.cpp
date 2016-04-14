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
    , exportToPyScriptButton(0)
    , m_simOptionsWidget(0)
{
    m_simOptionsWidget = new SimulationOptionsWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(createDataSelectorWidget());
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
    const MultiLayerItem *jobMultiLayerItem = getSelectedMultiLayerItem();
    const InstrumentItem *jobInstrumentItem = getSelectedInstrumentItem();

    if(!isValidSetup(jobMultiLayerItem, jobInstrumentItem))
        return;

    JobItem *jobItem = m_applicationModels->jobModel()->addJob(
                jobMultiLayerItem,
                jobInstrumentItem,
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
    const MultiLayerItem *jobMultiLayerItem = getSelectedMultiLayerItem();
    const InstrumentItem *jobInstrumentItem = getSelectedInstrumentItem();

    if(!isValidSetup(jobMultiLayerItem, jobInstrumentItem))
        return;

    PythonScriptWidget *pythonWidget = new PythonScriptWidget(this);
    pythonWidget->show();
    pythonWidget->raise();
    pythonWidget->generatePythonScript(jobMultiLayerItem, jobInstrumentItem,
            m_applicationModels->documentModel()->getSimulationOptionsItem(),
                                       m_projectManager->getProjectDir());
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

//! returns true, if there are sample/instruments selected. and they are suitable for simulation
bool SimulationSetupWidget::isValidSetup(const MultiLayerItem *multiLayerItem,
                                         const InstrumentItem *instrumentItem)
{
    if (!multiLayerItem) {
        QMessageBox::warning(this, tr("No Sample Selected"), tr("You must select a sample first."));
        return false;
    }

    SampleValidator sampleValidator;
    if (!sampleValidator.isValidMultiLayer(multiLayerItem)) {
        QMessageBox::warning(this, tr("Not suitable MultiLayer"),
                             sampleValidator.getValidationMessage());
        return false;
    }

    if (!instrumentItem) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return false;
    }

    return true;
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
