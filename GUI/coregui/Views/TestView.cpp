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
#include "BeamItem.h"
#include "LayerItem.h"
#include "AwesomePropertyEditor.h"
#include <QGroupBox>
#include <QGridLayout>

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

    BeamDistributionItem *item1 = new BeamDistributionItem;
    LayerItem *layer = new LayerItem();
    editor1->addItemProperty(layer, LayerItem::P_THICKNESS, "MyGroup");
    editor1->addItemProperties(item1, "MyGroup");

    editor2->addItemProperty(layer, LayerItem::P_THICKNESS, "MyGroup");
    editor2->addItemProperties(item1, "MyGroup", AwesomePropertyEditor::INSERT_AFTER);

    gridLayout->addWidget(editor1, 0, 0);
    gridLayout->addWidget(editor2, 0, 1);

    groupLayout->addLayout(gridLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);


}

