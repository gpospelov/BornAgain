#include "google_test.h"
#include "Exceptions.h"
#include "FixedBinAxis.h"
#include "Histogram1D.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "SpecularSimulation.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include <iostream>

class SpecularSimulationTest : public ::testing::Test
{
protected:
    SpecularSimulationTest();
    ~SpecularSimulationTest();
    MultiLayer multilayer;
};

SpecularSimulationTest::SpecularSimulationTest()
{
    Material mat0 = HomogeneousMaterial("ambience", 0.0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", 15e-6, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, 10 * Units::nanometer);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);
}

SpecularSimulationTest::~SpecularSimulationTest() = default;

TEST_F(SpecularSimulationTest, InitialState)
{
    SpecularSimulation sim;
    ASSERT_THROW(sim.runSimulation(), std::runtime_error);
    ASSERT_THROW(sim.getAlphaAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW(sim.getIntensityData(), std::runtime_error);
    ASSERT_THROW(sim.getDetectorIntensity(), std::runtime_error);
}

TEST_F(SpecularSimulationTest, CloneOfEmpty)
{
    SpecularSimulation sim;

    std::unique_ptr<SpecularSimulation> clone(sim.clone());
    ASSERT_THROW(clone->runSimulation(), std::runtime_error);
    ASSERT_THROW(clone->getAlphaAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, clone->sample());
    ASSERT_THROW(clone->getIntensityData(), std::runtime_error);
    ASSERT_THROW(clone->getDetectorIntensity(), std::runtime_error);
}

TEST_F(SpecularSimulationTest, SetBeamParameters)
{
    SpecularSimulation sim;

    VariableBinAxis axis("axis", 2, std::vector<double>{1.0, 2.0, 3.0});
    sim.setBeamParameters(1.0, axis);
    EXPECT_EQ(2u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(3.0, sim.getAlphaAxis()->getMax());

    sim.setBeamParameters(1.0, 10, 1.0 * Units::degree, 10.0 * Units::degree);
    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());

    EXPECT_THROW(sim.setBeamParameters(1.0, 10, -2.0, 3.0),
                 Exceptions::ClassInitializationException);
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0 * Units::degree, 2.0 * Units::degree);
    sim.setSample(multilayer);
    EXPECT_EQ(3u, sim.sample()->numberOfLayers());

    ASSERT_THROW(sim.getIntensityData(), std::runtime_error);

    sim.runSimulation();

    const std::unique_ptr<Histogram1D> reflectivity(sim.getIntensityData());
    EXPECT_EQ(10u, reflectivity->getTotalNumberOfBins());
    EXPECT_EQ(1u, reflectivity->getRank());
    EXPECT_EQ(0.0, reflectivity->getXaxis().getMin());
    EXPECT_EQ(2.0 * Units::degree, reflectivity->getXaxis().getMax());

    const std::unique_ptr<OutputData<double>> output(sim.getDetectorIntensity());
    EXPECT_EQ(reflectivity->getTotalNumberOfBins(), output->getAllocatedSize());
    EXPECT_EQ(reflectivity->getRank(), output->getRank());
    EXPECT_EQ(reflectivity->getXaxis().getMin(), output->getAxis(0).getMin());
    EXPECT_EQ(reflectivity->getXaxis().getMax(), output->getAxis(0).getMax());
    EXPECT_DOUBLE_EQ(reflectivity->getBinValues()[5], (*output)[5]);
}

TEST_F(SpecularSimulationTest, SimulationClone)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0 * Units::degree, 2.0 * Units::degree);
    sim.setSample(multilayer);

    std::unique_ptr<SpecularSimulation> clone(sim.clone());

    EXPECT_EQ(3u, clone->sample()->numberOfLayers());

    ASSERT_THROW(clone->getIntensityData(), std::runtime_error);
    ASSERT_THROW(clone->getDetectorIntensity(), std::runtime_error);

    sim.runSimulation();

    std::unique_ptr<SpecularSimulation> clone2(sim.clone());

    std::unique_ptr<Histogram1D> output(clone2->getIntensityData());
    EXPECT_EQ(10u, output->getTotalNumberOfBins());

    const std::unique_ptr<OutputData<double>> output_data(clone2->getDetectorIntensity());
    EXPECT_EQ(10u, output_data->getAllocatedSize());
}
