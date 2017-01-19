#include "FitSuite.h"
#include "IFitParameter.h"
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

    IFitParameter *par = fitSuite->addFitParameter("pattern1", 1.0);
    EXPECT_EQ("par0", par->name());
    EXPECT_EQ(1.0, par->value());
    EXPECT_EQ(0.0, par->error());
    EXPECT_EQ(0.01, par->step()); // default step invented by FitSuite
    EXPECT_TRUE(par->limits().isLimitless());

    par = fitSuite->addFitParameter("pattern2", 2.0, AttLimits::limited(10.0, 20.0), 0.02);
    EXPECT_EQ("par1", par->name());
    EXPECT_EQ(2.0, par->value());
    EXPECT_EQ(0.0, par->error());
    EXPECT_EQ(0.02, par->step());
    EXPECT_TRUE(par->limits().isLimited());
    EXPECT_EQ(10.0, par->limits().lowerLimit());
    EXPECT_EQ(20.0, par->limits().upperLimit());

    IFitParameter &par2 = fitSuite->addFitParameter("pattern3", 3.0)->
            setStep(0.03).setLowerLimited(30.0);
    EXPECT_EQ("par2", par2.name());
    EXPECT_EQ(3.0, par2.value());
    EXPECT_EQ(0.0, par2.error());
    EXPECT_EQ(0.03, par2.step());
    EXPECT_TRUE(par2.limits().isLowerLimited());
    EXPECT_EQ(30.0, par2.limits().lowerLimit());

    IFitParameter &par3 = fitSuite->addFitParameter("pattern4", 4.0)->setFixed();
    EXPECT_EQ("par3", par3.name());
    EXPECT_EQ(4.0, par3.value());
    EXPECT_TRUE(par3.limits().isFixed());
}

TEST_F(FitSuiteTest, addConstructedFitParameter)
{
    std::unique_ptr<FitSuite> fitSuite(new FitSuite);

    FitParameterLinked par("pattern1", 1.0, AttLimits::limited(0.0, 2.0));

    FitParameterLinked *clone = fitSuite->addFitParameter(par);
    EXPECT_EQ(clone->value(), 1.0);
    EXPECT_EQ(clone->startValue(), 1.0);
    EXPECT_EQ(clone->limits(), AttLimits::limited(0.0, 2.0));
    EXPECT_EQ(clone->step(), 0.01); // step invented by FitSuite
    EXPECT_EQ(clone->patterns(), std::vector<std::string>() = {"pattern1"});
}
