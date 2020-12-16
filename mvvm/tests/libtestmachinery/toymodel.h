// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_TOYMODEL_H
#define BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_TOYMODEL_H

#include "mvvm/model/itempool.h"
#include "mvvm/model/sessionmodel.h"

//! Collection of toy items and models for testing purposes.

namespace ToyItems {

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();
    SampleModel(std::shared_ptr<ModelView::ItemPool> pool);
};

} // namespace ToyItems

#endif // BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_TOYMODEL_H
