//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/linkeditem.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/standarditems/linkeditem.h"
#include "mvvm/model/customvariants.h"

using namespace ModelView;

namespace {
const Variant empty_link = Variant::fromValue(std::string());
}

LinkedItem::LinkedItem() : SessionItem(Constants::LinkedItemType) {
    setData(empty_link);
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void LinkedItem::setLink(const SessionItem* item) {
    setData(item ? Variant::fromValue(item->identifier()) : empty_link);
}
