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
#include "BeamItem.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

TestBeamEditorWidget::TestBeamEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *beamGroup = new QGroupBox("Beam Parameters");
    QVBoxLayout *beamGroupLayout = new QVBoxLayout;
    beamGroup->setLayout(beamGroupLayout);

//    QVBoxLayout *beamGroupLayout = new QVBoxLayout;
//    beamGroup->setLayout(beamGroupLayout);


    QGridLayout *beamParamsLayout = new QGridLayout;
    //beamGroup->setLayout(beamParamsLayout);

    beamParamsLayout->addWidget(new QLabel("Intensity"), 0, 0);
    beamParamsLayout->addWidget(new QLineEdit, 0, 1);


    UniversalPropertyEditor *editor = new UniversalPropertyEditor(0, this);
    editor->setCreateGroupProperty(false);
    editor->setItem(new BeamDistributionItem);

    beamParamsLayout->addWidget(new QLabel("Wavelength"), 1, 0);
    beamParamsLayout->addWidget(editor, 1, 1);


    beamGroupLayout->addLayout(beamParamsLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(beamGroup);
    setLayout(mainLayout);
}



