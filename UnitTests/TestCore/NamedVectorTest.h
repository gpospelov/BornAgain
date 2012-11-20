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

#endif // NAMEDVECTORTEST_H
