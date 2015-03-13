#ifndef ATTLIMITSTEST_H
#define ATTLIMITSTEST_H

#include "AttLimits.h"
#include <limits>

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

    //set limit [-1.0, 10.0[
    attLimits.setLimits(-1.0,10.0);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_TRUE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    EXPECT_EQ(-1.0,attLimits.getLowerLimit());
    EXPECT_EQ(10.0,attLimits.getUpperLimit());

    EXPECT_FALSE(attLimits.isInRange(-2.0));
    EXPECT_TRUE(attLimits.isInRange(-1.0));
    EXPECT_TRUE(attLimits.isInRange(0.0));
    EXPECT_TRUE(attLimits.isInRange(9.0));
    EXPECT_FALSE(attLimits.isInRange(10.0));
    EXPECT_FALSE(attLimits.isInRange(20.0));

    // [inf, -10.0[
    attLimits.removeLowerLimit();
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_EQ(0.0,attLimits.getLowerLimit());

    EXPECT_TRUE(attLimits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(attLimits.isInRange(-2.0));
    EXPECT_TRUE(attLimits.isInRange(9.0));
    EXPECT_FALSE(attLimits.isInRange(10.0));
    EXPECT_FALSE(attLimits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, -10.0[
    attLimits.setLowerLimit(2.1);
    EXPECT_TRUE(attLimits.hasLowerLimit());
    EXPECT_EQ(2.1,attLimits.getLowerLimit());

    EXPECT_FALSE(attLimits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(attLimits.isInRange(2.0));
    EXPECT_TRUE(attLimits.isInRange(2.1));

    //[2.1, inf]
    attLimits.removeUpperLimit();
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_EQ(0.0,attLimits.getUpperLimit());

    EXPECT_FALSE(attLimits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(attLimits.isInRange(2.0));
    EXPECT_TRUE(attLimits.isInRange(2.1));
    EXPECT_TRUE(attLimits.isInRange(20.0));
    EXPECT_TRUE(attLimits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, 2.2[
    attLimits.setUpperLimit(2.2);
    EXPECT_TRUE(attLimits.hasUpperLimit());
    EXPECT_EQ(2.2,attLimits.getUpperLimit());
    EXPECT_TRUE(attLimits.hasLowerAndUpperLimits());
    EXPECT_TRUE(attLimits.isInRange(2.15));
    EXPECT_FALSE(attLimits.isInRange(2.2));

    //remove limit
    attLimits.removeLimits();
    EXPECT_FALSE(attLimits.hasLowerLimit());
    EXPECT_FALSE(attLimits.hasUpperLimit());
    EXPECT_FALSE(attLimits.hasLowerAndUpperLimits());
    EXPECT_FALSE(attLimits.isFixed());

    EXPECT_TRUE(attLimits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(attLimits.isInRange(std::numeric_limits<double>::infinity()));

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

TEST_F(AttLimitsTest, ComparisonOperators)
{
    AttLimits lim1 = AttLimits::limited(1.0, 2.0);
    AttLimits lim2 = AttLimits::limited(1.0, 2.0);
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    AttLimits lim3 = AttLimits::limitless();
    AttLimits lim4 = AttLimits::limitless();
    EXPECT_TRUE(lim3 == lim4);
    EXPECT_FALSE(lim3 != lim4);

    AttLimits lim5 = AttLimits::lowerLimited(1.0);
    AttLimits lim6 = AttLimits::lowerLimited(1.0);
    EXPECT_TRUE(lim5 == lim6);
    EXPECT_FALSE(lim5 != lim6);

    AttLimits lim7 = AttLimits::upperLimited(1.0);
    AttLimits lim8 = AttLimits::upperLimited(1.0);
    EXPECT_TRUE(lim7 == lim8);
    EXPECT_FALSE(lim7 != lim8);
}

TEST_F(AttLimitsTest, CopyConstructor)
{
    AttLimits lim1 = AttLimits::limited(1.0, 2.0);
    AttLimits lim2 = lim1;
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    AttLimits lim3(lim1);
    EXPECT_TRUE(lim1 == lim3);
    EXPECT_FALSE(lim1 != lim3);
}

#endif // ATTLIMITSTEST_H
