#ifndef ASYMMETRICBINAXISTEST_H
#define ASYMMETRICBINAXISTEST_H

#include "AsymmetricBinAxis.h"
#include "gtest/gtest.h"

class AsymmetricBinAxisTest: public ::testing::Test
{
protected:
    AsymmetricBinAxisTest() {}

};

TEST_F(AsymmetricBinAxisTest, VectorOfUnitLength)
{
    static const double arr1[] = {1.};
    std::vector<double> values1 (arr1, arr1 + sizeof(arr1) / sizeof(double) );
    AsymmetricBinAxis axis1("name", 1, values1);

    EXPECT_EQ("name", axis1.getName());
    EXPECT_EQ(1, axis1.getSize());
    EXPECT_EQ(0.5, axis1.getMin());
    EXPECT_EQ(1.5, axis1.getMax());
    EXPECT_EQ(1.0, axis1[0]);
}


TEST_F(AsymmetricBinAxisTest, AsymmetricBins)
{
    static const double arr1[] = {0.0};
    std::vector<double> values1 (arr1, arr1 + sizeof(arr1) / sizeof(double) );
    AsymmetricBinAxis axis1("name", 1, values1);
    EXPECT_EQ("name", axis1.getName());
    EXPECT_EQ(1, axis1.getSize());
    EXPECT_EQ(-0.5, axis1.getMin());
    EXPECT_EQ(0.5, axis1.getMax());
    EXPECT_EQ(0.0, axis1[0]);
    ASSERT_THROW( axis1[1], Exceptions::OutOfBoundsException);

    static const double arr2[] = {1.0, 2.0};
    std::vector<double> values2 (arr2, arr2 + sizeof(arr2) / sizeof(double) );
    AsymmetricBinAxis axis2("name", 2, values2);
    EXPECT_EQ("name", axis2.getName());
    EXPECT_EQ(2, axis2.getSize());
    EXPECT_EQ(0.5, axis2.getMin());
    EXPECT_EQ(2.5, axis2.getMax());
    EXPECT_EQ(1.0, axis2[0]);
    EXPECT_EQ(2.0, axis2[1]);
    ASSERT_THROW( axis2[2], Exceptions::OutOfBoundsException);

    static const double arr3[] = {0.0, 2.0, 3.0};
    std::vector<double> values3 (arr3, arr3 + sizeof(arr3) / sizeof(double) );
    AsymmetricBinAxis axis3("name", 3, values3);
    EXPECT_EQ("name", axis3.getName());
    EXPECT_EQ(3, axis3.getSize());
    EXPECT_EQ(-1.0, axis3.getMin());
    EXPECT_EQ(3.5, axis3.getMax());
    EXPECT_EQ(0.0, axis3[0]);
    EXPECT_EQ(2.0, axis3[1]);
    EXPECT_EQ(3.0, axis3[2]);
    ASSERT_THROW( axis3[3], Exceptions::OutOfBoundsException);
}


