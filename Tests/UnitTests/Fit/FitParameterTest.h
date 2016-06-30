#ifndef FITPARAMETERTEST_H
#define FITPARAMETERTEST_H

#include "FitParameter.h"

#include "gtest/gtest.h"


class FitParameterTest : public ::testing::Test
{
 protected:
    FitParameterTest(){}
    virtual ~FitParameterTest(){}

};



TEST_F(FitParameterTest, FitParameterInitial)
{
    FitParameter fitParameter;

    EXPECT_EQ("", fitParameter.getName());
    EXPECT_EQ(0.0, fitParameter.getValue());
    EXPECT_EQ(0.0, fitParameter.getStep());
    EXPECT_EQ(0.0, fitParameter.getError());


    EXPECT_FALSE(fitParameter.hasLowerLimit());
    EXPECT_FALSE(fitParameter.hasUpperLimit());
    EXPECT_FALSE(fitParameter.hasLowerAndUpperLimits());
    EXPECT_FALSE(fitParameter.isFixed());
}

TEST_F(FitParameterTest, FitParameterSetValue)
{
    FitParameter fitParameter;
    fitParameter.setValue(-1.0);
    fitParameter.setStep(0.1);
    fitParameter.setError(1.2);

    EXPECT_EQ(-1.0, fitParameter.getValue());
    EXPECT_EQ(0.1, fitParameter.getStep());
    EXPECT_EQ(1.2, fitParameter.getError());
}


TEST_F(FitParameterTest, FitParameterWithValue)
{
    AttLimits attLimits = AttLimits::limited(-10.0, 2.0);

    FitParameter fitParameter("FitP", 2.0, 0.2, attLimits, 0.01);

    EXPECT_EQ("FitP", fitParameter.getName());
    EXPECT_EQ(2.0, fitParameter.getValue());
    EXPECT_EQ(0.2, fitParameter.getStep());
    EXPECT_EQ(0.01, fitParameter.getError());


    EXPECT_TRUE(fitParameter.hasLowerLimit());
    EXPECT_TRUE(fitParameter.hasUpperLimit());
    EXPECT_TRUE(fitParameter.hasLowerAndUpperLimits());
    EXPECT_FALSE(fitParameter.isFixed());
    EXPECT_EQ(-10.0, fitParameter.getLowerLimit());
    EXPECT_EQ(2.0, fitParameter.getUpperLimit());


    fitParameter.setValue(-1.0);
    fitParameter.setStep(0.1);
    fitParameter.setError(1.2);

    EXPECT_EQ(-1.0, fitParameter.getValue());
    EXPECT_EQ(0.1, fitParameter.getStep());
    EXPECT_EQ(1.2, fitParameter.getError());
}

#endif //FITPARAMETERTEST_H
