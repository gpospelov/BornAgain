// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestInstrumentWidget.cpp
//! @brief     Implements class TestInstrumentWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestInstrumentWidget.h"
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>


TestInstrumentWidget::TestInstrumentWidget(QWidget *parent)
    : QWidget(parent)
{
    // group box layout
    QGroupBox *beamGroup = new QGroupBox("Test Widget");
    QVBoxLayout *beamGroupLayout = new QVBoxLayout;
    beamGroup->setLayout(beamGroupLayout);

    beamGroupLayout->addWidget(new QLabel("xxx"));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(beamGroup);
    setLayout(mainLayout);
}


void TestInstrumentWidget::setBeamItem(BeamItem *item)
{
    m_currentItem = item;
}
