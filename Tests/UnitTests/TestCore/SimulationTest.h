#ifndef SIMULATIONTEST_H
#define SIMULATIONTEST_H

#include "Simulation.h"
#include "OutputData.h"
#include "Beam.h"
#include "MultiLayer.h"
#include "ISampleBuilder.h"


#include <cmath>
#include "gtest/gtest.h"


class SimulationTest : public ::testing::Test
{
protected:
    SimulationTest();
    virtual ~SimulationTest();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        virtual ISample *buildSample() const { return new Layer(); }
    };

    Simulation emptySimulation;
    Simulation constructedSimulation;
    OutputData<double> test_data;
    SampleBuilder sample_builder;
};


SimulationTest::SimulationTest()
{
    test_data.addAxis(NDetector2d::PHI_AXIS_NAME, 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);

}

SimulationTest::~SimulationTest()
{

}


TEST_F(SimulationTest, SimulationInitialState)
{
    EXPECT_EQ( NULL, emptySimulation.getSample());
    EXPECT_EQ( size_t(1), emptySimulation.getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptySimulation.getOutputData()->getNdimensions());
    EXPECT_TRUE(emptySimulation.getOutputData()->getNdimensions() == emptySimulation.getInstrument().getDetectorDimension() );
}


TEST_F(SimulationTest, SimulationConstruction)
{
    EXPECT_FALSE( constructedSimulation.getOutputData()->hasSameShape(test_data));
    constructedSimulation.setDetectorParameters(test_data);
    EXPECT_TRUE( constructedSimulation.getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(0), constructedSimulation.getOutputData()->totalSum());

    constructedSimulation.normalize();
    EXPECT_EQ( double(0), constructedSimulation.getOutputData()->totalSum());

    MultiLayer ml;
    Layer layer;
    ml.addLayer(layer);
    constructedSimulation.setSample(ml);
    EXPECT_EQ( size_t(1), dynamic_cast<MultiLayer *>(constructedSimulation.getSample())->getNumberOfLayers());
    constructedSimulation.setSampleBuilder(&sample_builder);
    EXPECT_EQ( NULL, constructedSimulation.getSample());
    constructedSimulation.prepareSimulation();

    EXPECT_FALSE( NULL == constructedSimulation.getSample());
    EXPECT_EQ( std::string("Layer"), constructedSimulation.getSample()->getName());
    EXPECT_EQ( double(0), dynamic_cast<Layer *>(constructedSimulation.getSample())->getThickness());
}

TEST_F(SimulationTest, SimulationInitialStateOfClone)
{
    Simulation *emptyClonedSimulation = emptySimulation.clone();
    EXPECT_EQ( NULL, emptyClonedSimulation->getSample());
    EXPECT_EQ( size_t(1), emptyClonedSimulation->getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptyClonedSimulation->getOutputData()->getNdimensions());
    EXPECT_TRUE(emptyClonedSimulation->getOutputData()->getNdimensions() == emptyClonedSimulation->getInstrument().getDetector().getDimension() );
    EXPECT_EQ( double(1), emptyClonedSimulation->getInstrument().getIntensity());
    delete emptyClonedSimulation;
}

TEST_F(SimulationTest, SimulationClone)
{
    Simulation *originalSimulation = new Simulation();
    originalSimulation->setBeamIntensity(10);
    originalSimulation->setDetectorParameters(test_data);
    originalSimulation->setSampleBuilder(&sample_builder);
    Simulation *clonedSimulation = originalSimulation->clone();
    delete originalSimulation;

    EXPECT_TRUE( clonedSimulation->getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(10), clonedSimulation->getInstrument().getIntensity());
    EXPECT_TRUE( NULL == clonedSimulation->getSample());
    clonedSimulation->prepareSimulation();
    EXPECT_FALSE( NULL == clonedSimulation->getSample());

    delete clonedSimulation;
}


#endif // SIMULATIONTEST_H
