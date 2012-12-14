#ifndef EXPERIMENTTEST_H
#define EXPERIMENTTEST_H

#include "Experiment.h"
#include "OutputData.h"
#include "Beam.h"
#include "MultiLayer.h"
#include "ISampleBuilder.h"


#include <cmath>
#include "gtest/gtest.h"


class ExperimentTest : public ::testing::Test
{
protected:
    ExperimentTest();
    virtual ~ExperimentTest();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        virtual ISample *buildSample() const { return new Layer(); }
    };

    Experiment emptyExperiment;
    Experiment constructedExperiment;
    OutputData<double> test_data;
    SampleBuilder sample_builder;
};


ExperimentTest::ExperimentTest()
{
    test_data.addAxis(NDetector2d::PHI_AXIS_NAME, 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);

}

ExperimentTest::~ExperimentTest()
{

}


TEST_F(ExperimentTest, ExperimentInitialState)
{
    EXPECT_EQ( NULL, emptyExperiment.getSample());
    EXPECT_EQ( size_t(1), emptyExperiment.getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptyExperiment.getOutputData()->getNdimensions());
    EXPECT_TRUE(emptyExperiment.getOutputData()->getNdimensions() == emptyExperiment.getDetector().getDimension() );
    EXPECT_EQ( double(1), emptyExperiment.getBeam().getIntensity());
}


TEST_F(ExperimentTest, ExperimentConstruction)
{
    double lambda(1), alpha(1), phi(1);
    double k = 2.*M_PI/lambda;
    double x = k*std::cos(alpha) * std::cos(phi);
    double y = k*std::cos(alpha) * std::sin(phi);
    double z = k*std::sin(alpha);
    constructedExperiment.setBeamParameters(lambda, alpha, phi);
    EXPECT_DOUBLE_EQ(x, constructedExperiment.getBeam().getCentralK().x().real() );
    EXPECT_DOUBLE_EQ(0, constructedExperiment.getBeam().getCentralK().x().imag() );
    EXPECT_DOUBLE_EQ(y, constructedExperiment.getBeam().getCentralK().y().real() );
    EXPECT_DOUBLE_EQ(0, constructedExperiment.getBeam().getCentralK().y().imag() );
    EXPECT_DOUBLE_EQ(z, constructedExperiment.getBeam().getCentralK().z().real() );
    EXPECT_DOUBLE_EQ(0, constructedExperiment.getBeam().getCentralK().z().imag() );

    EXPECT_FALSE( constructedExperiment.getOutputData()->hasSameShape(test_data));
    constructedExperiment.setDetectorParameters(test_data);
    EXPECT_TRUE( constructedExperiment.getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(0), constructedExperiment.getOutputData()->totalSum());

    constructedExperiment.setBeamIntensity(10);
    EXPECT_EQ( double(10), constructedExperiment.getBeam().getIntensity());
    constructedExperiment.normalize();
    EXPECT_EQ( double(0), constructedExperiment.getOutputData()->totalSum());

    MultiLayer ml;
    Layer layer;
    ml.addLayer(layer);
    constructedExperiment.setSample(ml);
    EXPECT_EQ( size_t(1), dynamic_cast<MultiLayer *>(constructedExperiment.getSample())->getNumberOfLayers());
    constructedExperiment.setSampleBuilder(&sample_builder);
    EXPECT_EQ( NULL, constructedExperiment.getSample());
    constructedExperiment.runSimulation();
    EXPECT_FALSE( NULL == constructedExperiment.getSample());
    EXPECT_EQ( std::string("Layer"), constructedExperiment.getSample()->getName());
    EXPECT_EQ( double(0), dynamic_cast<Layer *>(constructedExperiment.getSample())->getThickness());
}

TEST_F(ExperimentTest, ExperimentInitialStateOfClone)
{
    Experiment *emptyClonedExperiment = emptyExperiment.clone();
    EXPECT_EQ( NULL, emptyClonedExperiment->getSample());
    EXPECT_EQ( size_t(1), emptyClonedExperiment->getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(0), emptyClonedExperiment->getOutputData()->getNdimensions());
    EXPECT_TRUE(emptyClonedExperiment->getOutputData()->getNdimensions() == emptyClonedExperiment->getDetector().getDimension() );
    EXPECT_EQ( double(1), emptyClonedExperiment->getBeam().getIntensity());
    delete emptyClonedExperiment;
}

TEST_F(ExperimentTest, ExperimentClone)
{
    Experiment *originalExperiment = new Experiment();
    originalExperiment->setBeamIntensity(10);
    originalExperiment->setDetectorParameters(test_data);
    originalExperiment->setSampleBuilder(&sample_builder);
    Experiment *clonedExperiment = originalExperiment->clone();
    delete originalExperiment;

    EXPECT_TRUE( clonedExperiment->getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(10), clonedExperiment->getBeam().getIntensity());
    EXPECT_TRUE( NULL == clonedExperiment->getSample());
    clonedExperiment->runSimulation();
    EXPECT_FALSE( NULL == clonedExperiment->getSample());

    delete clonedExperiment;


}


#endif // EXPERIMENTTEST_H
