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
#include "ComponentEditor.h"
#include "BeamItem.h"
#include "LayerItem.h"
#include "GroupInfoBox.h"
#include "GUIHelpers.h"
#include "ComponentEditorBox.h"
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

//    m_intensityEditor
//        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    m_intensityEditor = new ComponentEditor();
    m_intensityEditor->setPresentationType(ComponentEditorFlags::BROWSER_GROUPBOX);


    m_gridLayout->addWidget(m_intensityEditor, 0, 0);

//    m_wavelengthPresenter = new AwesomePropertyPresenter(name_of_groupbox_wavenlength, this);
//    m_gridLayout->addWidget(m_wavelengthPresenter, 1, 0);
//    connect(m_wavelengthPresenter, SIGNAL(onDialogRequest(ParameterizedItem*, QString)), this,
//            SLOT(onDialogRequest(ParameterizedItem*, QString)));

    m_wavelengthPresenter = new ComponentEditorBox(name_of_groupbox_wavenlength);
    m_gridLayout->addWidget(m_wavelengthPresenter, 1, 0);
    connect(m_wavelengthPresenter, SIGNAL(onDialogRequest(ParameterizedItem*, QString)), this,
            SLOT(onDialogRequest(ParameterizedItem*, QString)));


    m_inclinationAnglePresenter = new AwesomePropertyPresenter(name_of_groupbox_inclination, this);
    m_gridLayout->addWidget(m_inclinationAnglePresenter, 1, 1);
    connect(m_inclinationAnglePresenter, SIGNAL(onDialogRequest(ParameterizedItem*, QString)),
            this, SLOT(onDialogRequest(ParameterizedItem*, QString)));

    m_azimuthalAnglePresenter = new AwesomePropertyPresenter(name_of_groupbox_azimuthal, this);
    m_gridLayout->addWidget(m_azimuthalAnglePresenter, 1, 2);
    connect(m_azimuthalAnglePresenter, SIGNAL(onDialogRequest(ParameterizedItem*, QString)),
            this, SLOT(onDialogRequest(ParameterizedItem*, QString)));

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
//    m_intensityEditor->clearEditor();
    m_wavelengthPresenter->clearEditor();
    m_inclinationAnglePresenter->clearEditor();
    m_azimuthalAnglePresenter->clearEditor();

    if (!m_beamItem)
        return;

//    m_intensityEditor->addItemProperty(m_beamItem, BeamItem::P_INTENSITY);
    m_intensityEditor->setItem(m_beamItem->getPropertyItem(BeamItem::P_INTENSITY));

    ParameterizedItem *wavelengthItem = m_beamItem->getGroupItem(BeamItem::P_WAVELENGTH);
    m_wavelengthPresenter->setItem(wavelengthItem);

    ParameterizedItem *inclinationAngleItem
            = m_beamItem->getGroupItem(BeamItem::P_INCLINATION_ANGLE);
    m_inclinationAnglePresenter->setItem(inclinationAngleItem);

    ParameterizedItem *azimuthalAngleItem = m_beamItem->getGroupItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalAnglePresenter->setItem(azimuthalAngleItem);
}

void BeamEditorWidget::onDialogRequest(ParameterizedItem *item, QString name)
{
    DistributionDialog *dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
