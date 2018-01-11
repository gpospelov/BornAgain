// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.cpp
//! @brief     Implements class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentComponentsWidget.h"
#include "BackgroundItems.h"
#include "BeamEditorWidget.h"
#include "ComponentEditor.h"
#include "ColumnResizer.h"
#include "DetectorEditorWidget.h"
#include "DetectorItems.h"
#include "InstrumentItems.h"
#include "GroupItem.h"
#include <QVBoxLayout>

namespace
{
const QString background_title("Background");
}

InstrumentComponentsWidget::InstrumentComponentsWidget(QWidget* parent)
    : QWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new BeamEditorWidget)
    , m_detectorEditor(new DetectorEditorWidget(m_columnResizer))
    , m_backgroundEditor(new ComponentEditor(ComponentEditor::PlainWidget, background_title))
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_beamEditor);
    mainLayout->addWidget(m_detectorEditor);
    mainLayout->addWidget(m_backgroundEditor);
    mainLayout->addStretch();

    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 0);
    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 1);
    m_columnResizer->addWidgetsFromGridLayout(m_beamEditor->gridLayout(), 2);

    connect(m_detectorEditor, &DetectorEditorWidget::extendedDetectorEditorRequest,
            this, &InstrumentComponentsWidget::extendedDetectorEditorRequest);

    setStyleSheet("InstrumentComponentsWidget {background-color:transparent;}");
}

void InstrumentComponentsWidget::setInstrumentItem(InstrumentItem* instrumentItem)
{
    m_backgroundEditor->clearEditor();
    if(instrumentItem) {
        m_beamEditor->setBeamItem(instrumentItem->beamItem());
        m_detectorEditor->setItem(instrumentItem);
        m_backgroundEditor->setItem(instrumentItem->backgroundGroup());
    } else {
        m_beamEditor->setBeamItem(nullptr);
        m_detectorEditor->setItem(nullptr);
    }
}
