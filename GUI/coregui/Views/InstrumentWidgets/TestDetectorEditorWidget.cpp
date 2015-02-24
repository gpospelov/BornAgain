// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestDetectorEditorWidget.cpp
//! @brief     Implements class TestDetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestDetectorEditorWidget.h"
#include "AwesomePropertyEditor.h"
#include "DetectorItems.h"
#include <QGroupBox>
#include <QVBoxLayout>

TestDetectorEditorWidget::TestDetectorEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_phiAxisEditor(0)
    , m_alphaAxisEditor(0)
    , m_detectorItem(0)
{
    QGroupBox *groupBox = new QGroupBox("Detector Parameters");
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    QGridLayout *gridLayout = new QGridLayout;

    m_phiAxisEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_phiAxisEditor, 0, 0);
    m_alphaAxisEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_alphaAxisEditor, 0, 1);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);

}

void TestDetectorEditorWidget::setDetectorItem(TestDetectorItem *detectorItem)
{
    m_detectorItem = detectorItem;
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();

    if(!m_detectorItem) return;

    ParameterizedItem *phiAxisItem = m_detectorItem->getSubItems()[TestDetectorItem::P_PHI_AXIS];
    m_phiAxisEditor->addItemProperties(phiAxisItem, QString("Phi axis"), AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *alphaAxisItem = m_detectorItem->getSubItems()[TestDetectorItem::P_ALPHA_AXIS];
    m_alphaAxisEditor->addItemProperties(alphaAxisItem, QString("Alpha axis"), AwesomePropertyEditor::INSERT_AFTER);

}



