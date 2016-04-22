#ifndef GISASSIMULATIONTEST_H
#define GISASSIMULATIONTEST_H

#include "GISASSimulation.h"
#include "OutputData.h"
#include "Beam.h"
#include "MultiLayer.h"
#include "ISampleBuilder.h"
#include "BornAgainNamespace.h"

#include <memory>
#include <cmath>


class GISASSimulationTest : public ::testing::Test
{
 protected:
    GISASSimulationTest();
    virtual ~GISASSimulationTest();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        virtual ISample *buildSample() const { return new Layer(); }
    };

    std::shared_ptr<class ISampleBuilder> sample_builder;

    GISASSimulation emptySimulation;
    GISASSimulation constructedSimulation;
    OutputData<double> test_data;
};


GISASSimulationTest::GISASSimulationTest()
    : sample_builder(new SampleBuilder)
{
    test_data.addAxis(BornAgain::PHI_AXIS_NAME, 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);
}

GISASSimulationTest::~GISASSimulationTest()
{
}


TEST_F(GISASSimulationTest, SimulationInitialState)
{
    EXPECT_EQ( nullptr, emptySimulation.getSample());
    EXPECT_EQ( size_t(1), emptySimulation.getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptySimulation.getOutputData()->getRank());
    EXPECT_TRUE(emptySimulation.getOutputData()->getRank() == emptySimulation.getInstrument().getDetectorDimension() );
    EXPECT_EQ(nullptr, emptySimulation.getSampleBuilder().get());
}


TEST_F(GISASSimulationTest, SimulationConstruction)
{
    EXPECT_FALSE( constructedSimulation.getOutputData()->hasSameShape(test_data));
    constructedSimulation.setDetectorParameters(test_data);
    EXPECT_TRUE( constructedSimulation.getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(0), constructedSimulation.getOutputData()->totalSum());

    MultiLayer ml;
    Layer layer;
    ml.addLayer(layer);
    constructedSimulation.setSample(ml);
    EXPECT_EQ( size_t(1), dynamic_cast<MultiLayer *>(constructedSimulation.getSample())->getNumberOfLayers());
    constructedSimulation.setSampleBuilder(sample_builder);
    EXPECT_EQ( nullptr, constructedSimulation.getSample());
    EXPECT_EQ( sample_builder.get(), constructedSimulation.getSampleBuilder().get());

    constructedSimulation.prepareSimulation();

    EXPECT_TRUE( nullptr == constructedSimulation.getSample());
    std::unique_ptr<ISample> sample(constructedSimulation.getSampleBuilder()->buildSample());
    EXPECT_EQ( std::string("Layer"), sample->getName());
    EXPECT_EQ( double(0), dynamic_cast<Layer *>(sample.get())->getThickness());
}

TEST_F(GISASSimulationTest, SimulationInitialStateOfClone)
{
    GISASSimulation *emptyClonedSimulation = emptySimulation.clone();
    EXPECT_EQ( nullptr, emptyClonedSimulation->getSample());
    EXPECT_EQ( size_t(1), emptyClonedSimulation->getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptyClonedSimulation->getOutputData()->getRank());
    EXPECT_TRUE(emptyClonedSimulation->getOutputData()->getRank() == emptyClonedSimulation->getInstrument().getDetector()->getDimension() );
    EXPECT_EQ( 0.0, emptyClonedSimulation->getInstrument().getBeamIntensity());
    delete emptyClonedSimulation;
}

TEST_F(GISASSimulationTest, SimulationClone)
{
    EXPECT_EQ(1,1);
    GISASSimulation *originalSimulation = new GISASSimulation();
    originalSimulation->setBeamIntensity(10);
    originalSimulation->setDetectorParameters(test_data);
    originalSimulation->setSampleBuilder(sample_builder);
    GISASSimulation *clonedSimulation = originalSimulation->clone();
    delete originalSimulation;

    EXPECT_TRUE( clonedSimulation->getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(10), clonedSimulation->getInstrument().getBeamIntensity());
    EXPECT_TRUE( nullptr == clonedSimulation->getSample());
    clonedSimulation->prepareSimulation();
    EXPECT_TRUE( nullptr == clonedSimulation->getSample());

    delete clonedSimulation;
}

#endif // GISASSIMULATIONTEST_H
