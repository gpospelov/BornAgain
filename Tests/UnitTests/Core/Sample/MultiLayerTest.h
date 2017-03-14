//! Trivial construct/clone/get tests for class MultiLayer. No physics tested here.

#include "BornAgainNamespace.h"
#include "HomogeneousMagneticMaterial.h"
#include "Layer.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"

class MultiLayerTest : public ::testing::Test
{
protected:
    MultiLayerTest()
        // The following delta, beta are all unphysical. Values don't matter here.
        : air("air", 1e-6, 9e-4)
        , iron("iron", 2e-5, 8e-5)
        , chromium("chromium", 3e-7, 7e-6)
        , stone("stone", 4e-4, 8e-7)
        , topLayer(air, 0*Units::nanometer)
        , layer1(iron, 20*Units::nanometer)
        , layer2(chromium, 40*Units::nanometer)
        , substrate(stone, 0*Units::nanometer) {}
    void set_four() {
        mLayer.addLayer(topLayer);
        mLayer.addLayer(layer1);
        mLayer.addLayer(layer2);
        mLayer.addLayer(substrate);
    }

    MultiLayer mLayer;
    const HomogeneousMaterial air, iron, chromium, stone;
    Layer topLayer, layer1, layer2, substrate;
};

TEST_F(MultiLayerTest, BasicProperty)
{
    //check default properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayer.getName());
    EXPECT_EQ(0.0, mLayer.crossCorrLength());
    EXPECT_EQ(size_t(0), mLayer.numberOfLayers());
    EXPECT_EQ(size_t(0), mLayer.numberOfInterfaces());

    //set parameter
    mLayer.setParameterValue(BornAgain::CrossCorrelationLength, 2.54);
    EXPECT_EQ(2.54, mLayer.crossCorrLength());

    // adding layers
    mLayer.addLayer(topLayer);
    EXPECT_EQ(size_t(1), mLayer.numberOfLayers());
    EXPECT_EQ(size_t(0), mLayer.numberOfInterfaces());

    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(substrate);
    EXPECT_EQ(size_t(4), mLayer.numberOfLayers());
    EXPECT_EQ(size_t(3), mLayer.numberOfInterfaces());
}

TEST_F(MultiLayerTest, LayerThicknesses)
{
    set_four();

    //check layer thickness
    EXPECT_EQ( 0.0, mLayer.layerThickness(0));
    EXPECT_EQ(20.0, mLayer.layerThickness(1));
    EXPECT_EQ(40.0, mLayer.layerThickness(2));
    EXPECT_EQ( 0.0, mLayer.layerThickness(3));

    //check bottomZ value
    EXPECT_EQ(  0.0, mLayer.layerBottomZ(0));
    EXPECT_EQ(-20.0, mLayer.layerBottomZ(1));
    EXPECT_EQ(-60.0, mLayer.layerBottomZ(2));
    EXPECT_EQ(-60.0, mLayer.layerBottomZ(3));

    //set layer thickness
    mLayer.setLayerThickness(1, 45.0);
    EXPECT_EQ(45.0, mLayer.layerThickness(1));

    EXPECT_EQ(  0.0, mLayer.layerBottomZ(0));
    EXPECT_EQ(-45.0, mLayer.layerBottomZ(1));
    EXPECT_EQ(-85.0, mLayer.layerBottomZ(2));
    EXPECT_EQ(-85.0, mLayer.layerBottomZ(3));
}

TEST_F(MultiLayerTest, CheckAllLayers)
{
    set_four();

    //check individual layer
    const Layer* got0 = mLayer.layer(0);
    EXPECT_EQ(BornAgain::LayerType, got0->getName());
    EXPECT_EQ(0, got0->thickness());
    EXPECT_EQ(topLayer.material()->getName(), got0->material()->getName());

    const Layer* got1 = mLayer.layer(1);
    EXPECT_EQ(BornAgain::LayerType, got1->getName());
    EXPECT_EQ(20, got1->thickness());
    EXPECT_EQ(layer1.material()->getName(), got1->material()->getName());

    const Layer* got2 = mLayer.layer(2);
    EXPECT_EQ(BornAgain::LayerType, got2->getName());
    EXPECT_EQ(40, got2->thickness());
    EXPECT_EQ(layer2.material()->getName(), got2->material()->getName());

    const Layer* got3 = mLayer.layer(3);
    EXPECT_EQ(BornAgain::LayerType, got3->getName());
    EXPECT_EQ(0, got3->thickness());
    EXPECT_EQ(substrate.material()->getName(), got3->material()->getName());
}

