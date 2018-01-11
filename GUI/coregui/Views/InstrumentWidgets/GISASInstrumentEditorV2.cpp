// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditorV2.cpp
//! @brief     Implements class GISASInstrumentEditorV2
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GISASInstrumentEditorV2.h"
#include "GISASBeamEditor.h"
#include "GISASDetectorEditor.h"
#include "EnvironmentEditor.h"
#include "PolarizationAnalysisEditor.h"
#include "InstrumentItems.h"
#include "detailswidget.h"
#include <QVBoxLayout>

GISASInstrumentEditorV2::GISASInstrumentEditorV2(QWidget* parent)
    : SessionItemWidget(parent)
    , m_beamEditor(new GISASBeamEditor)
    , m_detectorEditor(new GISASDetectorEditor)
    , m_environmentEditor(new EnvironmentEditor)
    , m_polarizationAnalysisEditor(new PolarizationAnalysisEditor)
{
    auto mainLayout = new QVBoxLayout;

    addEditor(mainLayout, m_beamEditor, "Beam parameters");
    addEditor(mainLayout, m_detectorEditor, "Detector parameters");
    addEditor(mainLayout, m_environmentEditor, "Environment", /*expanded*/false);
    addEditor(mainLayout, m_polarizationAnalysisEditor, "Polarization analysis", /*expanded*/false);

    mainLayout->addStretch();

    setLayout(mainLayout);
}

void GISASInstrumentEditorV2::subscribeToItem()
{
    m_beamEditor->setBeamItem(instrumentItem()->beamItem());
}

void GISASInstrumentEditorV2::unsubscribeFromItem()
{
    m_beamEditor->setBeamItem(nullptr);
}

void GISASInstrumentEditorV2::addEditor(QVBoxLayout* layout, QWidget* widget, const QString& name,
                                        bool expanded)
{
    auto detailsWidget = new Utils::DetailsWidget;
    detailsWidget->setSummaryText(name);
    detailsWidget->setSummaryFontBold(true);
    detailsWidget->setWidget(widget);
    if (expanded)
        detailsWidget->setState(Utils::DetailsWidget::Expanded);
    layout->addWidget(detailsWidget);
}

GISASInstrumentItem*GISASInstrumentEditorV2::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}
