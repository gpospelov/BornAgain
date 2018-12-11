// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/OffSpecInstrumentEditor.cpp
//! @brief     Implements class OffSpecInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OffSpecInstrumentEditor.h"
#include "OffSpecBeamEditor.h"
#include "GISASDetectorEditor.h"
#include "EnvironmentEditor.h"
#include "PolarizationAnalysisEditor.h"
#include "InstrumentItems.h"
#include "ColumnResizer.h"
#include "StyleUtils.h"
#include <QVBoxLayout>

OffSpecInstrumentEditor::OffSpecInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new OffSpecBeamEditor(m_columnResizer))
    , m_detectorEditor(new GISASDetectorEditor)
    // temporary switched off to avoid memory leakage
    //, m_environmentEditor(new EnvironmentEditor(m_columnResizer))
    //, m_polarizationAnalysisEditor(new PolarizationAnalysisEditor(m_columnResizer))
    , m_environmentEditor(nullptr)
    , m_polarizationAnalysisEditor(nullptr)
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_beamEditor, "Beam parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_detectorEditor, "Detector parameters"));
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void OffSpecInstrumentEditor::subscribeToItem()
{
    m_beamEditor->setItem(instrumentItem());
    m_detectorEditor->setItem(instrumentItem());
//    m_environmentEditor->setItem(instrumentItem());
//    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

OffSpecInstrumentItem* OffSpecInstrumentEditor::instrumentItem()
{
    auto result = dynamic_cast<OffSpecInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}
