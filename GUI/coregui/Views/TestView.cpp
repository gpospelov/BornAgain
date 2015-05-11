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

TestView::TestView(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    BeamWavelengthItem *item = new BeamWavelengthItem;
    DistributionEditor *distributionEditor = new DistributionEditor;
    distributionEditor->setItem(item);
//    m_propertyEditor = new AwesomePropertyEditor(this);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

//    mainLayout->addWidget(m_propertyEditor);
    mainLayout->addWidget(distributionEditor);
    setLayout(mainLayout);
}


