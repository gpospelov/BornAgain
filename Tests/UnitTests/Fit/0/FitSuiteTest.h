#ifndef FITSUITETEST_H
#define FITSUITETEST_H

#include "FitSuite.h"
#include "FitParameter.h"
#include "gtest/gtest.h"
#include <memory>

class FitSuiteTest : public ::testing::Test
{
 protected:
    FitSuiteTest(){}
    virtual ~FitSuiteTest(){}
};

TEST_F(FitSuiteTest, addFitParameter)
{
    std::unique_ptr<FitSuite> fitSuite(new FitSuite);

    fitSuite->addFitParameter("par1", 1.0);
    FitParameter *par = fitSuite->fitParameters()->fitParameter("par1");
    EXPECT_EQ("par1", par->name());
    EXPECT_EQ(1.0, par->value());
    EXPECT_EQ(0.0, par->error());
    EXPECT_EQ(0.01, par->step()); // default step invented by FitSuite
    EXPECT_TRUE(par->limits().isLimitless());

    par = fitSuite->addFitParameter("par2", 2.0, AttLimits::limited(10.0, 20.0), 0.02);
    EXPECT_EQ("par2", par->name());
    EXPECT_EQ(2.0, par->value());
    EXPECT_EQ(0.0, par->error());
    EXPECT_EQ(0.02, par->step());
    EXPECT_TRUE(par->limits().isLimited());
    EXPECT_EQ(10.0, par->limits().lowerLimit());
    EXPECT_EQ(20.0, par->limits().upperLimit());

    FitParameter &par2 = fitSuite->addFitParameter("par3", 3.0)->setStep(0.03).setLowerLimited(30.0);
    EXPECT_EQ("par3", par2.name());
    EXPECT_EQ(3.0, par2.value());
    EXPECT_EQ(0.0, par2.error());
    EXPECT_EQ(0.03, par2.step());
    EXPECT_TRUE(par2.limits().isLowerLimited());
    EXPECT_EQ(30.0, par2.limits().lowerLimit());

    FitParameter &par3 = fitSuite->addFitParameter("par4", 4.0)->setFixed();
    EXPECT_EQ("par4", par3.name());
    EXPECT_EQ(4.0, par3.value());
    EXPECT_TRUE(par3.limits().isFixed());
}

#endif
