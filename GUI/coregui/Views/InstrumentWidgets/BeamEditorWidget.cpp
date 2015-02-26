// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/BeamEditorWidget.cpp
//! @brief     Implements class BeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamEditorWidget.h"
#include "UniversalPropertyEditor.h"
#include "AwesomePropertyEditor.h"
#include "BeamItem.h"
#include "LayerItem.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>


BeamEditorWidget::BeamEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_intensityEditor(0)
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

    m_intensityEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_intensityEditor, 0, 0);

    m_wavelengthEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_wavelengthEditor, 1, 0);
    m_inclinationAngleEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_inclinationAngleEditor, 2, 0);
    m_azimuthalAngleEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    gridLayout->addWidget(m_azimuthalAngleEditor, 2, 1);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

void BeamEditorWidget::setBeamItem(BeamItem *beamItem)
{
    m_beamItem = beamItem;
    m_intensityEditor->clearEditor();
    m_wavelengthEditor->clearEditor();
    m_inclinationAngleEditor->clearEditor();
    m_azimuthalAngleEditor->clearEditor();

    if(!m_beamItem) return;

    m_intensityEditor->addItemProperty(m_beamItem, BeamItem::P_INTENSITY);

    ParameterizedItem *wavelengthItem = m_beamItem->getSubItems()[BeamItem::P_WAVELENGTH];
    m_wavelengthEditor->addItemProperties(wavelengthItem, QString("Wavelength"), AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *inclinationAngleItem = m_beamItem->getSubItems()[BeamItem::P_INCLINATION_ANGLE];
    m_inclinationAngleEditor->addItemProperties(inclinationAngleItem, QString("Inclination angle"), AwesomePropertyEditor::INSERT_AFTER);

    ParameterizedItem *azimuthalAngleItem = m_beamItem->getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE];
    m_azimuthalAngleEditor->addItemProperties(azimuthalAngleItem, QString("Azimuthal angle"), AwesomePropertyEditor::INSERT_AFTER);

}

