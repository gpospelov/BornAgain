// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.cpp
//! @brief     Implements class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentEditorWidget.h"
#include "InstrumentItems.h"
#include "AdjustingScrollArea.h"
#include "DetectorItems.h"
#include "InstrumentPresenter.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>

InstrumentEditorWidget::InstrumentEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_nameLineEdit(new QLineEdit)
    , m_instrumentPresenter(new InstrumentPresenter)
    , m_currentItem(nullptr)
    , m_block_signals(false)
{

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // main group box with all instrument parameters
    QGroupBox* instrumentGroup = new QGroupBox("Instrument Parameters");
    QVBoxLayout* instrumentGroupLayout = new QVBoxLayout;
    instrumentGroupLayout->setContentsMargins(0, 0, 0, 0);
    instrumentGroup->setLayout(instrumentGroupLayout);
    instrumentGroupLayout->addSpacing(10);
    instrumentGroupLayout->addLayout(create_NameAndTypeLayout());

    AdjustingScrollArea* area = new AdjustingScrollArea;
    area->setWidget(m_instrumentPresenter);
    instrumentGroupLayout->addWidget(area, 1);
    instrumentGroupLayout->addStretch();

    // setting main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instrumentGroup);
    setLayout(mainLayout);

    connect(m_nameLineEdit, &QLineEdit::textChanged,
            this, &InstrumentEditorWidget::onChangedEditor);

//    connect(m_instrumentComponents, &GISASInstrumentEditor::extendedDetectorEditorRequest,
//            this, &InstrumentEditorWidget::extendedDetectorEditorRequest);

}

QSize InstrumentEditorWidget::sizeHint() const
{
    return QSize(600, 600);
}

void InstrumentEditorWidget::setItem(SessionItem* instrument)
{
    m_currentItem = instrument;
    updateWidgets();

    m_instrumentPresenter->setItem(instrument);
}

void InstrumentEditorWidget::onChangedEditor(const QString&)
{
    if (m_block_signals)
        return;

    if (m_currentItem)
        m_currentItem->setItemName(m_nameLineEdit->text());
}

//! top block with instrument name and type
QLayout* InstrumentEditorWidget::create_NameAndTypeLayout()
{
    QHBoxLayout* result = new QHBoxLayout;

    m_nameLineEdit->setMinimumWidth(200);

    result->addSpacing(17);
    result->addWidget(new QLabel("Name"));
    result->addWidget(m_nameLineEdit);
    result->addStretch(1);

    return result;
}

void InstrumentEditorWidget::updateWidgets()
{
    m_block_signals = true;

    if (m_currentItem) {
        m_nameLineEdit->setEnabled(true);
        m_nameLineEdit->setText(m_currentItem->itemName());
    } else {
        m_nameLineEdit->setText(QString());
        m_nameLineEdit->setEnabled(false);
    }

    m_block_signals = false;
}
