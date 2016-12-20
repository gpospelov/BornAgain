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
    HomogeneousMaterial something("something",0,0.5);

    Layer layer(air, 10*Units::nanometer);
    EXPECT_EQ(air.getName(), layer.getMaterial()->getName());
    EXPECT_EQ(nullptr, layer.getLayout(0));
    EXPECT_EQ(10, layer.getThickness());
    EXPECT_FALSE(layer.hasComputation());
    EXPECT_EQ(complex_t(1,0), layer.getRefractiveIndex());
    EXPECT_EQ(0.0, layer.getTotalParticleSurfaceDensity(0));
    EXPECT_EQ(BornAgain::LayerType, layer.getName());

    layer.setThickness(20.0);
    EXPECT_EQ(20, layer.getThickness());
    layer.setMaterial(something);
    EXPECT_EQ(something.getName(), layer.getMaterial()->getName());
    EXPECT_EQ(BornAgain::LayerType, layer.getName());
    EXPECT_EQ(complex_t(1,0.5), layer.getRefractiveIndex());

    std::unique_ptr<Layer> clone(layer.clone());
    EXPECT_EQ(something.getName(), clone->getMaterial()->getName());
    EXPECT_EQ(nullptr, clone->getLayout(0));
    EXPECT_EQ(20, clone->getThickness());
    EXPECT_FALSE(clone->hasComputation());
    EXPECT_EQ(complex_t(1,0.5), clone->getRefractiveIndex());
    EXPECT_EQ(0.0, clone->getTotalParticleSurfaceDensity(0));
    EXPECT_EQ(BornAgain::LayerType, clone->getName());
}


TEST_F(LayerTest, LayerAndDecoration)
{
    HomogeneousMaterial air("air",0,0);
    std::unique_ptr<ParticleLayout> layout1(new ParticleLayout());

    Layer layer(air, 10*Units::nanometer);
    layer.addLayout(*layout1);
    EXPECT_TRUE(layer.hasComputation());

    ParticleLayout layout2;
    layer.addLayout(layout2);
    EXPECT_EQ(layer.getNumberOfLayouts(), 2u);
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
    EXPECT_EQ(children.at(0), layer.getLayout(0));
    EXPECT_EQ(children.at(1), layer.getLayout(1));
}
