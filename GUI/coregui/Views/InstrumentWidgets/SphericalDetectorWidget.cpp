// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/SphericalDetectorWidget.cpp
//! @brief     Implements class SphericalDetectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SphericalDetectorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include "GroupBox.h"
#include "ExtendedDetectorDialog.h"
#include <QGroupBox>
#include <QVBoxLayout>

SphericalDetectorWidget::SphericalDetectorWidget(QWidget *parent)
    : QWidget(parent)
    , m_phiAxisEditor(0)
    , m_alphaAxisEditor(0)
    , m_resolutionFunctionEditor(0)
    , m_gridLayout(new QGridLayout)
    , m_detectorItem(0)
{
    m_phiAxisEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_phiAxisEditor, 0, 0);
    m_alphaAxisEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_alphaAxisEditor, 0, 1);

    m_resolutionFunctionEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 0, 2);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void SphericalDetectorWidget::setDetectorItem(SphericalDetectorItem *detectorItem)
{
    m_detectorItem = detectorItem;
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();

    if (!m_detectorItem)
        return;


    ParameterizedItem *phiAxisItem = m_detectorItem->getSubItems()[SphericalDetectorItem::P_PHI_AXIS];
    m_phiAxisEditor->addItemProperties(phiAxisItem, QString("Phi axis"),
                                       AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *alphaAxisItem
        = m_detectorItem->getSubItems()[SphericalDetectorItem::P_ALPHA_AXIS];
    m_alphaAxisEditor->addItemProperties(alphaAxisItem, QString("Alpha axis"),
                                         AwesomePropertyEditor::INSERT_AFTER);

    m_resolutionFunctionEditor->addItemProperty(
        m_detectorItem, SphericalDetectorItem::P_RESOLUTION_FUNCTION, "Resolution function",
                AwesomePropertyEditor::INSERT_AFTER);
}


