// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/DetectorEditorWidget.cpp
//! @brief     Implements class DetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorEditorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include "GroupBox.h"
#include "ExtendedDetectorDialog.h"
#include <QGroupBox>
#include <QVBoxLayout>

DetectorEditorWidget::DetectorEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_groupBox(new GroupBox("Detector Parameters"))
    , m_detectorTypeEditor(0)
    , m_phiAxisEditor(0)
    , m_alphaAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_gridLayout(0)
    , m_detectorItem(0)
{
//    QGroupBox *groupBox = new QGroupBox("Detector Parameters");
    QVBoxLayout *groupLayout = new QVBoxLayout;
    m_groupBox->setButtonToolTip("Gives access to the detector mask editor");
    m_groupBox->setLayout(groupLayout);
    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(onGroupBoxExtendedButton()));

    // whole content is represented as grid layout
    m_gridLayout = new QGridLayout;

    m_detectorTypeEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_detectorTypeEditor, 0, 0);
    m_phiAxisEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_phiAxisEditor, 1, 0);
    m_alphaAxisEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_alphaAxisEditor, 1, 1);

    m_resolutionFunctionEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    groupLayout->addLayout(m_gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void DetectorEditorWidget::setDetectorItem(DetectorItem *detectorItem)
{
    m_detectorItem = detectorItem;
    m_detectorTypeEditor->clearEditor();
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();

    if (!m_detectorItem)
        return;

    SphericalDetectorItem *subDetector = dynamic_cast<SphericalDetectorItem *>(
        detectorItem->getSubItems()[DetectorItem::P_DETECTOR]);

    m_detectorTypeEditor->addItemProperty(detectorItem, DetectorItem::P_DETECTOR, QString(),
                                     AwesomePropertyEditor::SKIP);

    ParameterizedItem *phiAxisItem = subDetector->getSubItems()[SphericalDetectorItem::P_PHI_AXIS];
    m_phiAxisEditor->addItemProperties(phiAxisItem, QString("Phi axis"),
                                       AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *alphaAxisItem
        = subDetector->getSubItems()[SphericalDetectorItem::P_ALPHA_AXIS];
    m_alphaAxisEditor->addItemProperties(alphaAxisItem, QString("Alpha axis"),
                                         AwesomePropertyEditor::INSERT_AFTER);

    m_resolutionFunctionEditor->addItemProperty(
        subDetector, SphericalDetectorItem::P_RESOLUTION_FUNCTION, "Resolution function",
                AwesomePropertyEditor::INSERT_AFTER);
}

void DetectorEditorWidget::onGroupBoxExtendedButton()
{
    emit extendedDetectorEditorRequest(m_detectorItem);
}

