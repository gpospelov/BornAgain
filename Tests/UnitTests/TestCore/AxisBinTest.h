#ifndef AXISBINTEST_H
#define AXISBINTEST_H

#include "AxisBin.h"
#include "gtest/gtest.h"

class AxisBinTest: public ::testing::Test
{
protected:
    AxisBinTest()
        : angleAxis("angle"), lengthAxis("length", 100, 0.0, 10.0) {}

    AxisBin angleAxis;
    AxisBin lengthAxis;
};

TEST_F(AxisBinTest, DefaultIsEmpty)
{
     EXPECT_EQ((size_t)0, angleAxis.getSize());
}

TEST_F(AxisBinTest, AddElementsToEmpty)
{
    angleAxis.push_back(0.0);
    angleAxis.push_back(1.0);
    angleAxis.push_back(2.0);
    angleAxis.push_back(3.0);
    angleAxis.push_back(4.0);
    angleAxis.push_back(5.0);

    ASSERT_EQ((size_t)5, angleAxis.getSize());
    EXPECT_DOUBLE_EQ(0.5, (double)angleAxis[0]);
    EXPECT_DOUBLE_EQ(1.5, (double)angleAxis[1]);
    EXPECT_DOUBLE_EQ(2.5, (double)angleAxis[2]);
    EXPECT_DOUBLE_EQ(3.5, (double)angleAxis[3]);
    EXPECT_DOUBLE_EQ(4.5, (double)angleAxis[4]);
}

TEST_F(AxisBinTest, ExtendedConstructor)
{
    ASSERT_EQ((size_t)100, lengthAxis.getSize());
    EXPECT_DOUBLE_EQ(0.05, (double)lengthAxis[0]);
    EXPECT_DOUBLE_EQ(0.15, (double)lengthAxis[1]);
    EXPECT_DOUBLE_EQ(6.55, (double)lengthAxis[65]);
    EXPECT_DOUBLE_EQ(9.95, (double)lengthAxis[99]);
}

TEST_F(AxisBinTest, VectorOfUnitLength)
{
    AxisBin vec("name", 1, 1.0, 2.0);
    EXPECT_EQ((size_t)1, vec.getSize());
    EXPECT_EQ(double(1.0), vec.getMin());
    EXPECT_EQ(double(2.0), vec.getMax());
}

TEST_F(AxisBinTest, FindClosestIndex)
{
    AxisBin vec_size2("name", 2, 0.0, 1.0);
    EXPECT_EQ( size_t(2), vec_size2.getSize());
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(0.1));
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(0.2));
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(0.5));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(0.6));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(1.0));


    AxisBin vec_size10("name", 10, 0.0, 10.0);
    EXPECT_EQ( size_t(10), vec_size10.getSize());
    EXPECT_DOUBLE_EQ(0.5, vec_size10[0]);
    EXPECT_DOUBLE_EQ(9.5, vec_size10[9]);

    EXPECT_EQ( size_t(0), vec_size10.findClosestIndex(0.0));
    EXPECT_EQ( size_t(1), vec_size10.findClosestIndex(1.2));
    EXPECT_EQ( size_t(0), vec_size10.findClosestIndex(0.49));
    EXPECT_EQ( size_t(0), vec_size10.findClosestIndex(0.51));
    EXPECT_EQ( size_t(5), vec_size10.findClosestIndex(5.01));
    EXPECT_EQ( size_t(6), vec_size10.findClosestIndex(6.61));
    EXPECT_EQ( size_t(9), vec_size10.findClosestIndex(9.9));
}

TEST_F(AxisBinTest, CheckBin)
{
    AxisBin bin("name",20,0,10);

    Bin1D bin1d3 = bin.getBin(3);
    EXPECT_DOUBLE_EQ( 1.75, bin1d3.getMidPoint());
    EXPECT_DOUBLE_EQ( 1.5, bin1d3.m_lower);
    EXPECT_DOUBLE_EQ( 2.0, bin1d3.m_upper);

    Bin1D bin1d10 = bin.getBin(10);
    EXPECT_DOUBLE_EQ( 5.25, bin1d10.getMidPoint());
    EXPECT_DOUBLE_EQ( 5.0, bin1d10.m_lower);
    EXPECT_DOUBLE_EQ( 5.5, bin1d10.m_upper);


}


#endif //AXISBINTEST_H
