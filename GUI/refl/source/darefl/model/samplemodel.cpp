// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/sampleitems.h>
#include <darefl/model/samplemodel.h>
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace DaRefl
{

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    result->registerItem<RoughnessItem>();
    return result;
}
} // namespace

SampleModel::SampleModel(std::shared_ptr<ModelView::ItemPool> pool)
    : SessionModel("SampleModel", pool)
{
    setItemCatalogue(CreateItemCatalogue());
}

//! Populate the model with default MultiLayer with 3 layers.

void SampleModel::create_default_multilayer()
{
    auto multilayer = insertItem<MultiLayerItem>();

    auto top = insertItem<LayerItem>(multilayer);
    top->setProperty(LayerItem::P_NAME, std::string("Ambient"));
    auto middle = insertItem<LayerItem>(multilayer);
    middle->setProperty(LayerItem::P_NAME, std::string("Middle"));
    auto substrate = insertItem<LayerItem>(multilayer);
    substrate->setProperty(LayerItem::P_NAME, std::string("Substrate"));

    middle->setProperty(LayerItem::P_THICKNESS, 42.0);
}

} // namespace DaRefl
