#include "IParameterized.h"
#include "RealParameter.h"
#include <stdexcept>
#include <iostream>

class RealParameterTest : public ::testing::Test
{
 protected:
    RealParameterTest() {}
    virtual ~RealParameterTest() {}
};

TEST_F(RealParameterTest, simpleConstructor)
{
    double value(42.0);
    std::unique_ptr<RealParameter> par(new RealParameter("name", &value));

    EXPECT_EQ(par->getName(), "name");
    EXPECT_EQ(par->getValue(), value);
    EXPECT_EQ(par->getLimits(), RealLimits::limitless());
    EXPECT_EQ(par->unit(), std::string());
    EXPECT_EQ(&value, &par->getData());
    EXPECT_FALSE(par->isNull());
}

TEST_F(RealParameterTest, dataComparison)
{
    double value(1.0);
    RealParameter par1("name1", &value);
    RealParameter par2("name2", &value);
    EXPECT_EQ(&par1.getData(), &value);
    EXPECT_EQ(&par1.getData(), &par2.getData());
    EXPECT_TRUE(par1.hasSameData(par2));

    double another_value(42.0);
    RealParameter par3("name3", &another_value);
    EXPECT_FALSE(par3.hasSameData(par1));
}

TEST_F(RealParameterTest, extendedConstructor)
{
    double value(42.0);
    bool is_changed(false);
    RealParameter par("name", &value, "parent_name",
                      [&](){is_changed=true;},
                      RealLimits::limited(1.0, 43.0), Attributes::free());

    EXPECT_EQ(par.getName(), "name");
    EXPECT_EQ(par.getValue(), value);
    EXPECT_EQ(par.getLimits(), RealLimits::limited(1.0, 43.0));

    // checks
    EXPECT_FALSE(is_changed);
    const double new_value(41.0);
    par.setValue(new_value);
    EXPECT_TRUE(is_changed);
    EXPECT_EQ(par.getValue(), new_value);
}

TEST_F(RealParameterTest, clone)
{
    double value(42.0);
    bool is_changed(false);
    std::unique_ptr<RealParameter> par(new RealParameter("name", &value, "parent_name",
                      [&](){is_changed=true;},
                      RealLimits::limited(1.0, 43.0), Attributes::free()));

    // cloning and deleting original
    std::unique_ptr<RealParameter> clone(par->clone());
    par.reset();

    EXPECT_EQ(clone->getName(), "name");
    EXPECT_EQ(clone->getValue(), value);
    EXPECT_EQ(clone->getLimits(), RealLimits::limited(1.0, 43.0));

    // checks
    EXPECT_FALSE(is_changed);
    const double new_value(41.0);
    clone->setValue(new_value);
    EXPECT_TRUE(is_changed);
    EXPECT_EQ(clone->getValue(), new_value);
    EXPECT_EQ(value, new_value);
}
