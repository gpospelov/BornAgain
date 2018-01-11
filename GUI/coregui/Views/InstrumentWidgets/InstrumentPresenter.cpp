// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.cpp
//! @brief     Implements class InstrumentPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentPresenter.h"
#include "item_constants.h"
#include "GISASInstrumentEditor.h"
#include "GISASInstrumentEditorV2.h"

namespace {
const QString GISASPresentation = "GISAS";
const QString GISASPresentationV2 = "GISAS2";
}

InstrumentPresenter::InstrumentPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(GISASPresentation, create_new<GISASInstrumentEditor>);
    registerWidget(GISASPresentationV2, create_new<GISASInstrumentEditorV2>);
}

QString InstrumentPresenter::itemPresentation() const
{
    return GISASPresentation;
}

QStringList InstrumentPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << GISASPresentation << GISASPresentationV2;
}
