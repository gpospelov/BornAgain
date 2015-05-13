// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestView.h"
#include "TestItem.h"
#include "LayerItem.h"
#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
//#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>
#include "DistributionEditor.h"
#include "qgroupbox.h"

//TestView::TestView(QWidget *parent)
//    : QWidget(parent)
//    , m_item(0)
//{
//    setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    BeamWavelengthItem *item = new BeamWavelengthItem;
//    DistributionEditor *distributionEditor = new DistributionEditor;
//    distributionEditor->setItem(item);
////    m_propertyEditor = new AwesomePropertyEditor(this);

//    // main layout
//    QVBoxLayout *mainLayout = new QVBoxLayout;

////    mainLayout->addWidget(m_propertyEditor);
//    mainLayout->addWidget(distributionEditor);
//    setLayout(mainLayout);
//}


TestView::TestView(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGroupBox *groupBox = new QGroupBox("Beam Parameters");
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    // whole content is represented as grid layout
    QGridLayout *gridLayout = new QGridLayout;

    AwesomePropertyEditor *editor1 = new AwesomePropertyEditor(this);
    editor1->setMinimumSize(256, 256);
    AwesomePropertyEditor *editor2 = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);

    TestItem *item1 = new TestItem;
    LayerItem *layer = new LayerItem();
    editor1->addItemProperty(layer, LayerItem::P_THICKNESS, "MyGroup");
    editor1->addItemProperties(item1, "MyGroup");

//    editor2->addItemProperty(layer, LayerItem::P_THICKNESS, "MyGroup");
    editor2->addItemProperties(item1, QString(), AwesomePropertyEditor::INSERT_AFTER);

    gridLayout->addWidget(editor1, 0, 0);
    gridLayout->addWidget(editor2, 0, 1);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);


}
