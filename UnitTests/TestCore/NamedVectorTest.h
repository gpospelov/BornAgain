#ifndef NAMEDVECTORTEST_H
#define NAMEDVECTORTEST_H

#include "NamedVector.h"

#include "gtest/gtest.h"

class NamedVectorTest : public ::testing::Test
{
protected:
    NamedVectorTest();

    NamedVector<float> floatAngleVector;
    NamedVector<double> doubleLengthVector;

};

NamedVectorTest::NamedVectorTest()
    : floatAngleVector("angle")
    , doubleLengthVector("length", 0.0, 9.9, 100)
{
}

TEST_F(NamedVectorTest, DefaultIsEmpty)
{
    EXPECT_EQ((size_t)0, floatAngleVector.getSize());
}

TEST_F(NamedVectorTest, AddElementsToEmpty)
{
    floatAngleVector.push_back(1.0f);
    ASSERT_EQ((size_t)1, floatAngleVector.getSize());
    EXPECT_FLOAT_EQ(1.0f, floatAngleVector[0]);
}

TEST_F(NamedVectorTest, ExtendedConstructor)
{
    ASSERT_EQ((size_t)100, doubleLengthVector.getSize());
    EXPECT_DOUBLE_EQ(0.0, doubleLengthVector[0]);
    EXPECT_DOUBLE_EQ(0.1, doubleLengthVector[1]);
    EXPECT_DOUBLE_EQ(6.5, doubleLengthVector[65]);
    EXPECT_DOUBLE_EQ(9.9, doubleLengthVector[99]);
}

TEST_F(NamedVectorTest, VectorOfUnitLength)
{
    NamedVector<double> vec("name", 1.0, 2.0, 1);
    EXPECT_EQ((size_t)1, vec.getSize());
    EXPECT_EQ(double(1), vec.getMin());
    EXPECT_EQ(double(1), vec.getMax());
}


TEST_F(NamedVectorTest, FindClosestIndex)
{
    NamedVector<double> vec_size1("name", 2.0, 4.0, 1);
    EXPECT_EQ( size_t(1), vec_size1.getSize());
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(1.0));
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(3.0));
    EXPECT_EQ( size_t(0), vec_size1.findClosestIndex(5.0));

    NamedVector<double> vec_size2("name", 2.0, 4.0, 2);
    EXPECT_EQ( size_t(2), vec_size2.getSize() );
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(1.0));
    EXPECT_EQ( size_t(0), vec_size2.findClosestIndex(2.9));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(3.1));
    EXPECT_EQ( size_t(1), vec_size2.findClosestIndex(4.1));

    NamedVector<double> vec_size11("name", 0.0, 10.0, 11);
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



#endif // NAMEDVECTORTEST_H
