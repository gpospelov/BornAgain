#ifndef DETECTORTEST_H
#define DETECTORTEST_H


#include "Detector.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "FixedBinAxis.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"

#include "gtest/gtest.h"


class DetectorTest : public ::testing::Test
{
 protected:
    DetectorTest();
    virtual ~DetectorTest();

    Detector emptyDetector;
    Detector constructedDetector;
    Detector *originalDetector;
    Detector copyOfOriginalDetector;
};

DetectorTest::DetectorTest()
{
    originalDetector = new Detector();
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    originalDetector->addAxis(axis0);
    originalDetector->addAxis(axis1);
    originalDetector->setDetectorResolution(new ConvolutionDetectorResolution(
            new ResolutionFunction2DGaussian(1,1)));
}

DetectorTest::~DetectorTest()
{
    delete originalDetector;
}

TEST_F(DetectorTest, InitialDetectorState)
{
    EXPECT_EQ((size_t)0, emptyDetector.getDimension());
    ASSERT_THROW(emptyDetector.getAxis(0), OutOfBoundsException);
    OutputData<double>* p_intensity_map(0);
    ASSERT_THROW(emptyDetector.applyDetectorResolution(p_intensity_map),
            NullPointerException);
}

TEST_F(DetectorTest, DetectorConstruction)
{
    // pushing two axes
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    constructedDetector.addAxis(axis0);
    constructedDetector.addAxis(axis1);

    EXPECT_EQ((size_t)2, constructedDetector.getDimension());
    const IAxis& axis0copy = constructedDetector.getAxis(0);
    const IAxis& axis1copy = constructedDetector.getAxis(1);
    ASSERT_TRUE(axis0.getMin() == axis0copy.getMin() );
    ASSERT_TRUE(axis0.getMax() == axis0copy.getMax() );
    ASSERT_TRUE(axis0.getName() == axis0copy.getName() );
    ASSERT_TRUE(axis1.getName() == axis1copy.getName() );
    ASSERT_TRUE(axis1.getMin() == axis1copy.getMin() );
    ASSERT_TRUE(axis1.getMax() == axis1copy.getMax() );
    constructedDetector.clear();
    EXPECT_EQ((size_t)0, constructedDetector.getDimension());
}

TEST_F(DetectorTest, DetectorCopying)
{
    copyOfOriginalDetector = *originalDetector;
    delete originalDetector;
    originalDetector = 0;
    ASSERT_TRUE( copyOfOriginalDetector.getDimension() == 2 );
    EXPECT_EQ( (double)0, copyOfOriginalDetector.getAxis(0).getMin() );
    EXPECT_EQ( (double)10, copyOfOriginalDetector.getAxis(0).getMax() );
    EXPECT_EQ( (size_t)10, copyOfOriginalDetector.getAxis(0).getSize() );
    EXPECT_EQ( (double)0, copyOfOriginalDetector.getAxis(1).getMin() );
    EXPECT_EQ( (double)20, copyOfOriginalDetector.getAxis(1).getMax() );
    EXPECT_EQ( (size_t)20, copyOfOriginalDetector.getAxis(1).getSize() );
    EXPECT_TRUE(std::string("ConvolutionDetectorResolution")
        == copyOfOriginalDetector.getDetectorResolutionFunction()->getName());
}

#endif // DETECTORTEST_H
