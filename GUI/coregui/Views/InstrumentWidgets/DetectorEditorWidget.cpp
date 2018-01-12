// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorEditorWidget.cpp
//! @brief     Implements class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DetectorEditorWidget.h"
#include "ComponentEditor.h"
#include "DetectorItems.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"
#include "ExtendedDetectorDialog.h"
#include "GUIHelpers.h"
#include "GroupInfoBox.h"
#include "RectangularDetectorWidget.h"
#include "SphericalDetectorWidget.h"
#include "InstrumentItems.h"
#include "GroupItem.h"
#include "ColumnResizer.h"
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

DetectorEditorWidget::DetectorEditorWidget(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(columnResizer)
    , m_detectorTypeEditor(new ComponentEditor(ComponentEditor::PlainWidget
                                               | ComponentEditor::W_NoChildren))
    , m_groupBox(new GroupInfoBox("Detector Parameters"))
    , m_currentDetector(nullptr)
    , m_subDetectorWidget(nullptr)
{
    QVBoxLayout* groupLayout = new QVBoxLayout;
    m_groupBox->setButtonToolTip("Gives access to the detector mask editor");
    m_groupBox->setLayout(groupLayout);
    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(onGroupBoxExtendedButton()));

    groupLayout->addWidget(m_detectorTypeEditor);

    // main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void DetectorEditorWidget::onGroupBoxExtendedButton()
{
    emit extendedDetectorEditorRequest(instrumentItem()->detectorItem());
}

void DetectorEditorWidget::subscribeToItem()
{

    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == GISASInstrumentItem::P_DETECTOR)
                init_SubDetector_Widget();
        }, this);

    m_detectorTypeEditor->clearEditor();
    m_detectorTypeEditor->setItem(instrumentItem()->detectorGroup());

    init_SubDetector_Widget();
}

void DetectorEditorWidget::unsubscribeFromItem()
{
    m_currentDetector = nullptr;
    remove_SubDetectorWidget();
    m_detectorTypeEditor->clearEditor();
}

void DetectorEditorWidget::init_SubDetector_Widget()
{
    if (m_currentDetector == instrumentItem()->detectorItem())
        return;

    m_currentDetector = instrumentItem()->detectorItem();

    remove_SubDetectorWidget();

    if (m_currentDetector->modelType() == Constants::SphericalDetectorType) {
        m_subDetectorWidget = new SphericalDetectorWidget(m_columnResizer, m_currentDetector);
    } else if (m_currentDetector->modelType() == Constants::RectangularDetectorType) {
        m_subDetectorWidget = new RectangularDetectorWidget(
            m_columnResizer, dynamic_cast<RectangularDetectorItem*>(m_currentDetector));
    } else {
        throw GUIHelpers::Error("DetectorEditorWidget::init_SubDetector_Widget() -> Error!"
                                "Unknown sybdetector type.");
    }

    m_groupBox->layout()->addWidget(m_subDetectorWidget);
}

void DetectorEditorWidget::remove_SubDetectorWidget()
{
    if (m_subDetectorWidget)
        m_groupBox->layout()->removeWidget(m_subDetectorWidget);

    delete m_subDetectorWidget;
    m_subDetectorWidget = 0;
}

GISASInstrumentItem* DetectorEditorWidget::instrumentItem()
{
    return dynamic_cast<GISASInstrumentItem*>(currentItem());
}
