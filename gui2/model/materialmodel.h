// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_MODEL_MATERIALMODEL_H
#define BORNAGAIN_GUI2_MODEL_MATERIALMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/tagrow.h"
#include <vector>

namespace ModelView {
class ExternalProperty;
}

namespace gui2 {

class MaterialBaseItem;
class MaterialContainerItem;
class SLDMaterialItem;

//! Model to hold MaterialItems.

class DAREFLCORE_EXPORT MaterialModel : public ModelView::SessionModel {
public:
    MaterialModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    std::vector<ModelView::ExternalProperty>
    material_data(std::string container_id = std::string()) const;

    ModelView::ExternalProperty material_property(const std::string& id);

    MaterialBaseItem* cloneMaterial(const MaterialBaseItem* item);

    SLDMaterialItem* addDefaultMaterial(const ModelView::TagRow& tagrow = {});

private:
    void init_model();
    MaterialContainerItem* materialContainer();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_MATERIALMODEL_H
