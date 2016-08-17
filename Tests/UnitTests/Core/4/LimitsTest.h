#ifndef LIMITSTEST_H
#define LIMITSTEST_H

#include "Limits.h"
#include <limits>


class LimitsTest : public ::testing::Test
{
 protected:
    LimitsTest(){}
    virtual ~LimitsTest(){}

};


TEST_F(LimitsTest, LimitsInitial)
{
    Limits limits;

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
}

TEST_F(LimitsTest, LimitsSetLimit)
{
    Limits limits;

    //set limit [-1.0, 10.0[
    limits.setLimits(-1.0,10.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(-1.0,limits.getLowerLimit());
    EXPECT_EQ(10.0,limits.getUpperLimit());

    EXPECT_FALSE(limits.isInRange(-2.0));
    EXPECT_TRUE(limits.isInRange(-1.0));
    EXPECT_TRUE(limits.isInRange(0.0));
    EXPECT_TRUE(limits.isInRange(9.0));
    EXPECT_FALSE(limits.isInRange(10.0));
    EXPECT_FALSE(limits.isInRange(20.0));

    // [inf, -10.0[
    limits.removeLowerLimit();
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_EQ(0.0,limits.getLowerLimit());

    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(-2.0));
    EXPECT_TRUE(limits.isInRange(9.0));
    EXPECT_FALSE(limits.isInRange(10.0));
    EXPECT_FALSE(limits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, -10.0[
    limits.setLowerLimit(2.1);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_EQ(2.1,limits.getLowerLimit());

    EXPECT_FALSE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(limits.isInRange(2.0));
    EXPECT_TRUE(limits.isInRange(2.1));

    //[2.1, inf]
    limits.removeUpperLimit();
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_EQ(0.0,limits.getUpperLimit());

    EXPECT_FALSE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(limits.isInRange(2.0));
    EXPECT_TRUE(limits.isInRange(2.1));
    EXPECT_TRUE(limits.isInRange(20.0));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));

    // [2.1, 2.2[
    limits.setUpperLimit(2.2);
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_EQ(2.2,limits.getUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());
    EXPECT_TRUE(limits.isInRange(2.15));
    EXPECT_FALSE(limits.isInRange(2.2));

    //remove limit
    limits.removeLimits();
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_TRUE(limits.isInRange(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(limits.isInRange(std::numeric_limits<double>::infinity()));

}

TEST_F(LimitsTest, LimitsLowerLimited)
{
    Limits limits = Limits::lowerLimited(5.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(5.0,limits.getLowerLimit());
    EXPECT_EQ(0.0,limits.getUpperLimit());
}

TEST_F(LimitsTest, LimitsUpperLimited)
{
    Limits limits = Limits::upperLimited(5.0);
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(0.0,limits.getLowerLimit());
    EXPECT_EQ(5.0,limits.getUpperLimit());
}

TEST_F(LimitsTest, LimitsLimited)
{
    Limits limits = Limits::limited(-10.0, 2.0);
    EXPECT_TRUE(limits.hasLowerLimit());
    EXPECT_TRUE(limits.hasUpperLimit());
    EXPECT_TRUE(limits.hasLowerAndUpperLimits());

    EXPECT_EQ(-10.0,limits.getLowerLimit());
    EXPECT_EQ(2.0,limits.getUpperLimit());
}

TEST_F(LimitsTest, LimitsLimitless)
{
    Limits limits = Limits::limitless();

    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
    EXPECT_FALSE(limits.hasLowerAndUpperLimits());
}

TEST_F(LimitsTest, ComparisonOperators)
{
    Limits lim1 = Limits::limited(1.0, 2.0);
    Limits lim2 = Limits::limited(1.0, 2.0);
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    Limits lim3 = Limits::limitless();
    Limits lim4 = Limits::limitless();
    EXPECT_TRUE(lim3 == lim4);
    EXPECT_FALSE(lim3 != lim4);

    Limits lim5 = Limits::lowerLimited(1.0);
    Limits lim6 = Limits::lowerLimited(1.0);
    EXPECT_TRUE(lim5 == lim6);
    EXPECT_FALSE(lim5 != lim6);

    Limits lim7 = Limits::upperLimited(1.0);
    Limits lim8 = Limits::upperLimited(1.0);
    EXPECT_TRUE(lim7 == lim8);
    EXPECT_FALSE(lim7 != lim8);
}

TEST_F(LimitsTest, CopyConstructor)
{
    Limits lim1 = Limits::limited(1.0, 2.0);
    Limits lim2 = lim1;
    EXPECT_TRUE(lim1 == lim2);
    EXPECT_FALSE(lim1 != lim2);

    Limits lim3(lim1);
    EXPECT_TRUE(lim1 == lim3);
    EXPECT_FALSE(lim1 != lim3);
}

#endif // LIMITSTEST_H
