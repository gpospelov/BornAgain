//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/propertyitem.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/model/propertyitem.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/mvvm_types.h"

using namespace ModelView;

PropertyItem::PropertyItem() : SessionItem(Constants::PropertyType) {}

PropertyItem* PropertyItem::setDisplayName(const std::string& name) {
    SessionItem::setDisplayName(name);
    return this;
}

PropertyItem* PropertyItem::setLimits(const RealLimits& value) {
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}