TEST_F(MultiLayerTest, LayerInterfaces)
{
    set_four();

    //check interfaces
    const LayerInterface* interface0 = mLayer.layerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(),
              interface0->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(),
              interface0->bottomLayer()->material()->getName());

    const LayerInterface* interface1 = mLayer.layerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.material()->getName(),
              interface1->topLayer()->material()->getName());
    EXPECT_EQ(layer2.material()->getName(),
              interface1->bottomLayer()->material()->getName());

    const LayerInterface* interface2 = mLayer.layerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.material()->getName(),
              interface2->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(),
              interface2->bottomLayer()->material()->getName());

    //bottom interface
    const LayerInterface* interfaceBottom = mLayer.layerBottomInterface(0);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(),
              interfaceBottom->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(),
              interfaceBottom->bottomLayer()->material()->getName());

    //top interface
    const LayerInterface* interfaceTop = mLayer.layerTopInterface(3);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.material()->getName(),
              interfaceTop->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(),
              interfaceTop->bottomLayer()->material()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayer.layerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayer.layerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);
}

TEST_F(MultiLayerTest, Clone)
{
    set_four();

    MultiLayer* mLayerClone = mLayer.clone();

    //check properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayerClone->getName());
    EXPECT_EQ(0.0,mLayerClone->crossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->numberOfLayers());
    EXPECT_EQ(size_t(3), mLayerClone->numberOfInterfaces());

    //check layer thickness
    EXPECT_EQ(topLayer.thickness(), mLayerClone->layerThickness(0));
    EXPECT_EQ(layer1.thickness(), mLayerClone->layerThickness(1));
    EXPECT_EQ(layer2.thickness(), mLayerClone->layerThickness(2));
    EXPECT_EQ(substrate.thickness(), mLayerClone->layerThickness(3));

    //check bottomZ value
    EXPECT_EQ(mLayer.layerBottomZ(0), mLayerClone->layerBottomZ(0));
    EXPECT_EQ(mLayer.layerBottomZ(1), mLayerClone->layerBottomZ(1));
    EXPECT_EQ(mLayer.layerBottomZ(2), mLayerClone->layerBottomZ(2));
    EXPECT_EQ(mLayer.layerBottomZ(3), mLayerClone->layerBottomZ(3));

    //check individual layer
    const Layer* layerCopy0 = mLayerClone->layer(0);
    EXPECT_EQ(topLayer.getName(), layerCopy0->getName());
    EXPECT_EQ(topLayer.thickness(), layerCopy0->thickness());
    EXPECT_EQ(topLayer.material()->getName(), layerCopy0->material()->getName());

    const Layer* layerCopy1 = mLayerClone->layer(1);
    EXPECT_EQ(layer1.getName(), layerCopy1->getName());
    EXPECT_EQ(layer1.thickness(), layerCopy1->thickness());
    EXPECT_EQ(layer1.material()->getName(), layerCopy1->material()->getName());

    const Layer* layerCopy2 = mLayerClone->layer(2);
    EXPECT_EQ(layer2.getName(), layerCopy2->getName());
    EXPECT_EQ(layer2.thickness(), layerCopy2->thickness());
    EXPECT_EQ(layer2.material()->getName(), layerCopy2->material()->getName());

    const Layer* layerCopy3 = mLayerClone->layer(3);
    EXPECT_EQ(substrate.getName(), layerCopy3->getName());
    EXPECT_EQ(substrate.thickness(), layerCopy3->thickness());
    EXPECT_EQ(substrate.material()->getName(), layerCopy3->material()->getName());

    //check interfaces
    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(), interface0->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(), interface0->bottomLayer()->material()->getName());

    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.material()->getName(), interface1->topLayer()->material()->getName());
    EXPECT_EQ(layer2.material()->getName(), interface1->bottomLayer()->material()->getName());

    const LayerInterface* interface2 = mLayerClone->layerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.material()->getName(), interface2->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(), interface2->bottomLayer()->material()->getName());

    //top interface
    const LayerInterface* interfaceBottom = mLayerClone->layerTopInterface(1);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(), interfaceBottom->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(), interfaceBottom->bottomLayer()->material()->getName());

    //Bottom interface
    const LayerInterface* interfaceTop = mLayerClone->layerBottomInterface(2);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.material()->getName(), interfaceTop->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(), interfaceTop->bottomLayer()->material()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayerClone->layerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayerClone->layerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);

    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertB)
{
    set_four();

    MultiLayer* mLayerClone = mLayer.cloneInvertB();

    //check properties
    EXPECT_EQ(BornAgain::MultiLayerType, mLayerClone->getName());
    EXPECT_EQ(0.0,mLayerClone->crossCorrLength());
    EXPECT_EQ(size_t(4), mLayerClone->numberOfLayers());
    EXPECT_EQ(size_t(3), mLayerClone->numberOfInterfaces());

    //check layer thickness
    EXPECT_EQ(topLayer.thickness(), mLayerClone->layerThickness(0));
    EXPECT_EQ(layer1.thickness(), mLayerClone->layerThickness(1));
    EXPECT_EQ(layer2.thickness(), mLayerClone->layerThickness(2));
    EXPECT_EQ(substrate.thickness(), mLayerClone->layerThickness(3));

    //check bottomZ value
    EXPECT_EQ(mLayer.layerBottomZ(0), mLayerClone->layerBottomZ(0));
    EXPECT_EQ(mLayer.layerBottomZ(1), mLayerClone->layerBottomZ(1));
    EXPECT_EQ(mLayer.layerBottomZ(2), mLayerClone->layerBottomZ(2));
    EXPECT_EQ(mLayer.layerBottomZ(3), mLayerClone->layerBottomZ(3));

    //check individual layer
    const Layer* layerCopy0 = mLayerClone->layer(0);
    EXPECT_EQ(topLayer.getName(), layerCopy0->getName());
    EXPECT_EQ(topLayer.thickness(), layerCopy0->thickness());
    EXPECT_EQ(topLayer.material()->getName(), layerCopy0->material()->getName());

    const Layer* layerCopy1 = mLayerClone->layer(1);
    EXPECT_EQ(layer1.getName(), layerCopy1->getName());
    EXPECT_EQ(layer1.thickness(), layerCopy1->thickness());
    EXPECT_EQ(layer1.material()->getName(), layerCopy1->material()->getName());

    const Layer* layerCopy2 = mLayerClone->layer(2);
    EXPECT_EQ(layer2.getName(), layerCopy2->getName());
    EXPECT_EQ(layer2.thickness(), layerCopy2->thickness());
    EXPECT_EQ(layer2.material()->getName(), layerCopy2->material()->getName());

    const Layer* layerCopy3 = mLayerClone->layer(3);
    EXPECT_EQ(substrate.getName(), layerCopy3->getName());
    EXPECT_EQ(substrate.thickness(), layerCopy3->thickness());
    EXPECT_EQ(substrate.material()->getName(), layerCopy3->material()->getName());

    //check interfaces
    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    EXPECT_TRUE(nullptr!=interface0);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface0->getName());
    EXPECT_EQ(nullptr, interface0->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(), interface0->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(), interface0->bottomLayer()->material()->getName());

    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    EXPECT_TRUE(nullptr!=interface1);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface1->getName());
    EXPECT_EQ(nullptr, interface1->getRoughness());
    EXPECT_EQ(layer1.material()->getName(), interface1->topLayer()->material()->getName());
    EXPECT_EQ(layer2.material()->getName(), interface1->bottomLayer()->material()->getName());

    const LayerInterface* interface2 = mLayerClone->layerInterface(2);
    EXPECT_TRUE(nullptr!=interface2);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interface2->getName());
    EXPECT_EQ(nullptr, interface2->getRoughness());
    EXPECT_EQ(layer2.material()->getName(), interface2->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(), interface2->bottomLayer()->material()->getName());

    //top interface
    const LayerInterface* interfaceBottom = mLayerClone->layerTopInterface(1);
    EXPECT_TRUE(nullptr!=interfaceBottom);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceBottom->getName());
    EXPECT_EQ(nullptr, interfaceBottom->getRoughness());
    EXPECT_EQ(topLayer.material()->getName(), interfaceBottom->topLayer()->material()->getName());
    EXPECT_EQ(layer1.material()->getName(), interfaceBottom->bottomLayer()->material()->getName());

    //Bottom interface
    const LayerInterface* interfaceTop = mLayerClone->layerBottomInterface(2);
    EXPECT_TRUE(nullptr!=interfaceTop);
    EXPECT_EQ(BornAgain::LayerInterfaceType, interfaceTop->getName());
    EXPECT_EQ(nullptr, interfaceTop->getRoughness());
    EXPECT_EQ(layer2.material()->getName(), interfaceTop->topLayer()->material()->getName());
    EXPECT_EQ(substrate.material()->getName(), interfaceTop->bottomLayer()->material()->getName());

    //null interface
    const LayerInterface* interfaceTopNull = mLayerClone->layerTopInterface(0);
    EXPECT_TRUE(nullptr==interfaceTopNull);

    const LayerInterface* interfaceBottomNull = mLayerClone->layerBottomInterface(3);
    EXPECT_TRUE(nullptr==interfaceBottomNull);

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithRoughness)
{
    //LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness lr(1.1, -7.3, 0.1);
    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1,lr);
    mLayer.addLayer(substrate);

    const LayerInterface* interface0 = mLayer.layerInterface(0);
    const LayerInterface* interface1 = mLayer.layerInterface(1);

    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_TRUE(roughness0);
    EXPECT_EQ(nullptr, roughness1);

    EXPECT_EQ(1.1, roughness0->getSigma());
    EXPECT_EQ(-7.3, roughness0->getHurstParameter());
    EXPECT_EQ(0.1, roughness0->getLatteralCorrLength());
}

