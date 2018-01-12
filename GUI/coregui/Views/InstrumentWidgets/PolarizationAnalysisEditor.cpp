// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.cpp
//! @brief     Implements class PolarizationAnalysisEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PolarizationAnalysisEditor.h"
#include "ComponentEditor.h"
#include "InstrumentItems.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "ColumnResizer.h"
#include "LayoutUtils.h"
#include <QGridLayout>
#include <QSpacerItem>

namespace
{
const QString beam_pol_title("Polarization (Bloch vector)");
const QString analyzer_title = "Analyzer orientation";
}

PolarizationAnalysisEditor::PolarizationAnalysisEditor(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(columnResizer)
    , m_polarizationEditor(new ComponentEditor(ComponentEditor::GroupWidget, beam_pol_title))
    , m_analyserEditor(new ComponentEditor(ComponentEditor::GroupWidget, analyzer_title))
    , m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_polarizationEditor, 0, 0);
    m_gridLayout->addWidget(m_analyserEditor, 0, 1);
    m_gridLayout->addWidget(LayoutUtils::placeHolder(), 0, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void PolarizationAnalysisEditor::subscribeToItem()
{
    m_polarizationEditor->setItem(beamItem()->getItem(BeamItem::P_POLARIZATION));

    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == GISASInstrumentItem::P_DETECTOR)
                updateAnalyserEditor();
        }, this);

    updateAnalyserEditor();
}

void PolarizationAnalysisEditor::unsubscribeFromItem()
{
    m_polarizationEditor->clearEditor();
    m_analyserEditor->clearEditor();
}

GISASInstrumentItem* PolarizationAnalysisEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

BeamItem* PolarizationAnalysisEditor::beamItem()
{
    return instrumentItem()->beamItem();
}

DetectorItem* PolarizationAnalysisEditor::detectorItem()
{
    return instrumentItem()->detectorItem();
}

//! Updates analyser editor to display properties of currently selected detector
//! (spherical/rectangular).

void PolarizationAnalysisEditor::updateAnalyserEditor()
{
    m_analyserEditor->clearEditor();
    m_analyserEditor->addItem(detectorItem()->getItem(DetectorItem::P_ANALYZER_EFFICIENCY));
    m_analyserEditor->addItem(detectorItem()->getItem(DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION));
}
