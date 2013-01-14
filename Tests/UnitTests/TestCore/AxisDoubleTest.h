#ifndef AXISDOUBLETEST_H
#define AXISDOUBLETEST_H

#include "AxisDouble.h"

#include "gtest/gtest.h"

class AxisDoubleTest : public ::testing::Test
{
protected:
    AxisDoubleTest();

    AxisDouble angleAxis;
    AxisDouble lengthAxis;

};

AxisDoubleTest::AxisDoubleTest()
: angleAxis("angle")
, lengthAxis("length", 100, 0.0, 9.9)
{
}

TEST_F(AxisDoubleTest, DefaultIsEmpty)
{
    EXPECT_EQ((size_t)0, angleAxis.getSize());
}

TEST_F(AxisDoubleTest, AddElementsToEmpty)
{
    angleAxis.push_back(1.0f);
    ASSERT_EQ((size_t)1, angleAxis.getSize());
    EXPECT_FLOAT_EQ(1.0f, angleAxis[0]);
}

TEST_F(AxisDoubleTest, ExtendedConstructor)
{
    ASSERT_EQ((size_t)100, lengthAxis.getSize());
    EXPECT_DOUBLE_EQ(0.0, lengthAxis[0]);
    EXPECT_DOUBLE_EQ(0.1, lengthAxis[1]);
    EXPECT_DOUBLE_EQ(6.5, lengthAxis[65]);
    EXPECT_DOUBLE_EQ(9.9, lengthAxis[99]);
}

TEST_F(AxisDoubleTest, VectorOfUnitLength)
{
    AxisDouble vec("name", 1, 1.0, 2.0);
    EXPECT_EQ((size_t)1, vec.getSize());
    EXPECT_EQ(double(1), vec.getMin());
    EXPECT_EQ(double(1), vec.getMax());
}

TEST_F(AxisDoubleTest, FindClosestIndex)
{
    AxisDouble vec_size1("name", 1, 2.0, 4.0);
    EXPECT_EQ( size_t(1), vec_size1.getSize());
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(1.0));
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(3.0));
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(5.0));

    AxisDouble vec_size2("name", 2, 2.0, 4.0);
    EXPECT_EQ( size_t(2), vec_size2.getSize() );
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(1.0));
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(2.9));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(3.1));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(4.1));

    AxisDouble vec_size11("name", 11, 0.0, 10.0);
    EXPECT_EQ( size_t(11), vec_size11.getSize());
    EXPECT_DOUBLE_EQ(double(0), vec_size11[0]);
    EXPECT_DOUBLE_EQ(double(10), vec_size11[10]);
    EXPECT_EQ( size_t(0), vec_size11.findClosestIndex(-1.0));
    EXPECT_EQ( size_t(0), vec_size11.findClosestIndex(0.0));
    EXPECT_EQ( size_t(1), vec_size11.findClosestIndex(1));
    EXPECT_EQ( size_t(0), vec_size11.findClosestIndex(0.49));
    EXPECT_EQ( size_t(1), vec_size11.findClosestIndex(0.51));
    EXPECT_EQ( size_t(9), vec_size11.findClosestIndex(9.01));
    EXPECT_EQ( size_t(10), vec_size11.findClosestIndex(100.));
}

#endif // AXISDOUBLETEST_H