TEST_F(MultiLayerTest, CloneWithRoughness)
{
    LayerRoughness lr0(-2.1, 7.3, 12.1);
    LayerRoughness lr1(1.1, -7.3, 0.1);

    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1,lr0);
    mLayer.addLayerWithTopRoughness(substrate,lr1);

    MultiLayer* mLayerClone = mLayer.clone();

    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_TRUE(roughness0);
    EXPECT_TRUE(roughness1);

    EXPECT_EQ( -2.1, roughness0->getSigma());
    EXPECT_EQ(  7.3, roughness0->getHurstParameter());
    EXPECT_EQ( 12.1, roughness0->getLatteralCorrLength());

    EXPECT_EQ(  1.1, roughness1->getSigma());
    EXPECT_EQ( -7.3, roughness1->getHurstParameter());
    EXPECT_EQ(  0.1, roughness1->getLatteralCorrLength());

    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertBWithRoughness)
{
    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(stone, 5*Units::nanometer);

    //LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength);
    LayerRoughness lr0(-2.1, 7.3,  12.1);
    LayerRoughness lr1(1.1, -7.3, 0.1);

    mLayer.addLayer(topLayer);
    mLayer.addLayerWithTopRoughness(layer1,lr0);
    mLayer.addLayerWithTopRoughness(layer2,lr1);

    MultiLayer* mLayerClone = mLayer.cloneInvertB();

    const LayerInterface* interface0 = mLayerClone->layerInterface(0);
    const LayerInterface* interface1 = mLayerClone->layerInterface(1);
    const LayerRoughness* roughness0 = interface0->getRoughness();
    const LayerRoughness* roughness1 = interface1->getRoughness();

    EXPECT_EQ( -2.1, roughness0->getSigma());
    EXPECT_EQ(  7.3, roughness0->getHurstParameter());
    EXPECT_EQ( 12.1, roughness0->getLatteralCorrLength());

    EXPECT_EQ(  1.1, roughness1->getSigma());
    EXPECT_EQ( -7.3, roughness1->getHurstParameter());
    EXPECT_EQ(  0.1, roughness1->getLatteralCorrLength());

    delete mLayerClone;
}

