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


//TEST_F(FitParameterTest, FitParameterInitial)
//{
//    FitParameter fitParameter;

//    EXPECT_EQ("", fitParameter.getName());
//    EXPECT_EQ(0.0, fitParameter.getValue());
//    EXPECT_EQ(0.0, fitParameter.getStep());
//    EXPECT_EQ(0.0, fitParameter.getError());

//    EXPECT_FALSE(fitParameter.hasLowerLimit());
//    EXPECT_FALSE(fitParameter.hasUpperLimit());
//    EXPECT_FALSE(fitParameter.hasLowerAndUpperLimits());
//    EXPECT_FALSE(fitParameter.isFixed());
//}

//TEST_F(FitParameterTest, FitParameterSetValue)
//{
//    FitParameter fitParameter;
//    fitParameter.setValue(-1.0);
//    fitParameter.setStep(0.1);
//    fitParameter.setError(1.2);

//    EXPECT_EQ(-1.0, fitParameter.getValue());
//    EXPECT_EQ(0.1, fitParameter.getStep());
//    EXPECT_EQ(1.2, fitParameter.getError());
//}


//TEST_F(FitParameterTest, FitParameterWithValue)
//{
//    RealLimits limits = RealLimits::limited(-10.0, 2.0);

//    FitParameter fitParameter("FitP", 2.0, 0.2, limits, Attributes::free(), 0.01);

//    EXPECT_EQ("FitP", fitParameter.getName());
//    EXPECT_EQ(2.0, fitParameter.getValue());
//    EXPECT_EQ(0.2, fitParameter.getStep());
//    EXPECT_EQ(0.01, fitParameter.getError());

//    EXPECT_TRUE(fitParameter.hasLowerLimit());
//    EXPECT_TRUE(fitParameter.hasUpperLimit());
//    EXPECT_TRUE(fitParameter.hasLowerAndUpperLimits());
//    EXPECT_FALSE(fitParameter.isFixed());
//    EXPECT_EQ(-10.0, fitParameter.getLowerLimit());
//    EXPECT_EQ(2.0, fitParameter.getUpperLimit());

//    fitParameter.setValue(-1.0);
//    fitParameter.setStep(0.1);
//    fitParameter.setError(1.2);

//    EXPECT_EQ(-1.0, fitParameter.getValue());
//    EXPECT_EQ(0.1, fitParameter.getStep());
//    EXPECT_EQ(1.2, fitParameter.getError());
//}

TEST_F(FitParameterTest, Initial)
{
    FitParameter par;
    EXPECT_EQ(std::string(), par.name());
    EXPECT_EQ(0.0, par.value());
    EXPECT_EQ(0.0, par.startValue());
    EXPECT_EQ(0.0, par.step());
    EXPECT_EQ(0.0, par.error());
    EXPECT_TRUE(par.limits().isLimitless());
}

TEST_F(FitParameterTest, Constructors)
{
    const std::string name("name");
    const double value(1.0);

    FitParameter par(name, value);
    EXPECT_EQ(name, par.name());
    EXPECT_EQ(value, par.value());
    EXPECT_EQ(value, par.startValue());
    EXPECT_EQ(0.0, par.step());
    EXPECT_EQ(0.0, par.error());
    EXPECT_TRUE(par.limits().isLimitless());

    const AttLimits limits = AttLimits::limited(1.0, 2.0);
    const double step(0.01);

    FitParameter par2(name, value, limits, step);
    EXPECT_EQ(name, par2.name());
    EXPECT_EQ(value, par2.value());
    EXPECT_EQ(value, par2.startValue());
    EXPECT_EQ(step, par2.step());
    EXPECT_EQ(0.0, par2.error());
    EXPECT_EQ(limits, par2.limits());
}

TEST_F(FitParameterTest, Setters)
{
    const std::string name("name");
    const double start_value(1.0);
    const double value(2.0);
    const AttLimits limits = AttLimits::limited(1.0, 2.0);
    const double error(0.02);
    const double step(0.01);

    FitParameter par(name, start_value);
    par.setValue(value);

    EXPECT_EQ(value, par.value());
    EXPECT_EQ(start_value, par.startValue());

    par.setError(error);
    EXPECT_EQ(error, par.error());

    par.setLimits(limits);
    EXPECT_EQ(limits, par.limits());

    par.setStep(step);
    EXPECT_EQ(step, par.step());
}

TEST_F(FitParameterTest, CompoundSetters)
{
    const std::string name("name");
    const double start_value(1.0);
    const double step(0.1);
    const double lim1(1.0), lim2(2.0);

    FitParameter par(name, start_value);

    par.setStep(step).setLowerLimited(lim1);
    EXPECT_EQ(step, par.step());
    EXPECT_TRUE(par.limits().isLowerLimited());
    EXPECT_EQ(par.limits().lowerLimit(), lim1);
    EXPECT_EQ(par.limits().upperLimit(), 0.0);

    par.setStep(step).setUpperLimited(lim2);
    EXPECT_TRUE(par.limits().isUpperLimited());
    EXPECT_EQ(par.limits().lowerLimit(), 0.0);
    EXPECT_EQ(par.limits().upperLimit(), lim2);

    par.setStep(step).setLimited(lim1, lim2);
    EXPECT_TRUE(par.limits().isLimited());
    EXPECT_EQ(par.limits().lowerLimit(), lim1);
    EXPECT_EQ(par.limits().upperLimit(), lim2);

    par.setStep(step).setFixed();
    EXPECT_TRUE(par.limits().isFixed());
    EXPECT_EQ(par.limits().lowerLimit(), 0.0);
    EXPECT_EQ(par.limits().upperLimit(), 0.0);
}


#endif