TEST_F(AsymmetricBinAxisTest, FindClosestIndex)
{
    static const double arr2[] = {1.0, 2.0};
    std::vector<double> values2 (arr2, arr2 + sizeof(arr2) / sizeof(double) );
    AsymmetricBinAxis axis2("name", 2, values2);
    EXPECT_EQ( 0, axis2.findClosestIndex(0.5));
    EXPECT_EQ( 0, axis2.findClosestIndex(1.0));
    EXPECT_EQ( 0, axis2.findClosestIndex(1.49));
    EXPECT_EQ( 1, axis2.findClosestIndex(1.5));
    EXPECT_EQ( 1, axis2.findClosestIndex(2.0));
    EXPECT_EQ( 1, axis2.findClosestIndex(2.49));
    ASSERT_THROW( axis2.findClosestIndex(2.5), Exceptions::OutOfBoundsException);

    static const double arr3[] = {0.0, 2.0, 3.0};
    std::vector<double> values3 (arr3, arr3 + sizeof(arr3) / sizeof(double) );
    AsymmetricBinAxis axis3("name", 3, values3);
    ASSERT_THROW( axis3.findClosestIndex(-1.01), Exceptions::OutOfBoundsException);
    EXPECT_EQ( 0, axis3.findClosestIndex(-1.0));
    EXPECT_EQ( 0, axis3.findClosestIndex(0.0));
    EXPECT_EQ( 0, axis3.findClosestIndex(0.99));
    EXPECT_EQ( 1, axis3.findClosestIndex(1.0));
    EXPECT_EQ( 1, axis3.findClosestIndex(2.0));
    EXPECT_EQ( 1, axis3.findClosestIndex(2.49));
    EXPECT_EQ( 2, axis3.findClosestIndex(2.5));
    EXPECT_EQ( 2, axis3.findClosestIndex(3.0));
    EXPECT_EQ( 2, axis3.findClosestIndex(3.49));
    ASSERT_THROW( axis3.findClosestIndex(3.5), Exceptions::OutOfBoundsException);

    static const double arr4[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values4 (arr4, arr4 + sizeof(arr4) / sizeof(arr2[0]) );
    AsymmetricBinAxis axis4("name", 5, values4);
    ASSERT_THROW( axis4.findClosestIndex(-1.26), Exceptions::OutOfBoundsException);
    EXPECT_EQ(0, axis4.findClosestIndex(-1.25));
    EXPECT_EQ(0, axis4.findClosestIndex(-1.0));
    EXPECT_EQ(0, axis4.findClosestIndex(-0.76));
    EXPECT_EQ(1, axis4.findClosestIndex(-0.75));
    EXPECT_EQ(1, axis4.findClosestIndex(-0.5));
    EXPECT_EQ(1, axis4.findClosestIndex(-0.01));
    EXPECT_EQ(2, axis4.findClosestIndex(0.01));
    EXPECT_EQ(2, axis4.findClosestIndex(0.5));
    EXPECT_EQ(2, axis4.findClosestIndex(0.74));
    EXPECT_EQ(3, axis4.findClosestIndex(0.75));
    EXPECT_EQ(3, axis4.findClosestIndex(1.0));
    EXPECT_EQ(3, axis4.findClosestIndex(1.49));
    EXPECT_EQ(4, axis4.findClosestIndex(1.50));
    EXPECT_EQ(4, axis4.findClosestIndex(2.0));
    EXPECT_EQ(4, axis4.findClosestIndex(2.49));
    ASSERT_THROW( axis4.findClosestIndex(2.50), Exceptions::OutOfBoundsException);

}


TEST_F(AsymmetricBinAxisTest, CheckBin)
{
    static const double arr1[] = {1.};
    std::vector<double> values1 (arr1, arr1 + sizeof(arr1) / sizeof(double) );
    AsymmetricBinAxis axis1("name", 1, values1);
//    EXPECT_DOUBLE_EQ( 0.5, axis1.getBin(0).m_lower);
    EXPECT_DOUBLE_EQ( 1.0, axis1.getBin(0).getMidPoint());
//    EXPECT_DOUBLE_EQ( 1.5, axis1.getBin(0).m_upper);
//    EXPECT_DOUBLE_EQ( 1.0, axis1.getBin(0).getBinSize());

    static const double arr2[] = {-1., 1.0};
    std::vector<double> values2 (arr2, arr2 + sizeof(arr2) / sizeof(double) );
    AsymmetricBinAxis axis2("name", 2, values2);
//    EXPECT_DOUBLE_EQ(-2.0, axis2.getBin(0).m_lower);
    EXPECT_DOUBLE_EQ(-1.0, axis2.getBin(0).getMidPoint());
//    EXPECT_DOUBLE_EQ( 0.0, axis2.getBin(0).m_upper);
//    EXPECT_DOUBLE_EQ( 2.0, axis2.getBin(0).getBinSize());

//    EXPECT_DOUBLE_EQ( 0.0, axis2.getBin(1).m_lower);
    EXPECT_DOUBLE_EQ( 1.0, axis2.getBin(1).getMidPoint());
//    EXPECT_DOUBLE_EQ( 2.0, axis2.getBin(1).m_upper);
//    EXPECT_DOUBLE_EQ( 2.0, axis2.getBin(1).getBinSize());

    static const double arr4[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values4 (arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]) );
    AsymmetricBinAxis axis4("name", 5, values4);
//    EXPECT_DOUBLE_EQ( -1.25, axis4.getBin(0).m_lower);
    EXPECT_DOUBLE_EQ( -1.0,  axis4.getBin(0).getMidPoint());
//    EXPECT_DOUBLE_EQ( -0.75, axis4.getBin(0).m_upper);
//    EXPECT_DOUBLE_EQ( 0.5,   axis4.getBin(0).getBinSize());

//    EXPECT_DOUBLE_EQ( -0.75, axis4.getBin(1).m_lower);
    EXPECT_DOUBLE_EQ( -0.5,  axis4.getBin(1).getMidPoint());
//    EXPECT_DOUBLE_EQ( -0.25, axis4.getBin(1).m_upper);
//    EXPECT_DOUBLE_EQ( 0.5,   axis4.getBin(1).getBinSize());

//    EXPECT_DOUBLE_EQ( 0.25, axis4.getBin(2).m_lower);
    EXPECT_DOUBLE_EQ( 0.5,  axis4.getBin(2).getMidPoint());
//    EXPECT_DOUBLE_EQ( 0.75, axis4.getBin(2).m_upper);
//    EXPECT_DOUBLE_EQ( 0.5,   axis4.getBin(2).getBinSize());

//    EXPECT_DOUBLE_EQ( 0.75, axis4.getBin(3).m_lower);
    EXPECT_DOUBLE_EQ( 1.0,  axis4.getBin(3).getMidPoint());
//    EXPECT_DOUBLE_EQ( 1.25, axis4.getBin(3).m_upper);
//    EXPECT_DOUBLE_EQ( 0.5,   axis4.getBin(3).getBinSize());

//    EXPECT_DOUBLE_EQ( 1.5, axis4.getBin(4).m_lower);
    EXPECT_DOUBLE_EQ( 2.0,  axis4.getBin(4).getMidPoint());
//    EXPECT_DOUBLE_EQ( 2.5, axis4.getBin(4).m_upper);
//    EXPECT_DOUBLE_EQ( 1.0,   axis4.getBin(4).getBinSize());
}


TEST_F(AsymmetricBinAxisTest, CheckEquality)
{
    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );

    AsymmetricBinAxis a1("name", 5, values3);
    AsymmetricBinAxis a2("name", 5, values3);
    AsymmetricBinAxis a3("nameX", 5, values3);
    EXPECT_TRUE( a1 == a2);
    EXPECT_FALSE( a1 == a3);

    static const double arr4[] = {-1.0, -0.5, 0.5, 1.1, 2.0};
    std::vector<double> values4 (arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]) );
    AsymmetricBinAxis a4("nameX", 5, values4);
    EXPECT_FALSE( a1 == a4);
}


TEST_F(AsymmetricBinAxisTest, CheckClone)
{
    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
    AsymmetricBinAxis a1("name", 5, values3);

    AsymmetricBinAxis *clone=a1.clone();
    EXPECT_TRUE(a1 == *clone);
    delete clone;
}



#endif
