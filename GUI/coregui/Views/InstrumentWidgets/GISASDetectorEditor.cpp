// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.cpp
//! @brief     Implements class GISASDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GISASDetectorEditor.h"
#include "ComponentEditor.h"
#include "DetectorPresenter.h"
#include "InstrumentItems.h"
#include "DetectorItems.h"
#include "GroupItem.h"
#include <QVBoxLayout>

GISASDetectorEditor::GISASDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_detectorTypeEditor(new ComponentEditor(ComponentEditor::PlainWidget
                                               | ComponentEditor::W_NoChildren))
    , m_detectorPresenter(new DetectorPresenter)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_detectorTypeEditor);
    mainLayout->addWidget(m_detectorPresenter);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void GISASDetectorEditor::subscribeToItem()
{
    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == GISASInstrumentItem::P_DETECTOR)
                updateDetectorPresenter();
        }, this);

    m_detectorTypeEditor->clearEditor();
    m_detectorTypeEditor->setItem(instrumentItem()->detectorGroup());

    updateDetectorPresenter();
}

void GISASDetectorEditor::unsubscribeFromItem()
{

}

GISASInstrumentItem* GISASDetectorEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

//! Shows detector editor corresponding to the currently selected detector in detectorGroup.

void GISASDetectorEditor::updateDetectorPresenter()
{
    m_detectorPresenter->setItem(instrumentItem()->detectorItem());
}
