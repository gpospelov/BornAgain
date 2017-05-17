// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.cpp
//! @brief     Implements class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentComponentsWidget.h"
#include "InstrumentItem.h"
#include "BeamEditorWidget.h"
#include "DetectorEditorWidget.h"
#include "ColumnResizer.h"
#include <QVBoxLayout>

InstrumentComponentsWidget::InstrumentComponentsWidget(QWidget* parent)
    : QWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new BeamEditorWidget)
    , m_detectorEditor(new DetectorEditorWidget(m_columnResizer))
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_beamEditor);
    mainLayout->addWidget(m_detectorEditor);
    mainLayout->addStretch();

    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 0);
    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 1);
    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 2);

    connect(m_detectorEditor, SIGNAL(extendedDetectorEditorRequest(DetectorItem*)), this,
            SIGNAL(extendedDetectorEditorRequest(DetectorItem*)));

    setStyleSheet("InstrumentComponentsWidget {background-color:transparent;}");
}

void InstrumentComponentsWidget::setInstrumentItem(InstrumentItem* instrumentItem)
{
    if(instrumentItem) {
        m_beamEditor->setBeamItem(instrumentItem->beamItem());
        m_detectorEditor->setItem(instrumentItem);
    } else {
        m_beamEditor->setBeamItem(nullptr);
        m_detectorEditor->setItem(nullptr);
    }
}