TEST_F(MultiLayerTest, WithMagneticMaterial)
{
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);
    HomogeneousMagneticMaterial magMaterial1("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(stone, 30*Units::nanometer);
    Layer layer3(magMaterial0, 20*Units::nanometer);
    Layer layer4(magMaterial1, 0*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    EXPECT_FALSE(mLayer.containsMagneticMaterial());

    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);
    EXPECT_TRUE(mLayer.containsMagneticMaterial());
}

TEST_F(MultiLayerTest, CloneWithMagneticMaterial)
{
    kvector_t magnetic_field(1.1, 2.1, -5.1);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);
    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);

    MultiLayer* mLayerClone = mLayer.clone();
    EXPECT_TRUE(mLayerClone->containsMagneticMaterial());
    delete mLayerClone;
}

TEST_F(MultiLayerTest, CloneInvertBMagneticMaterial)
{
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);

    Layer layer1(iron, 20*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);

    MultiLayer* mLayerClone = mLayer.cloneInvertB();
    EXPECT_TRUE(mLayerClone->containsMagneticMaterial());
    delete mLayerClone;
}

TEST_F(MultiLayerTest, MultiLayerCompositeTest)
{
    MultiLayer mLayer;
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial magMaterial0("MagMat0", 6e-4, 2e-8, magnetic_field);
    HomogeneousMagneticMaterial magMaterial1("MagMat1", -5.6, 10, magnetic_field);

    Layer layer1(iron, 10*Units::nanometer);
    Layer layer2(magMaterial0, 20*Units::nanometer);
    Layer layer3(magMaterial1, 30*Units::nanometer);
    Layer layer4(stone, 40*Units::nanometer);

    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);

    std::vector<const Layer *> layer_buffer;
    std::vector<const LayerInterface *> interface_buffer;
    int counter(0);

    std::vector<const INode*> children = mLayer.getChildren();
    for(size_t index=0; index<children.size();++index)
    {
        const INode *sample = children[index];
        if(counter%2 == 1)
        {
            const LayerInterface *interface = dynamic_cast<const LayerInterface *>(sample);
            EXPECT_TRUE(nullptr != interface);
            interface_buffer.push_back(interface);
        } else {
            const Layer *layer = dynamic_cast<const Layer *>(sample);
            EXPECT_TRUE(nullptr != layer);
            layer_buffer.push_back(layer);
        }
        counter++;
    }
    EXPECT_EQ( size_t(5), layer_buffer.size());
    EXPECT_EQ( size_t(4), interface_buffer.size());
    for(size_t i=0; i<layer_buffer.size(); ++i) {
        EXPECT_EQ( double(i*10), layer_buffer[i]->thickness());
    }
    for(size_t i=0; i<interface_buffer.size(); ++i) {
        EXPECT_EQ( double((i+1)*10), interface_buffer[i]->bottomLayer()->thickness());
    }
}

