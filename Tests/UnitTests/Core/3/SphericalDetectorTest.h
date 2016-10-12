#ifndef SPHERICALDETECTORTEST_H
#define SPHERICALDETECTORTEST_H

#include "SphericalDetector.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "FixedBinAxis.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "Polygon.h"
#include "BornAgainNamespace.h"
#include <memory>

class SphericalDetectorTest : public ::testing::Test
{
 protected:
    SphericalDetectorTest();
    virtual ~SphericalDetectorTest();

    SphericalDetector *originalDetector;
    SphericalDetector copyOfOriginalDetector;
};

SphericalDetectorTest::SphericalDetectorTest()
{
    originalDetector = new SphericalDetector();
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    originalDetector->addAxis(axis0);
    originalDetector->addAxis(axis1);
    originalDetector->setDetectorResolution(new ConvolutionDetectorResolution(
            new ResolutionFunction2DGaussian(1,1)));
}

SphericalDetectorTest::~SphericalDetectorTest()
{
    delete originalDetector;
}

//! Default detector construction

TEST_F(SphericalDetectorTest, initialState)
{
    SphericalDetector detector;

    // checking size
    EXPECT_EQ((size_t)0, detector.getDimension());
    EXPECT_EQ(IDetector2D::RADIANS, detector.getDefaultAxesUnits());

    // detector units
    std::vector<IDetector2D::EAxesUnits> validUnits =
        {IDetector2D::NBINS, IDetector2D::RADIANS, IDetector2D::DEGREES, IDetector2D::QYQZ};
    EXPECT_EQ(validUnits, detector.getValidAxesUnits());

    // masks
    EXPECT_FALSE(detector.hasMasks());
    EXPECT_EQ(0, detector.getNumberOfMaskedChannels());

    // resolution function
    EXPECT_EQ(nullptr, detector.getDetectorResolutionFunction());

    // behavior
    ASSERT_THROW(detector.getAxis(0), Exceptions::OutOfBoundsException);
    OutputData<double>* p_intensity_map(nullptr);
    ASSERT_THROW(detector.applyDetectorResolution(p_intensity_map),
                 Exceptions::NullPointerException);
}

//! Construction of the detector with axes.

TEST_F(SphericalDetectorTest, constructionWithAxes)
{
    SphericalDetector detector;
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    detector.addAxis(axis0);
    detector.addAxis(axis1);

    // checking dimension and axes
    EXPECT_EQ((size_t)2, detector.getDimension());
    EXPECT_EQ(axis0.getMin(), detector.getAxis(0).getMin() );
    EXPECT_EQ(axis0.getMax(), detector.getAxis(0).getMax() );
    EXPECT_EQ(axis0.getName(), detector.getAxis(0).getName() );
    EXPECT_EQ(axis1.getName(), detector.getAxis(1).getName() );
    EXPECT_EQ(axis1.getMin(), detector.getAxis(1).getMin() );
    EXPECT_EQ(axis1.getMax(), detector.getAxis(1).getMax() );

    // clearing detector
    detector.clear();
    EXPECT_EQ((size_t)0, detector.getDimension());
}

//! Construction of the detector via classical constructor.

TEST_F(SphericalDetectorTest, constructionWithParameters)
{
    SphericalDetector detector(10, -1.0, 1.0, 20, 0.0, 2.0);
    EXPECT_EQ(10, detector.getAxis(0).getSize() );
    EXPECT_EQ(-1.0, detector.getAxis(0).getMin() );
    EXPECT_EQ(1.0, detector.getAxis(0).getMax() );
    EXPECT_EQ(BornAgain::PHI_AXIS_NAME, detector.getAxis(0).getName());
    EXPECT_EQ(20, detector.getAxis(1).getSize() );
    EXPECT_EQ(0.0, detector.getAxis(1).getMin() );
    EXPECT_EQ(2.0, detector.getAxis(1).getMax() );
    EXPECT_EQ(BornAgain::ALPHA_AXIS_NAME, detector.getAxis(1).getName());
}

//! Init external data with detector axes

TEST_F(SphericalDetectorTest, initOutputData)
{
    SphericalDetector detector(10, -1.0, 1.0, 20, 0.0, 2.0);
    OutputData<double> data;
    detector.initOutputData(data);

    EXPECT_EQ(data.getAllocatedSize(), 200);

    EXPECT_EQ(10, data.getAxis(0)->getSize() );
    EXPECT_EQ(-1.0, data.getAxis(0)->getMin() );
    EXPECT_EQ(1.0, data.getAxis(0)->getMax() );
    EXPECT_EQ(BornAgain::PHI_AXIS_NAME, data.getAxis(0)->getName());
    EXPECT_EQ(20, data.getAxis(1)->getSize() );
    EXPECT_EQ(0.0, data.getAxis(1)->getMin() );
    EXPECT_EQ(2.0, data.getAxis(1)->getMax() );
    EXPECT_EQ(BornAgain::ALPHA_AXIS_NAME, data.getAxis(1)->getName());
}


TEST_F(SphericalDetectorTest, DetectorCopying)
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

TEST_F(SphericalDetectorTest, MaskOfDetector)
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

#endif // SPHERICALDETECTORTEST_H
