//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/itemfactory.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMFACTORY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMFACTORY_H

#include "mvvm/interfaces/itemfactoryinterface.h"
#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class ItemCatalogue;

//! Default SessionItem factory.

class MVVM_MODEL_EXPORT ItemFactory : public ItemFactoryInterface {
public:
    ItemFactory(std::unique_ptr<ItemCatalogue> catalogue);
    ~ItemFactory() override;

    void registerItem(const std::string& modelType, item_factory_func_t func,
                      const std::string& label) override;

    std::unique_ptr<SessionItem> createItem(const model_type& modelType) const override;

protected:
    std::unique_ptr<ItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMFACTORY_H
