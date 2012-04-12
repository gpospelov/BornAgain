#include "gtest/gtest.h"
#include "NamedVectorTest.h"
#include "OutputDataTest.h"

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

TEST_F(OutputDataTest, EmptyAfterConstruction)
{
    EXPECT_EQ((size_t)0, int_data_0d.getAllocatedSize());
    EXPECT_EQ((size_t)0, fl_data_1d.getAllocatedSize());
}

TEST_F(OutputDataTest, SizeAfterAllocation)
{
    MultiIndex &index_int_data = int_data_0d.getIndex();
    MultiIndex &index_fl_data = fl_data_1d.getIndex();
    MultiIndex &index_db_data = db_data_3d.getIndex();
    EXPECT_EQ((size_t)1, int_data_0d.getAllocatedSize());
    EXPECT_EQ((size_t)20, fl_data_1d.getAllocatedSize());
    EXPECT_EQ((size_t)2000, db_data_3d.getAllocatedSize());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}

