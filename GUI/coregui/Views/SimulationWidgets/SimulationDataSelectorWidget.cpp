// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.cpp
//! @brief     Implements class SimulationDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationDataSelectorWidget.h"
#include "ApplicationModels.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "InstrumentItem.h"
#include "MultiLayerItem.h"
#include <QComboBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

SimulationDataSelectorWidget::SimulationDataSelectorWidget(QWidget *parent)
    : QWidget(parent)
    , instrumentSelectionBox(0)
    , sampleSelectionBox(0)
    , selectRealData(0)
    , pathLabel(0)
    , m_applicationModels(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // selection of input parameters
    QGroupBox *groupBox = new QGroupBox(tr("Data selection"));

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
    groupBox->setLayout(dataSelectionLayout);

    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);

    connect(selectRealData, SIGNAL(clicked(bool)), this, SLOT(onOpenFile()));
}

void SimulationDataSelectorWidget::setApplicationModels(ApplicationModels *applicationModels)
{
    m_applicationModels = applicationModels;
    updateViewElements();
}


QString SimulationDataSelectorWidget::getSelectedInstrumentName() const
{
    return instrumentSelectionBox->currentText();
}

int SimulationDataSelectorWidget::getSelectedInstrumentIndex() const
{
    return instrumentSelectionBox->currentIndex();
}

QString SimulationDataSelectorWidget::getSelectedSampleName() const
{
    return sampleSelectionBox->currentText();
}

int SimulationDataSelectorWidget::getSelectedSampleIndex() const
{
    return sampleSelectionBox->currentIndex();
}

void SimulationDataSelectorWidget::updateViewElements()
{
    Q_ASSERT(m_applicationModels);
    updateSelectionBox(instrumentSelectionBox,
                       m_applicationModels->instrumentModel()->getInstrumentMap().keys());
    updateSelectionBox(sampleSelectionBox,
                       m_applicationModels->sampleModel()->getSampleMap().keys());
}

//! Returns selected MultiLayerItem taking into account that there might be several
//! multilayers with same name

const MultiLayerItem *SimulationDataSelectorWidget::getSelectedMultiLayerItem() const
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

const InstrumentItem *SimulationDataSelectorWidget::getSelectedInstrumentItem() const
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

void SimulationDataSelectorWidget::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Intensity File"), "", tr("Intensity File (*.int *.tif *.tiff *.tif.gz);;Other (*)"));
    pathLabel->setText(fileName);
}

void SimulationDataSelectorWidget::updateSelectionBox(QComboBox *comboBox, QStringList itemList)
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
