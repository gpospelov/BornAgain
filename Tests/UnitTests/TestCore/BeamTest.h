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
    EXPECT_EQ(double(1), emptyBeam.getIntensity());
    EXPECT_EQ(complex_t(0,0), emptyBeam.getCentralK()[0]);
    EXPECT_EQ(complex_t(0,0), emptyBeam.getCentralK()[1]);
    EXPECT_EQ(complex_t(0,0), emptyBeam.getCentralK()[2]);
    EXPECT_EQ(size_t(1), emptyBeam.getParameterPool()->size());
    EXPECT_EQ(double(1), emptyBeam.getParameterPool()->getParameter("intensity").getValue() );
}

#include <iostream>

TEST_F(BeamTest, BeamAssignment)
{
    Beam *originalBeam = new Beam();
    originalBeam->setIntensity(2);
    Beam assignedBeam = *originalBeam;
    EXPECT_TRUE(assignedBeam.getName() == originalBeam->getName());
    EXPECT_TRUE(assignedBeam.getIntensity() == originalBeam->getIntensity());
    delete originalBeam;
    EXPECT_EQ(double(2), assignedBeam.getParameterPool()->getParameter("intensity").getValue() );
}




#endif // BEAMTEST_H
