#include "Layer.h"
#include "HomogeneousMaterial.h"
#include "ParticleLayout.h"
#include "Units.h"

class LayerTest : public ::testing::Test
{
 protected:
    LayerTest(){}
    virtual ~LayerTest(){}
};

TEST_F(LayerTest, LayerGetAndSet)
{
    HomogeneousMaterial air("air",0,0);

    Layer layer(air, 10*Units::nanometer);
    EXPECT_EQ(air.getName(), layer.material()->getName());
    EXPECT_EQ(nullptr, layer.layout(0));
    EXPECT_EQ(10, layer.thickness());
    EXPECT_EQ(layer.numberOfLayouts(), 0u);
    EXPECT_EQ(complex_t(1, 0), layer.refractiveIndex());
    EXPECT_EQ(BornAgain::LayerType, layer.getName());

    layer.setThickness(20.0);
    EXPECT_EQ(20, layer.thickness());
    EXPECT_EQ(BornAgain::LayerType, layer.getName());
    EXPECT_EQ(complex_t(1, 0), layer.refractiveIndex());

    std::unique_ptr<Layer> clone(layer.clone());
    EXPECT_EQ(air.getName(), clone->material()->getName());
    EXPECT_EQ(nullptr, clone->layout(0));
    EXPECT_EQ(20, clone->thickness());
    EXPECT_EQ(clone->numberOfLayouts(), 0u);
    EXPECT_EQ(complex_t(1, 0), clone->refractiveIndex());
    EXPECT_EQ(BornAgain::LayerType, clone->getName());
}


TEST_F(LayerTest, LayerAndDecoration)
{
    HomogeneousMaterial air("air",0,0);
    std::unique_ptr<ParticleLayout> layout1(new ParticleLayout());

    Layer layer(air, 10*Units::nanometer);
    layer.addLayout(*layout1);
    EXPECT_EQ(layer.numberOfLayouts(), 1u);

    ParticleLayout layout2;
    layer.addLayout(layout2);
    EXPECT_EQ(layer.numberOfLayouts(), 2u);
}

TEST_F(LayerTest, getChildren)
{
    Layer layer(HomogeneousMaterial("air", 0.0, 0.0));

    std::vector<const INode*> children = layer.getChildren();
    EXPECT_EQ(children.size(), 0u);

    // children after adding layout
    layer.addLayout(ParticleLayout());
    layer.addLayout(ParticleLayout());

    children = layer.getChildren();
    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0), layer.layout(0));
    EXPECT_EQ(children.at(1), layer.layout(1));
}
