#include "Layer.h"
#include "LayerInterface.h"
#include "HomogeneousMaterial.h"
#include "LayerRoughness.h"
#include <memory>

class LayerInterfaceTest : public ::testing::Test
{
 protected:
    LayerInterfaceTest(){}
    virtual ~LayerInterfaceTest(){}
};

TEST_F(LayerInterfaceTest, createSmoothInterface)
{
    std::unique_ptr<Layer> layer0(new Layer(HomogeneousMaterial("air", 0.0, 0.0)));
    std::unique_ptr<Layer> layer1(new Layer(HomogeneousMaterial("air", 0.0, 0.0)));

    std::unique_ptr<LayerInterface> interface(
                LayerInterface::createSmoothInterface(layer0.get(), layer1.get()));

    EXPECT_EQ(interface->topLayer(), layer0.get());
    EXPECT_EQ(interface->bottomLayer(), layer1.get());
    EXPECT_EQ(interface->getRoughness(), nullptr);
    EXPECT_EQ(interface->getChildren().size(), 0u);
}

TEST_F(LayerInterfaceTest, createRoughInterface)
{
    std::unique_ptr<Layer> layer0(new Layer(HomogeneousMaterial("air", 0.0, 0.0)));
    std::unique_ptr<Layer> layer1(new Layer(HomogeneousMaterial("air", 0.0, 0.0)));

    std::unique_ptr<LayerInterface> interface(LayerInterface::createRoughInterface(
        layer0.get(), layer1.get(), LayerRoughness(1.0, 2.0, 3.0)));

    EXPECT_EQ(interface->topLayer(), layer0.get());
    EXPECT_EQ(interface->bottomLayer(), layer1.get());
    EXPECT_EQ(interface->getRoughness()->getSigma(), 1.0);
    std::vector<const INode*> children =interface->getChildren();
    EXPECT_EQ(children.size(), 1u);
    EXPECT_TRUE(dynamic_cast<const LayerRoughness*>(children.at(0)) != nullptr);
}
