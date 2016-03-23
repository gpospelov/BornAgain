// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitSettingsWidget.h
//! @brief     Defines class FitSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitSettingsWidget.h"
#include "FitParameterWidget.h"
#include "FitModel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>


FitSettingsWidget::FitSettingsWidget(FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_fitModel(fitModel)
    , m_fitParameter(new FitParameterWidget(m_fitModel, this))
    , m_sampleCombo(new QComboBox())
    , m_instrumentCombo(new QComboBox())
{
    m_sampleCombo->setMinimumWidth(200);
    m_instrumentCombo->setMinimumWidth(200);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(new QLabel("Select Sample:"));
    topLayout->addWidget(m_sampleCombo);
    topLayout->addSpacing(30);
    topLayout->addWidget(new QLabel("Select Instrument:"));
    topLayout->addWidget(m_instrumentCombo);
    topLayout->addStretch();
    QWidget *topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    topWidget->setContentsMargins(0,0,0,0);
    topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(m_fitParameter);
    m_fitParameter->setSizePolicy(QSizePolicy::MinimumExpanding,
                                  QSizePolicy::MinimumExpanding);
    connectCombos();
    setLayout(mainLayout);
}

void FitSettingsWidget::showEvent(QShowEvent *)
{
    onUpdateGUI();
}

void FitSettingsWidget::onUpdateGUI()
{
    m_fitParameter->updateSelector();

    disconnectCombos();
    m_sampleCombo->clear();
    m_instrumentCombo->clear();

    foreach (QString v, m_fitModel->getSampleNames()) {
        m_sampleCombo->addItem(m_fitModel->getSampleItemNameForDisplayName(v),
                               v);
    }

    foreach (QString v, m_fitModel->getInstrumentNames()) {
        m_instrumentCombo->addItem(m_fitModel->getInstrumentItemNameForDisplayName(v),
                                   v);
    }
    m_sampleCombo->setCurrentIndex(-1);
    m_instrumentCombo->setCurrentIndex(-1);
    connectCombos();

    m_instrumentCombo->setCurrentIndex(m_instrumentCombo->findData
                                      (m_fitModel->getSelectedInstrumentName()));
    m_sampleCombo->setCurrentIndex(m_sampleCombo->findData(m_fitModel->getSelectedSampleName()));
}

void FitSettingsWidget::onSampleChanged(int index)
{
    QString data = m_sampleCombo->itemData(index).toString();
    if (data != m_fitModel->getSelectedSampleName()) {
        m_fitModel->setSelectedSample(data);
        m_fitParameter->updateSelector();
        // when sample changed, discard all fit parameters
        m_fitParameter->clearParameter();
    }
}

void FitSettingsWidget::onInstrumentChanged(int index)
{
    QString data = m_instrumentCombo->itemData(index).toString();
    if (data != m_fitModel->getSelectedInstrumentName()) {
        m_fitModel->setSelectedInstrument(data);
        m_fitParameter->updateSelector();
        // when sample changed, discard all fit parameters
        m_fitParameter->clearParameter();
    }
}

void FitSettingsWidget::connectCombos() {
    connect(m_sampleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onSampleChanged(int)));
    connect(m_instrumentCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInstrumentChanged(int)));
}

void FitSettingsWidget::disconnectCombos() {
    disconnect(m_sampleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onSampleChanged(int)));
    disconnect(m_instrumentCombo, SIGNAL(currentIndexChanged(int)),
               this, SLOT(onInstrumentChanged(int)));
}
