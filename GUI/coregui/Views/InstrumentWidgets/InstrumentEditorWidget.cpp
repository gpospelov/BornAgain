// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentEditorWidget.cpp
//! @brief     Implements class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentEditorWidget.h"
#include "ParameterizedItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "DetectorEditorWidget.h"
#include "BeamEditorWidget.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>


InstrumentEditorWidget::InstrumentEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_nameLineEdit(new QLineEdit())
    , m_typeComboBox(new QComboBox())
    , m_beamWidget(new BeamEditorWidget(this))
    , m_detectorWidget(new DetectorEditorWidget(this))
    , m_currentItem(0)
    , m_block_signals(false)
{

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_typeComboBox->setMinimumWidth(300);
    m_typeComboBox->addItem("Default GISAS Instrument");

    QHBoxLayout *topLayout = new QHBoxLayout;
    QGridLayout *nameAndTypeLayout = new QGridLayout;
    nameAndTypeLayout->addWidget(new QLabel("Name"), 0, 0);
    nameAndTypeLayout->addWidget(m_nameLineEdit, 0, 1);
    nameAndTypeLayout->addWidget(new QLabel("Type"), 1, 0);
    nameAndTypeLayout->addWidget(m_typeComboBox, 1, 1);
    topLayout->addLayout(nameAndTypeLayout );
    topLayout->addStretch(1);

    QGroupBox *instrumentGroup = new QGroupBox(tr("Instrument Parameters"));
    QVBoxLayout *instrumentGroupLayout = new QVBoxLayout;
    instrumentGroupLayout->addLayout(topLayout);
    instrumentGroupLayout->addWidget(m_beamWidget);
    instrumentGroupLayout->addWidget(m_detectorWidget);
    instrumentGroup->setLayout(instrumentGroupLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instrumentGroup);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_nameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onChangedEditor(const QString &)));
}




void InstrumentEditorWidget::setInstrumentItem(ParameterizedItem *instrument)
{
    Q_ASSERT(instrument);

    if(instrument != m_currentItem) {
        if(m_currentItem) {
            disconnect(m_currentItem, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
            disconnect(m_currentItem, SIGNAL(propertyItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        }

        m_currentItem = instrument;

        connect(m_currentItem, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        connect(m_currentItem, SIGNAL(propertyItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));

        updateWidgets();
    }

    BeamItem *beamItem(0);
    DetectorItem *detectorItem(0);

    instrument->print();

    foreach(ParameterizedItem *item, instrument->childItems()) {
        qDebug() << "XXX " << item->modelType();
        item->print();
        if(item->modelType() == Constants::BeamType) {
            beamItem = dynamic_cast<BeamItem *>(item);
        }
        else if(item->modelType() == Constants::DetectorType) {
            detectorItem = dynamic_cast<DetectorItem *>(item);
        }
    }
    Q_ASSERT(beamItem);
    Q_ASSERT(detectorItem);

    m_beamWidget->initFromItem(beamItem);
    m_detectorWidget->initFromItem(detectorItem);
}


void InstrumentEditorWidget::onChangedEditor(const QString &)
{
    qDebug() << "InstrumentEditorWidget::onChangedEditor() ->";
    Q_ASSERT(m_currentItem);
    if(m_block_signals) return;
    qDebug() << "          InstrumentEditorWidget::onChangedEditor(): " << m_nameLineEdit->text();
    m_currentItem->setItemName(m_nameLineEdit->text());
}


void InstrumentEditorWidget::onPropertyChanged(const QString &)
{
    qDebug() << "InstrumentEditorWidget::onPropertyChanged() ->";
    updateWidgets();
}


void InstrumentEditorWidget::updateWidgets()
{
    qDebug() << "InstrumentEditorWidget::updateWidgets() ->";
    Q_ASSERT(m_currentItem);
    m_block_signals = true;
    m_nameLineEdit->setText(m_currentItem->itemName());
    m_block_signals = false;
}





