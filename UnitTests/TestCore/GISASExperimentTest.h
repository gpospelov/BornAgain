#ifndef GISASEXPERIMENTTEST_H
#define GISASEXPERIMENTTEST_H

#include "GISASExperiment.h"
#include "OutputData.h"
#include "Beam.h"
#include "MultiLayer.h"
#include "ISampleBuilder.h"


#include <cmath>
#include "gtest/gtest.h"


class GISASExperimentTest : public ::testing::Test
{
protected:
    GISASExperimentTest();
    virtual ~GISASExperimentTest();

    class SampleBuilder : public ISampleBuilder
    {
    public:
        virtual ISample *buildSample() const { return new Layer(); }
    };
    GISASExperiment emptyExperiment;
    GISASExperiment constructedExperiment;
    OutputData<double> test_data;
    SampleBuilder sample_builder;
};


GISASExperimentTest::GISASExperimentTest()
{
    test_data.addAxis("phi_f", 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);

}

GISASExperimentTest::~GISASExperimentTest()
{

}


TEST_F(GISASExperimentTest, GISASExperimentInitialState)
{
    EXPECT_EQ( NULL, emptyExperiment.getSample());
    EXPECT_EQ( size_t(10000), emptyExperiment.getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(2), emptyExperiment.getOutputData()->getNdimensions());
    EXPECT_TRUE(emptyExperiment.getOutputData()->getNdimensions() == emptyExperiment.getDetector().getDimension() );
    EXPECT_TRUE(std::string("phi_f") == emptyExperiment.getDetector().getAxis(0).getName());
    EXPECT_TRUE(std::string("alpha_f") == emptyExperiment.getDetector().getAxis(1).getName());
}


TEST_F(GISASExperimentTest, GISASExperimentInitialStateOfClone)
{
    GISASExperiment *emptyClonedExperiment = emptyExperiment.clone();
    EXPECT_EQ( NULL, emptyClonedExperiment->getSample());
    EXPECT_EQ( size_t(10000), emptyClonedExperiment->getOutputData()->getAllocatedSize());
    EXPECT_EQ( size_t(2), emptyClonedExperiment->getOutputData()->getNdimensions());
    EXPECT_TRUE(emptyClonedExperiment->getOutputData()->getNdimensions() == emptyClonedExperiment->getDetector().getDimension() );
    EXPECT_EQ( double(1), emptyClonedExperiment->getBeam().getIntensity());
    delete emptyClonedExperiment;
}

TEST_F(GISASExperimentTest, GISASExperimentClone)
{
    GISASExperiment *originalExperiment = new GISASExperiment();
    originalExperiment->setBeamIntensity(10);
    originalExperiment->setDetectorParameters(test_data);
    originalExperiment->setSampleBuilder(&sample_builder);
    GISASExperiment *clonedExperiment = originalExperiment->clone();
    delete originalExperiment;

    EXPECT_TRUE( clonedExperiment->getOutputData()->hasSameShape(test_data));
    EXPECT_EQ( double(10), clonedExperiment->getBeam().getIntensity());
    EXPECT_TRUE( NULL == clonedExperiment->getSample());

    delete clonedExperiment;

}


#endif // GISASEXPERIMENTTEST_H
