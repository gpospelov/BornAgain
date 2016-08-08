#ifndef MINIMIZEROPTIONTEST_H
#define MINIMIZEROPTIONTEST_H

#include "MinimizerOption.h"
#include <variant.hpp>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

class MinimizerOptionTest : public ::testing::Test {
protected:
    MinimizerOptionTest(){}

};

TEST_F(MinimizerOptionTest, Variant)
{
    MinimizerOption::variant_t v1(1);

    EXPECT_EQ(0, v1.which());
    EXPECT_EQ(1, v1.get<int>());

    v1 = 2.0;
    EXPECT_EQ(1, v1.which());
    EXPECT_EQ(2.0, v1.get<double>());

    const std::string text("xxx");
    v1 = text;
    EXPECT_EQ(2, v1.which());
    EXPECT_EQ(text, v1.get<std::string>());
}

TEST_F(MinimizerOptionTest, Construction)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MinimizerOption opt(name, double_value, description);

    EXPECT_EQ(name, opt.name());
    EXPECT_EQ(description, opt.description());
    EXPECT_EQ(double_value, opt.value().get<double>());
    EXPECT_EQ(double_value, opt.get<double>());
    EXPECT_EQ(double_value, opt.getDefault<double>());

    // setting new value
    const double new_value = 3.0;
    opt.value() = new_value;
    EXPECT_EQ(new_value, opt.get<double>());
    EXPECT_EQ(double_value, opt.getDefault<double>());
}

TEST_F(MinimizerOptionTest, Copying)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MinimizerOption opt(name, double_value, description);

    MinimizerOption copy(opt);
    EXPECT_EQ(name, copy.name());
    EXPECT_EQ(description, copy.description());
    EXPECT_EQ(double_value, copy.value().get<double>());
    EXPECT_EQ(double_value, copy.get<double>());
    EXPECT_EQ(double_value, copy.getDefault<double>());
}

TEST_F(MinimizerOptionTest, Assignment)
{
    const std::string name("name");
    const std::string description("description");
    const double double_value(2.0);
    MinimizerOption opt(name, double_value, description);

    MinimizerOption copy;
    copy = opt;

    const double new_value = 3.0;
    opt.value() = new_value;

    EXPECT_EQ(name, copy.name());
    EXPECT_EQ(description, copy.description());
    EXPECT_EQ(double_value, copy.value().get<double>());
    EXPECT_EQ(double_value, copy.get<double>());
    EXPECT_EQ(double_value, copy.getDefault<double>());
}

#endif
