#ifndef FITPARAMETERSETTEST_H
#define FITPARAMETERSETTEST_H

#include "FitParameter.h"
#include "FitParameterSet.h"
#include "gtest/gtest.h"

class FitParameterSetTest : public ::testing::Test
{
 protected:
    FitParameterSetTest(){}
    virtual ~FitParameterSetTest(){}
};

TEST_F(FitParameterSetTest, addFitParameter)
{
    FitParameterSet parameters;

    FitParameter *par = new FitParameter("par1", 1.0);
    parameters.addFitParameter(par);
    EXPECT_EQ(parameters.size(), 1);

    // attempt to add same fit parameter twice
    EXPECT_THROW(parameters.addFitParameter(par), std::runtime_error);

    // attempt to add fit parameter with the same name
    std::unique_ptr<FitParameter> par2(new FitParameter("par1", 2.0));
    EXPECT_THROW(parameters.addFitParameter(par2.get()), std::runtime_error);

    parameters.clear();
    EXPECT_EQ(parameters.size(), 0);
}

TEST_F(FitParameterSetTest, getFitParameter)
{
    FitParameterSet parameters;

    FitParameter *par1 = new FitParameter("par1", 1.0);
    parameters.addFitParameter(par1);
    FitParameter *par2 = new FitParameter("par2", 1.0);
    parameters.addFitParameter(par2);

    EXPECT_EQ(parameters.fitParameter("par1"), par1);
    EXPECT_EQ(parameters.fitParameter("par2"), par2);
    EXPECT_EQ(parameters["par1"], par1);
    EXPECT_EQ(parameters["par2"], par2);
    EXPECT_EQ(parameters[0], par1);
    EXPECT_EQ(parameters[1], par2);

    EXPECT_THROW(parameters.fitParameter("par3"), std::runtime_error);
    EXPECT_THROW(parameters["par3"], std::runtime_error);
    EXPECT_THROW(parameters[2], std::runtime_error);
}

TEST_F(FitParameterSetTest, parameterValues)
{
    FitParameterSet parameters;
    parameters.addFitParameter(new FitParameter("par1", 1.0));
    parameters.addFitParameter(new FitParameter("par2", 2.0));
    parameters.addFitParameter(new FitParameter("par3", 3.0));
    std::vector<double> values{1.0, 2.0, 3.0};
    EXPECT_EQ(parameters.values(), values);

    std::vector<double> new_values{4.0, 5.0, 6.0};
    parameters.setValues(new_values);
    EXPECT_EQ(parameters.values(), new_values);

    // are values different?
    EXPECT_FALSE(parameters.valuesDifferFrom(new_values));
    new_values = {4.0, 5.1, 6.0};
    EXPECT_TRUE(parameters.valuesDifferFrom(new_values));

    // attempt to set vector of wrong size
    new_values = {4.0, 5.0, 6.0, 7.0};
    EXPECT_THROW(parameters.setValues(new_values), std::runtime_error);
}

TEST_F(FitParameterSetTest, parameterErrors)
{
    FitParameterSet parameters;
    FitParameter *par1 = new FitParameter("par1", 1.0, 0.01, RealLimits::limitless(),
                                          Attributes::free(), 1.0);
    FitParameter *par2 = new FitParameter("par2", 1.0, 0.01, RealLimits::limitless(),
                                          Attributes::free(), 2.0);

    parameters.addFitParameter(par1);
    parameters.addFitParameter(par2);

    std::vector<double> errors{1.0, 2.0};
    EXPECT_EQ(parameters.errors(), errors);

    parameters.setErrors(std::vector<double>() = {4.0, 5.0});
    EXPECT_EQ(par1->getError(), 4.0);
    EXPECT_EQ(par2->getError(), 5.0);
}

TEST_F(FitParameterSetTest, fixRelease)
{
    FitParameterSet parameters;
    FitParameter *par1 = new FitParameter("par1", 1.0, 0.01, RealLimits::limitless(),
                                          Attributes::free(), 1.0);
    FitParameter *par2 = new FitParameter("par2", 1.0, 0.01, RealLimits::limitless(),
                                          Attributes::free(), 2.0);
    FitParameter *par3 = new FitParameter("par3", 1.0, 0.01, RealLimits::limitless(),
                                          Attributes::free(), 2.0);

    parameters.addFitParameter(par1);
    parameters.addFitParameter(par2);
    parameters.addFitParameter(par3);

    EXPECT_EQ(parameters.freeFitParameterCount(), 3);

    par1->setFixed(true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 2);
    par2->setFixed(true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 1);

    parameters.fixAll();
    EXPECT_EQ(parameters.freeFitParameterCount(), 0);

    parameters.releaseAll();
    EXPECT_EQ(parameters.freeFitParameterCount(), 3);

    std::vector<std::string> names_to_fix={"par1", "par3"};
    parameters.setFixed(names_to_fix, true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 1);
    EXPECT_TRUE(par1->isFixed());
    EXPECT_FALSE(par2->isFixed());
    EXPECT_TRUE(par3->isFixed());
}

#endif
