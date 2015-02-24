// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestBeamEditorWidget.cpp
//! @brief     Implements class TestBeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestBeamEditorWidget.h"
#include "UniversalPropertyEditor.h"
#include "AwesomePropertyEditor.h"
#include "BeamItem.h"
#include "LayerItem.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>


TestBeamEditorWidget::TestBeamEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_wavelengthEditor(0)
    , m_inclinationAngleEditor(0)
    , m_azimuthalAngleEditor(0)
    , m_beamItem(0)
{
    // group box layout
    QGroupBox *groupBox = new QGroupBox("Beam Parameters");
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    QGridLayout *gridLayout = new QGridLayout;

    m_wavelengthEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_wavelengthEditor, 0, 0);
    m_inclinationAngleEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_inclinationAngleEditor, 1, 0);
    m_azimuthalAngleEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_azimuthalAngleEditor, 1, 1);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

void TestBeamEditorWidget::setBeamItem(TestBeamItem *beamItem)
{
    m_beamItem = beamItem;
    m_wavelengthEditor->clearEditor();
    m_inclinationAngleEditor->clearEditor();

    if(!m_beamItem) return;

    ParameterizedItem *wavelengthItem = m_beamItem->getSubItems()[TestBeamItem::P_WAVELENGTH];
    m_wavelengthEditor->addItemProperties(wavelengthItem, QString("Wavelength"), AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *inclinationAngleItem = m_beamItem->getSubItems()[TestBeamItem::P_INCLINATION_ANGLE];
    m_inclinationAngleEditor->addItemProperties(inclinationAngleItem, QString("Inclination angle"), AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *azimuthalAngleItem = m_beamItem->getSubItems()[TestBeamItem::P_AZIMUTHAL_ANGLE];
    m_azimuthalAngleEditor->addItemProperties(azimuthalAngleItem, QString("Azimuthal angle"), AwesomePropertyEditor::INSERT_AFTER);

}

