#ifndef BEAMTEST_H
#define BEAMTEST_H

#include "Beam.h"
#include "Units.h"
#include "ParameterPool.h"
#include "gtest/gtest.h"


class BeamTest : public ::testing::Test
{
 protected:
    BeamTest();
    virtual ~BeamTest();

    Beam emptyBeam;
};


BeamTest::BeamTest()
{

}

BeamTest::~BeamTest()
{

}

TEST_F(BeamTest, BeamInitialState)
{
    EXPECT_DOUBLE_EQ(2.0*Units::PI, emptyBeam.getCentralK()[0]);
    EXPECT_EQ(0.0, emptyBeam.getCentralK()[1]);
    EXPECT_EQ(0.0, emptyBeam.getCentralK()[2]);
    EXPECT_EQ(double(0.0), emptyBeam.getIntensity());
    EXPECT_EQ(size_t(4), emptyBeam.getParameterPool()->size());
    EXPECT_EQ(double(0.0), emptyBeam.getParameterPool()->getParameter("intensity").getValue() );
    EXPECT_EQ(double(1.0), emptyBeam.getParameterPool()->getParameter("wavelength").getValue() );
    EXPECT_EQ(double(0.0), emptyBeam.getParameterPool()->getParameter("alpha").getValue() );
    EXPECT_EQ(double(0.0), emptyBeam.getParameterPool()->getParameter("phi").getValue() );
    EXPECT_EQ(complex_t(0.5,0.0), emptyBeam.getPolarization()(0,0));
    EXPECT_EQ(complex_t(0.5,0.0), emptyBeam.getPolarization()(1,1));
}


TEST_F(BeamTest, BeamAssignment)
{
    kvector_t polarization(0.0, 0.0, 0.2);

    Beam *originalBeam = new Beam();

    originalBeam->setCentralK(1.0, 1.0, 1.0);
    originalBeam->setIntensity(2.0);
    originalBeam->setPolarization(polarization);

    Beam assignedBeam = *originalBeam;
    EXPECT_NEAR(1.83423, assignedBeam.getCentralK()[0], 0.00001);
    EXPECT_NEAR(2.85664, assignedBeam.getCentralK()[1], 0.00001);
    EXPECT_NEAR(-5.28712, assignedBeam.getCentralK()[2], 0.00001);
    EXPECT_EQ(double(2.0), assignedBeam.getIntensity());
    EXPECT_EQ(size_t(4), assignedBeam.getParameterPool()->size());
    EXPECT_EQ(double(2.0), assignedBeam.getParameterPool()->getParameter("intensity").getValue() );
    EXPECT_EQ(complex_t(0.6,0.0), assignedBeam.getPolarization()(0,0));
    EXPECT_EQ(complex_t(0.4,0.0), assignedBeam.getPolarization()(1,1));

    delete originalBeam;
}


#endif // BEAMTEST_H
