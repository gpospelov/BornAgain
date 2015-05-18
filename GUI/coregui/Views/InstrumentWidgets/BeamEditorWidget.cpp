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
#include "AwesomePropertyPresenter.h"
#include "BeamItem.h"
#include "LayerItem.h"
#include "GroupBox.h"
#include "GUIHelpers.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include "DistributionDialog.h"

BeamEditorWidget::BeamEditorWidget(QWidget *parent)
    : QWidget(parent), m_intensityEditor(0), m_wavelengthPresenter(0),
      m_inclinationAnglePresenter(0), m_azimuthalAnglePresenter(0), m_gridLayout(0), m_beamItem(0)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QGroupBox *groupBox = new QGroupBox("Beam Parameters");

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    m_gridLayout = new QGridLayout;

    m_intensityEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_gridLayout->addWidget(m_intensityEditor, 0, 0);

    m_wavelengthPresenter = new AwesomePropertyPresenter("Wavelength [nm]", this);
    m_gridLayout->addWidget(m_wavelengthPresenter, 1, 0);
    connect(m_wavelengthPresenter, SIGNAL(onDialogRequest(ParameterizedItem *)), this,
            SLOT(onDialogRequest(ParameterizedItem *)));

    m_inclinationAnglePresenter = new AwesomePropertyPresenter("Inclination angle [deg]", this);
    m_gridLayout->addWidget(m_inclinationAnglePresenter, 1, 1);
    connect(m_inclinationAnglePresenter, SIGNAL(onDialogRequest(ParameterizedItem *)), this,
            SLOT(onDialogRequest(ParameterizedItem *)));

    m_azimuthalAnglePresenter = new AwesomePropertyPresenter("Azimuthal angle [deg]", this);
    m_gridLayout->addWidget(m_azimuthalAnglePresenter, 1, 2);
    connect(m_azimuthalAnglePresenter, SIGNAL(onDialogRequest(ParameterizedItem *)), this,
            SLOT(onDialogRequest(ParameterizedItem *)));

    groupLayout->addLayout(m_gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void BeamEditorWidget::setBeamItem(BeamItem *beamItem)
{
    m_beamItem = beamItem;
    m_intensityEditor->clearEditor();
    m_wavelengthPresenter->clearEditor();
    m_inclinationAnglePresenter->clearEditor();
    m_azimuthalAnglePresenter->clearEditor();

    if (!m_beamItem)
        return;

    m_intensityEditor->addItemProperty(m_beamItem, BeamItem::P_INTENSITY);

    ParameterizedItem *wavelengthItem = m_beamItem->getSubItems()[BeamItem::P_WAVELENGTH];
    m_wavelengthPresenter->setItem(wavelengthItem);

    ParameterizedItem *inclinationAngleItem
        = m_beamItem->getSubItems()[BeamItem::P_INCLINATION_ANGLE];
    m_inclinationAnglePresenter->setItem(inclinationAngleItem);

    ParameterizedItem *azimuthalAngleItem = m_beamItem->getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE];
    m_azimuthalAnglePresenter->setItem(azimuthalAngleItem);
}

void BeamEditorWidget::onDialogRequest(ParameterizedItem *item)
{
    DistributionDialog *dialog = new DistributionDialog;
    dialog->setItem(item);
}
