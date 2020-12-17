//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/propertyitem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_PROPERTYITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_PROPERTYITEM_H

#include "mvvm/model/sessionitem.h"

namespace ModelView {

class RealLimits;

//! Item to carry concrete editable entity (e.g. 'double' value with limits).
//! Intended for use as a child or CompountItem, not expected to have own children.

class MVVM_MODEL_EXPORT PropertyItem : public SessionItem {
public:
    PropertyItem();

    PropertyItem* setDisplayName(const std::string& name) override;

    PropertyItem* setLimits(const RealLimits& value);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_PROPERTYITEM_H
