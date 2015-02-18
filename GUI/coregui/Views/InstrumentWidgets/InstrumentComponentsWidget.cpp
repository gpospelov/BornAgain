// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.cpp
//! @brief     Implements class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentComponentsWidget.h"
#include "TestBeamEditorWidget.h"
#include "TestDetectorEditorWidget.h"
#include <QVBoxLayout>
#include <QDebug>


InstrumentComponentsWidget::InstrumentComponentsWidget(QWidget *parent)
    : QWidget(parent)
    , m_beamEditor(new TestBeamEditorWidget)
    , m_detectorEditor(new TestDetectorEditorWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_beamEditor);
    mainLayout->addWidget(m_detectorEditor);
    setLayout(mainLayout);
}


void InstrumentComponentsWidget::setBeamItem(TestBeamItem *beamItem)
{
    m_beamItem = beamItem;
    m_beamEditor->setBeamItem(beamItem);
}
