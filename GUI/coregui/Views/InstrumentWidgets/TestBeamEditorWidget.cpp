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
#include "CustomPropertyEditor.h"
#include "AwesomePropertyEditor.h"
#include "BeamItem.h"
#include "LayerItem.h"
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


//    QGridLayout *beamParamsLayout = new QGridLayout;
    //beamGroup->setLayout(beamParamsLayout);

//    beamParamsLayout->addWidget(new QLabel("Intensity"), 0, 0);
//    beamParamsLayout->addWidget(new QLineEdit, 0, 1);


    AwesomePropertyEditor *editor1 = new AwesomePropertyEditor(this);
    AwesomePropertyEditor *editor2 = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);

    BeamDistributionItem *item1 = new BeamDistributionItem;
    LayerItem *layer = new LayerItem();
//    editor1->addItemProperty(item1, BeamDistributionItem::P_VALUE);
    editor1->addItemProperty(layer, LayerItem::P_THICKNESS);
//    editor1->addItemPropertyToGroup(item1, BeamDistributionItem::P_VALUE, "xxx");
//    editor1->addItemPropertyToGroup(layer, LayerItem::P_THICKNESS, "xxx");
//    editor1->addItemPropertyToGroup(item1, BeamDistributionItem::P_COMBO, "xxx");

    editor1->addItemProperties(item1);

//    editor2->addItemProperty(item1, BeamDistributionItem::P_VALUE);
    editor2->addItemProperty(layer, LayerItem::P_THICKNESS);
//    editor2->addItemPropertyToGroup(item1, BeamDistributionItem::P_VALUE, "xxx");
//    editor2->addItemPropertyToGroup(layer, LayerItem::P_THICKNESS, "xxx");
//    editor2->addItemPropertyToGroup(item1, BeamDistributionItem::P_COMBO, "xxx");

    editor2->addItemProperties(item1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(editor1, 3);
    hlayout->addWidget(editor2);

    beamGroupLayout->addLayout(hlayout);
//    CustomPropertyEditor *editor = new CustomPropertyEditor(0, this);
    //editor->setCreateGroupProperty(false);
//    editor->setItem(new BeamDistributionItem);

//    beamParamsLayout->addWidget(new QLabel("Wavelength"), 1, 0);
//    beamParamsLayout->addWidget(editor1, 1, 0);
//    beamParamsLayout->addWidget(editor2, 1, 1);


    //beamGroupLayout->addLayout(beamParamsLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(beamGroup);
    setLayout(mainLayout);
}



