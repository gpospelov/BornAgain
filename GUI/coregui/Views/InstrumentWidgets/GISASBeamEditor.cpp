// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASBeamEditor.cpp
//! @brief     Implements class GISASBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GISASBeamEditor.h"
#include "BeamDistributionItem.h"
#include "BeamItem.h"
#include "ComponentEditor.h"
#include "DistributionDialog.h"
#include <QGridLayout>
#include <QGroupBox>

namespace
{
const QString wavelength_title("Wavelength [nm]");
const QString inclination_title("Inclination angle [deg]");
const QString azimuthal_title("Azimuthal angle [deg]");
const QString polarization_title("Polarization (Bloch vector)");
}

GISASBeamEditor::GISASBeamEditor(QWidget* parent)
    : QWidget(parent)
    , m_intensityEditor(new ComponentEditor(ComponentEditor::PlainWidget)),
      m_wavelengthEditor(new ComponentEditor(ComponentEditor::InfoWidget, wavelength_title)),
      m_inclinationEditor(new ComponentEditor(ComponentEditor::InfoWidget, inclination_title)),
      m_azimuthalEditor(new ComponentEditor(ComponentEditor::InfoWidget, azimuthal_title)),
      m_gridLayout(new QGridLayout)
    , m_beamItem(nullptr)
{
    m_gridLayout->addWidget(m_intensityEditor, 0, 0);
    m_gridLayout->addWidget(m_wavelengthEditor, 1, 0);
    m_gridLayout->addWidget(m_inclinationEditor, 1, 1);
    m_gridLayout->addWidget(m_azimuthalEditor, 1, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout());
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_wavelengthEditor, &ComponentEditor::dialogRequest,
            this, &GISASBeamEditor::onDialogRequest);
    connect(m_inclinationEditor, &ComponentEditor::dialogRequest,
            this, &GISASBeamEditor::onDialogRequest);
    connect(m_azimuthalEditor, &ComponentEditor::dialogRequest,
            this, &GISASBeamEditor::onDialogRequest);
}

void GISASBeamEditor::setBeamItem(BeamItem* beamItem)
{
    m_beamItem = beamItem;
    m_intensityEditor->clearEditor();
    m_wavelengthEditor->clearEditor();
    m_inclinationEditor->clearEditor();
    m_azimuthalEditor->clearEditor();

    if (!m_beamItem)
        return;

    m_intensityEditor->setItem(m_beamItem->getItem(BeamItem::P_INTENSITY));

    SessionItem* wavelengthItem = m_beamItem->getItem(BeamItem::P_WAVELENGTH);
    m_wavelengthEditor->setItem(
        wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem* inclinationAngleItem = m_beamItem->getItem(BeamItem::P_INCLINATION_ANGLE);
    m_inclinationEditor->setItem(
        inclinationAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem* azimuthalAngleItem = m_beamItem->getItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalEditor->setItem(
        azimuthalAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));
}

void GISASBeamEditor::onDialogRequest(SessionItem* item, const QString& name)
{
    if(!item)
        return;

    auto dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
