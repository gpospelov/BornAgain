// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSettingsWidget.h"
#include "FitModel.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "FitParameterWidget.h"
#include "FitParameterItems.h"
#include "SessionModel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

FitSettingsWidget::FitSettingsWidget(FitModel *fitModel, SampleModel *sampleModel,
                                     InstrumentModel *instrumentModel, QWidget *parent)
    : QWidget(parent)
    , m_fitModel(fitModel)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
    , m_fitParameter(0)
    , m_sampleCombo(new QComboBox())
    , m_instrumentCombo(new QComboBox())
{
    m_fitParameter = new FitParameterWidget(m_sampleModel, m_instrumentModel, m_fitModel, this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    m_sampleCombo->setMinimumWidth(200);
    m_instrumentCombo->setMinimumWidth(200);
    topLayout->addWidget(new QLabel("Select Sample:"));
    topLayout->addWidget(m_sampleCombo);
    topLayout->addSpacing(30);
    topLayout->addWidget(new QLabel("Select Instrument:"));
    topLayout->addWidget(m_instrumentCombo);
    topLayout->addStretch();
    QWidget *topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    topWidget->setContentsMargins(0,0,0,0);
    topWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(m_fitParameter);
    m_fitParameter->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    connect(m_sampleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onSampleChanged(int)));
    connect(m_instrumentCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onInstrumentChanged(int)));

    setLayout(mainLayout);
}

void FitSettingsWidget::showEvent(QShowEvent *)
{
    onUpdateGUI();
}

void FitSettingsWidget::onUpdateGUI()
{
    // we update the whole ui
    m_fitParameter->updateSelector();

    updateComboBox(m_sampleCombo, m_sampleModel, Constants::MultiLayerType,
                   FitSelectionItem::P_SAMPLE_INDEX);
    updateComboBox(m_instrumentCombo, m_instrumentModel, Constants::InstrumentType,
                   FitSelectionItem::P_INSTRUMENT_INDEX);
}

void FitSettingsWidget::updateComboBox(QComboBox *combo, SessionModel *model, const QString &type,
                                       const QString &selectionType)
{
    QString selectedSample = m_fitModel->itemForIndex(QModelIndex())
            ->getChildOfType(Constants::FitSelectionType)
            ->getRegisteredProperty(selectionType).toString();
    int curIndex = -1;
    combo->clear();
    for (int i_row = 0; i_row < model->rowCount(QModelIndex()); ++i_row) {
        QModelIndex itemIndex = model->index(i_row, 0, QModelIndex());
        if (ParameterizedItem *item = model->itemForIndex(itemIndex)) {
            if (item->modelType()  == type) {
                combo->addItem(item->itemName(), item->displayName());
                if (item->displayName() == selectedSample) {
                    curIndex = combo->count() - 1;
                }
            }
        }
    }
    if (curIndex >= 0)
        combo->setCurrentIndex(curIndex);
}

void FitSettingsWidget::onSampleChanged(int index)
{
    setFitSelection(m_sampleCombo, index, FitSelectionItem::P_SAMPLE_INDEX);
}

void FitSettingsWidget::onInstrumentChanged(int index)
{
    setFitSelection(m_instrumentCombo, index, FitSelectionItem::P_INSTRUMENT_INDEX);
}

void FitSettingsWidget::setFitSelection(QComboBox *combo, int index, const QString &prop)
{
    QVariant data = combo->itemData(index);
    if (index < 0)
        data = "";
    ParameterizedItem *selectionItem = m_fitModel->itemForIndex(QModelIndex())
            ->getChildOfType(Constants::FitSelectionType);
    if (selectionItem) {
        if (selectionItem->getRegisteredProperty(prop) != data) {
            selectionItem->setRegisteredProperty(prop, data);
            /*QModelIndex container = m_fitModel->indexOfItem(m_fitModel->itemForIndex(QModelIndex())
                                                ->getChildOfType(Constants::FitParameterContainerType));
            while (m_fitModel->rowCount(container) > 0) {
                m_fitModel->removeRow(0, container);
            }*/
            m_fitParameter->updateSelector();
        }
    }
}
