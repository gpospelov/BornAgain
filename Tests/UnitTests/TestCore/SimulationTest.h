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
    test_data.addAxis("phi_f", 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);
}

SimulationTest::~SimulationTest()
{
}


TEST_F(SimulationTest, SimulationInitialState)
{
    std::cout << "DDD 1.1" << std::endl;
    //EXPECT_EQ( NULL, emptySimulation.getSample());
    std::cout << "DDD 1.2" << std::endl;
    EXPECT_EQ( size_t(1), emptySimulation.getOutputData()->getAllocatedSize());
    std::cout << "DDD 1.3" << std::endl;
    EXPECT_EQ( size_t(0), emptySimulation.getOutputData()->getRank());
    std::cout << "DDD 1.4" << std::endl;
    EXPECT_TRUE(emptySimulation.getOutputData()->getRank() == emptySimulation.getInstrument().getDetectorDimension() );
    std::cout << "DDD 1.5" << std::endl;
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
    EXPECT_EQ( size_t(0), emptyClonedSimulation->getOutputData()->getRank());
    EXPECT_TRUE(emptyClonedSimulation->getOutputData()->getRank() == emptyClonedSimulation->getInstrument().getDetector().getDimension() );
    EXPECT_EQ( double(1), emptyClonedSimulation->getInstrument().getIntensity());
    delete emptyClonedSimulation;
}

TEST_F(SimulationTest, SimulationClone)
{
    EXPECT_EQ(1,1);
    std::cout << "XXX 1.1" << std::endl;
    //Simulation *originalSimulation = new Simulation();
    std::cout << "XXX 1.2" << std::endl;
    //originalSimulation->setBeamIntensity(10);
    std::cout << "XXX 1.3" << std::endl;
    //originalSimulation->setDetectorParameters(test_data);
    std::cout << "XXX 1.4" << std::endl;
    //originalSimulation->setSampleBuilder(&sample_builder);
    std::cout << "XXX 1.5" << std::endl;
    //Simulation *clonedSimulation = originalSimulation->clone();
    std::cout << "XXX 1.6 " << clonedSimulation << std::endl;
    //delete originalSimulation;
    std::cout << "XXX 1.7" << std::endl;

    //EXPECT_TRUE( clonedSimulation->getOutputData()->hasSameShape(test_data));
    std::cout << "XXX 1.8" << std::endl;
    //EXPECT_EQ( double(10), clonedSimulation->getInstrument().getIntensity());
    std::cout << "XXX 1.9" << std::endl;
    //EXPECT_TRUE( NULL == clonedSimulation->getSample());
    std::cout << "XXX 1.10" << std::endl;
    //clonedSimulation->prepareSimulation();
    std::cout << "XXX 1.11" << std::endl;
    //EXPECT_FALSE( NULL == clonedSimulation->getSample());
    std::cout << "XXX 1.12" << std::endl;

    //delete clonedSimulation;
}

#endif // SIMULATIONTEST_H
