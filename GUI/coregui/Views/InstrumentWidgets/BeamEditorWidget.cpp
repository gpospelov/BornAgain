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
#include "ComponentBoxEditor.h"
#include "BeamItem.h"
#include "LayerItem.h"
#include "GroupInfoBox.h"
#include "GUIHelpers.h"
#include "ComponentInfoBox.h"
#include "BeamDistributionItem.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include "DistributionDialog.h"
#include <iostream>
namespace
{
    QString name_of_groupbox_wavenlength("Wavelength [nm]");
    QString name_of_groupbox_inclination("Inclination angle [deg]");
    QString name_of_groupbox_azimuthal("Azimuthal angle [deg]");
}

BeamEditorWidget::BeamEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_intensityEditor(0)
    , m_wavelengthPresenter(0)
    , m_inclinationAnglePresenter(0)
    , m_azimuthalAnglePresenter(0)
    , m_gridLayout(0)
    , m_beamItem(0)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QGroupBox *groupBox = new QGroupBox("Beam Parameters");

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    m_gridLayout = new QGridLayout;

    m_intensityEditor = new ComponentBoxEditor;


    m_gridLayout->addWidget(m_intensityEditor, 0, 0);

    m_wavelengthPresenter = new ComponentInfoBox(name_of_groupbox_wavenlength);
    m_gridLayout->addWidget(m_wavelengthPresenter, 1, 0);
    connect(m_wavelengthPresenter, SIGNAL(onDialogRequest(SessionItem*, QString)), this,
            SLOT(onDialogRequest(SessionItem*, QString)));

    m_inclinationAnglePresenter = new ComponentInfoBox(name_of_groupbox_inclination, this);
    m_gridLayout->addWidget(m_inclinationAnglePresenter, 1, 1);
    connect(m_inclinationAnglePresenter, SIGNAL(onDialogRequest(SessionItem*, QString)),
            this, SLOT(onDialogRequest(SessionItem*, QString)));

    m_azimuthalAnglePresenter = new ComponentInfoBox(name_of_groupbox_azimuthal, this);
    m_gridLayout->addWidget(m_azimuthalAnglePresenter, 1, 2);
    connect(m_azimuthalAnglePresenter, SIGNAL(onDialogRequest(SessionItem*, QString)),
            this, SLOT(onDialogRequest(SessionItem*, QString)));

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

    m_intensityEditor->addItem(m_beamItem->getItem(BeamItem::P_INTENSITY));

    SessionItem *wavelengthItem = m_beamItem->getGroupItem(BeamItem::P_WAVELENGTH);
    m_wavelengthPresenter->addPropertyItems(wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem *inclinationAngleItem
            = m_beamItem->getGroupItem(BeamItem::P_INCLINATION_ANGLE);
    m_inclinationAnglePresenter->addPropertyItems(inclinationAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    SessionItem *azimuthalAngleItem = m_beamItem->getGroupItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalAnglePresenter->addPropertyItems(azimuthalAngleItem->getItem(BeamDistributionItem::P_DISTRIBUTION));
}

void BeamEditorWidget::onDialogRequest(SessionItem *item, QString name)
{
    DistributionDialog *dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
