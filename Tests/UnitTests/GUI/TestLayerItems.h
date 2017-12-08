#include "google_test.h"
#include "ApplicationModels.h"
#include "ExternalProperty.h"
#include "LayerItem.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include "ModelMapper.h"
#include "SampleModel.h"

class TestLayerItems : public ::testing::Test
{
public:
    ~TestLayerItems();
};

TestLayerItems::~TestLayerItems() = default;

//! Checking default material of the layer.

TEST_F(TestLayerItems, test_LayerDefaultMaterial)
{
    ApplicationModels models;
    auto layer = models.sampleModel()->insertNewItem(Constants::LayerType);
    auto materials = models.materialModel()->topItems();
    auto defMaterial = materials.front();

    ExternalProperty material
        = layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
    EXPECT_EQ(material.text(), QString("Default"));
    EXPECT_EQ(material.identifier(),
              defMaterial->getItemValue(MaterialItem::P_IDENTIFIER).toString());
}
