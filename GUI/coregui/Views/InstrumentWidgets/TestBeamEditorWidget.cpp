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
    , m_beamItem(0)
{
    // group box layout
    QGroupBox *groupBox = new QGroupBox("Beam Parameters");
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    QGridLayout *gridLayout = new QGridLayout;

    m_wavelengthEditor = new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
//    m_wavelengthEditor = new AwesomePropertyEditor(this);
    gridLayout->addWidget(m_wavelengthEditor, 0, 0);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

void TestBeamEditorWidget::setBeamItem(TestBeamItem *beamItem)
{
    m_beamItem = beamItem;
    initWavelengthWidget();
}

void TestBeamEditorWidget::onPropertyItemChanged(const QString &property_name)
{
    qDebug() << "TestBeamEditorWidget::onPropertyItemChanged(const QString &property_name)" << property_name;
//    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
//    if(item->modelType() == Constants::BeamWavelengthType)
//        initWavelengthWidget();

}

void TestBeamEditorWidget::initWavelengthWidget()
{
    m_wavelengthEditor->clearEditor();

    Q_ASSERT(m_beamItem);
    BeamWavelengthItem *wavelengthItem = dynamic_cast<BeamWavelengthItem *>(m_beamItem->getSubItems()[TestBeamItem::P_WAVELENGTH]);
    Q_ASSERT(wavelengthItem);
    qDebug() << "    XXX 1.1";

//    ParameterizedItem *distributionItem = wavelengthItem->getSubItems()[BeamWavelengthItem::P_DISTRIBUTION];
//    qDebug() << "    XXX 1.2";

//    Q_ASSERT(distributionItem);

    m_wavelengthEditor->addItemProperties(wavelengthItem, QString("Wavelength"), AwesomePropertyEditor::INSERT_AFTER);
//    m_wavelengthEditor->addItemProperties(wavelengthItem, QString("Wavelength"));

}






/*

TestBeamEditorWidget::TestBeamEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_beamItem(0)
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



*/
