#ifndef DETECTORTEST_H
#define DETECTORTEST_H

#include "SphericalDetector.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "FixedBinAxis.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "Polygon.h"
#include <memory>

class DetectorTest : public ::testing::Test
{
 protected:
    DetectorTest();
    virtual ~DetectorTest();

    SphericalDetector emptyDetector;
    SphericalDetector constructedDetector;
    SphericalDetector *originalDetector;
    SphericalDetector copyOfOriginalDetector;
};

DetectorTest::DetectorTest()
{
    originalDetector = new SphericalDetector();
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
    OutputData<double>* p_intensity_map(nullptr);
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

TEST_F(DetectorTest, MaskOfDetector)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};

    Geometry::Polygon polygon(x, y);
    detector.addMask(polygon, true);

    const OutputData<bool> *mask = detector.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector.isMasked(index));
        } else {
            EXPECT_FALSE(detector.isMasked(index));
        }
    }

    SphericalDetector detector2 = detector;
    mask = detector2.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector2.isMasked(index));
        } else {
            EXPECT_FALSE(detector2.isMasked(index));
        }
    }

    mask = detector.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector.isMasked(index));
        } else {
            EXPECT_FALSE(detector.isMasked(index));
        }
    }
}

#endif // DETECTORTEST_H
