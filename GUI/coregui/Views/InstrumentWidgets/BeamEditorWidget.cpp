// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/BeamEditorWidget.cpp
//! @brief     Implements class BeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BeamEditorWidget.h"
#include "BeamDistributionItem.h"
#include "BeamItem.h"
#include "ComponentBoxEditor.h"
#include "ComponentInfoBox.h"
#include "DistributionDialog.h"
#include <QGridLayout>

namespace
{
const QString name_of_groupbox_wavenlength("Wavelength [nm]");
const QString name_of_groupbox_inclination("Inclination angle [deg]");
const QString name_of_groupbox_azimuthal("Azimuthal angle [deg]");
}

BeamEditorWidget::BeamEditorWidget(QWidget* parent)
    : QWidget(parent)
    , m_intensityEditor(new ComponentBoxEditor)
    , m_wavelengthPresenter(new ComponentInfoBox(name_of_groupbox_wavenlength))
    , m_inclinationAnglePresenter(new ComponentInfoBox(name_of_groupbox_inclination))
    , m_azimuthalAnglePresenter(new ComponentInfoBox(name_of_groupbox_azimuthal))
    , m_gridLayout(new QGridLayout)
    , m_beamItem(nullptr)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    // whole content is represented as grid layout
    m_gridLayout->addWidget(m_intensityEditor, 0, 0);
    m_gridLayout->addWidget(m_wavelengthPresenter, 1, 0);
    m_gridLayout->addWidget(m_inclinationAnglePresenter, 1, 1);
    m_gridLayout->addWidget(m_azimuthalAnglePresenter, 1, 2);

    QGroupBox* groupBox = new QGroupBox(QStringLiteral("Beam Parameters"));
    QVBoxLayout* groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);
    groupLayout->addLayout(m_gridLayout);

    // main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_wavelengthPresenter, SIGNAL(onDialogRequest(SessionItem*, QString)),
            this, SLOT(onDialogRequest(SessionItem*, QString)));
    connect(m_inclinationAnglePresenter, SIGNAL(onDialogRequest(SessionItem*, QString)),
            this, SLOT(onDialogRequest(SessionItem*, QString)));
    connect(m_azimuthalAnglePresenter, SIGNAL(onDialogRequest(SessionItem*, QString)),
            this, SLOT(onDialogRequest(SessionItem*, QString)));
}

void BeamEditorWidget::setBeamItem(BeamItem* beamItem)
{
    m_beamItem = beamItem;
    m_intensityEditor->clearEditor();
    m_wavelengthPresenter->clearEditor();
    m_inclinationAnglePresenter->clearEditor();
    m_azimuthalAnglePresenter->clearEditor();

    if (!m_beamItem)
        return;

    m_intensityEditor->addItem(m_beamItem->getItem(BeamItem::P_INTENSITY));

    SessionItem* wavelengthItem = m_beamItem->getItem(BeamItem::P_WAVELENGTH);
    m_wavelengthPresenter->addPropertyItems(
        wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem* inclinationAngleItem = m_beamItem->getItem(BeamItem::P_INCLINATION_ANGLE);
    m_inclinationAnglePresenter->addPropertyItems(
        inclinationAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem* azimuthalAngleItem = m_beamItem->getItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalAnglePresenter->addPropertyItems(
        azimuthalAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));
}

void BeamEditorWidget::onDialogRequest(SessionItem* item, const QString& name)
{
    if(!item)
        return;

    DistributionDialog* dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
