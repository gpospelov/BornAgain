// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H

#include "mvvm/model/itemcatalogue.h"

namespace ModelView {

//! Creates a catalog of items supported by SessionModel out-of-the-box.
MVVM_MODEL_EXPORT std::unique_ptr<ItemCatalogue> CreateStandardItemCatalogue();

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H
