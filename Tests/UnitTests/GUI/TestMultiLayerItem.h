#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "SampleModel.h"
#include "google_test.h"
#include "item_constants.h"

class TestMultiLayerItem : public ::testing::Test
{
public:
    ~TestMultiLayerItem();
};

TestMultiLayerItem::~TestMultiLayerItem() = default;

//! Testing layer appearance (enabled, disabled) in a MultiLayer made of two default layers.

TEST_F(TestMultiLayerItem, test_twoLayerSystem)
{
    SampleModel model;

    auto multilayer = model.insertNewItem(Constants::MultiLayerType);
    auto top = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
    auto bottom = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Thickness property should be disabled for top and bottom layers
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // Thickness value should be 0.0 for top and bottom layers
    EXPECT_EQ(top->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);
    EXPECT_EQ(bottom->getItemValue(LayerItem::P_THICKNESS).toDouble(), 0.0);

    // Roughness group property should be disabled for top, and enabled for bottom layers
    EXPECT_FALSE(top->getItem(LayerItem::P_ROUGHNESS)->isEnabled());
    EXPECT_TRUE(bottom->getItem(LayerItem::P_ROUGHNESS)->isEnabled());

    // Default roughness should be "LayerZeroRoughness"
    EXPECT_EQ(top->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(),
              Constants::LayerZeroRoughnessType);
    EXPECT_EQ(bottom->getGroupItem(LayerItem::P_ROUGHNESS)->modelType(),
              Constants::LayerZeroRoughnessType);
}
