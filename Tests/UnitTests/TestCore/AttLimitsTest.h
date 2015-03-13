#ifndef ATTLIMITSTEST_H
#define ATTLIMITSTEST_H

#include "AttLimits.h"

#include "gtest/gtest.h"


class AttLimitsTest : public ::testing::Test
{
 protected:
    AttLimitsTest(){}
    virtual ~AttLimitsTest(){}

};



TEST_F(AttLimitsTest, AttLimitsInitial)
{
    AttLimits attLimits;

    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());
}

TEST_F(AttLimitsTest, AttLimitsSetLimit)
{
    AttLimits attLimits;

    //set limit
    attLimits.setLimits(-1.0,10.0);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_TRUE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    //lower limit
    EXPECT_EQ(-1.0,attLimits.getLowerLimit());

    attLimits.removeLowerLimit();
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_EQ(0.0,attLimits.getLowerLimit());

    attLimits.setLowerLimit(2.1);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_EQ(2.1,attLimits.getLowerLimit());

    //upper limit
    EXPECT_EQ(10.0,attLimits.getUpperLimit());

    attLimits.removeUpperLimit();
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_EQ(0.0,attLimits.getUpperLimit());

    attLimits.setUpperLimit(2.2);
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_EQ(2.2,attLimits.getUpperLimit());

    EXPECT_TRUE(attLimits.hasLowerAndUpperLimits());

    //remove limit
    attLimits.removeLimits();
    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

}

TEST_F(AttLimitsTest, AttLimitsLowerLimited)
{
    AttLimits attLimits = AttLimits::lowerLimited(5.0);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    EXPECT_EQ(5.0,attLimits.getLowerLimit());
    EXPECT_EQ(0.0,attLimits.getUpperLimit());
}

TEST_F(AttLimitsTest, AttLimitsUpperLimited)
{
    AttLimits attLimits = AttLimits::upperLimited(5.0);
    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    EXPECT_EQ(0.0,attLimits.getLowerLimit());
    EXPECT_EQ(5.0,attLimits.getUpperLimit());
}

TEST_F(AttLimitsTest, AttLimitsLimited)
{
    AttLimits attLimits = AttLimits::limited(-10.0, 2.0);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_TRUE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    EXPECT_EQ(-10.0,attLimits.getLowerLimit());
    EXPECT_EQ(2.0,attLimits.getUpperLimit());
}

TEST_F(AttLimitsTest, AttLimitsLimitless)
{
    AttLimits attLimits = AttLimits::limitless();

    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());
}

TEST_F(AttLimitsTest, AttLimitsFixed)
{
    AttLimits attLimits = AttLimits::fixed();

    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_TRUE(attLimits.isFixed());

    EXPECT_EQ(0.0,attLimits.getLowerLimit());
    EXPECT_EQ(0.0,attLimits.getUpperLimit());

    attLimits.setFixed(false);
    EXPECT_FALSE(attLimits.isFixed());
}


#endif // ATTLIMITSTEST_H
