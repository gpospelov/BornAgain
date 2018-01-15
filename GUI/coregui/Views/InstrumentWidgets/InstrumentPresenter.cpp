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
#include "OffSpecInstrumentEditor.h"
#include "GUIHelpers.h"
#include "SessionItem.h"

namespace {
const QString GISASPresentation = "GISAS";
const QString OffSpecPresentation = "OffSpec";
}

InstrumentPresenter::InstrumentPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(GISASPresentation, create_new<GISASInstrumentEditor>);
    registerWidget(OffSpecPresentation, create_new<OffSpecInstrumentEditor>);
    setToolBarVisible(false);
}

QString InstrumentPresenter::itemPresentation() const
{
    if (currentItem()->modelType() == Constants::GISASInstrumentType)
        return GISASPresentation;
    else if (currentItem()->modelType() == Constants::OffSpecInstrumentType)
        return OffSpecPresentation;
    else
        throw GUIHelpers::Error("InstrumentPresenter::itemPresentation() -> Error. Wrong item "
                                "type '"+currentItem()->modelType()+"'");
}

QStringList InstrumentPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << GISASPresentation << OffSpecPresentation;
}
