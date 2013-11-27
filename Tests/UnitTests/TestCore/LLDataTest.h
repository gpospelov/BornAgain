#ifndef LLDATATEST_H
#define LLDATATEST_H

#include "LLData.h"
#include <algorithm>

#include "gtest/gtest.h"

class LLDataTest : public ::testing::Test
{
 protected:
    LLDataTest();
    virtual ~LLDataTest();


    LLData<int> *int_data_0d;
    LLData<float> *fl_data_1d;
    LLData<double> *db_data_3d;
};

LLDataTest::LLDataTest()
{
	int *dim0 = new int[(size_t)0];
	
	int *dim1 = new int[(size_t)1];
	dim1[0] = 10;

	int *dim3 = new int[(size_t)3];
	dim3[0] = 10;
	dim3[1] = 15;
	dim3[2] = 20;
	
	int_data_0d = new LLData<int>((size_t)0, dim0);
	fl_data_1d  = new LLData<float>((size_t)1, dim1);
	db_data_3d  = new LLData<double>((size_t)3, dim3);
}

LLDataTest::~LLDataTest()
{
}

TEST_F(LLDataTest, TotalSize)
{
    EXPECT_EQ((size_t)1, int_data_0d->getTotalSize());
    EXPECT_EQ((size_t)10, fl_data_1d->getTotalSize());
    EXPECT_EQ((size_t)3000, db_data_3d->getTotalSize());
}

TEST_F(LLDataTest, GetRank)
{
    EXPECT_EQ((size_t)0, int_data_0d->getRank());
    EXPECT_EQ((size_t)1, fl_data_1d->getRank());
    EXPECT_EQ((size_t)3, db_data_3d->getRank());
}



TEST_F(LLDataTest, SetAll)
{
    db_data_3d->setAll(1.0);
    EXPECT_EQ( (*db_data_3d)[0], 1.0);
}

TEST_F(LLDataTest, ScaleAll)
{
    db_data_3d->setAll(2.0);
    db_data_3d->scaleAll(2.5);
    EXPECT_EQ( (*db_data_3d)[0], 5.0);
}

TEST_F(LLDataTest, TotalSum)
{
    fl_data_1d->setAll(2.0);
    EXPECT_EQ( fl_data_1d->getTotalSum(), 20.0);

	db_data_3d->setAll(0.5);
    EXPECT_EQ( db_data_3d->getTotalSum(), 1500.0);

}


#endif // LLDATATEST_H