TEST_F(MultiLayerTest, MultiLayerZtoIndex)
{
    MultiLayer mLayer;

    // index_0
    // -----------------  0.0
    // index_1
    // -----------------  -10.0
    // index_2
    // -----------------  -30.0
    // index_3
    // -----------------  -60.0
    // index_4
    Layer layer1(air, 10*Units::nanometer);
    Layer layer2(air, 20*Units::nanometer);
    Layer layer3(air, 30*Units::nanometer);
    Layer layer4(air, 0*Units::nanometer);
    mLayer.addLayer(topLayer);
    mLayer.addLayer(layer1);
    mLayer.addLayer(layer2);
    mLayer.addLayer(layer3);
    mLayer.addLayer(layer4);

    EXPECT_EQ(size_t(0), mLayer.bottomZToLayerIndex(1.0));
    EXPECT_EQ(size_t(0), mLayer.bottomZToLayerIndex(0.0));
    EXPECT_EQ(size_t(1), mLayer.bottomZToLayerIndex(-1.0));
    EXPECT_EQ(size_t(1), mLayer.bottomZToLayerIndex(-9.0));
    EXPECT_EQ(size_t(1), mLayer.bottomZToLayerIndex(-10.0));
    EXPECT_EQ(size_t(2), mLayer.bottomZToLayerIndex(-11.0));
    EXPECT_EQ(size_t(2), mLayer.bottomZToLayerIndex(-30.0));
    EXPECT_EQ(size_t(3), mLayer.bottomZToLayerIndex(-31.0));
    EXPECT_EQ(size_t(3), mLayer.bottomZToLayerIndex(-60.0));
    EXPECT_EQ(size_t(4), mLayer.bottomZToLayerIndex(-61.0));
}
