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

InstrumentPresenter::InstrumentPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::GISASInstrumentType, create_new<GISASInstrumentEditor>);
}

QString InstrumentPresenter::itemPresentation() const
{
    return Constants::GISASInstrumentType;
}

QStringList InstrumentPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << Constants::GISASInstrumentType;
}
