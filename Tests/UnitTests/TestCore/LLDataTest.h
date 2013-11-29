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

TEST_F(LLDataTest, GetDimensions) {
//	EXPECT_EQ( int_data_0d->getDimensions(), NULL);
	EXPECT_EQ( fl_data_1d->getDimensions()[0], 10);
	EXPECT_EQ( db_data_3d->getDimensions()[1], 15);
}

TEST_F(LLDataTest, DataCopyingConstructor) {
	LLData<int> *other_int_data_0d = new LLData<int>(*int_data_0d);
	EXPECT_TRUE(HaveSameDimensions(*int_data_0d, *other_int_data_0d));	

	fl_data_1d->setAll(1.2);
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	EXPECT_TRUE(HaveSameDimensions(*fl_data_1d, *other_fl_data_1d));
	EXPECT_EQ( (*other_fl_data_1d)[0], 1.2f);	
	EXPECT_EQ(fl_data_1d->getTotalSum(), other_fl_data_1d->getTotalSum());	
	
	db_data_3d->setAll(1.17);
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	EXPECT_TRUE(HaveSameDimensions(*db_data_3d, *other_db_data_3d));
	EXPECT_EQ( (*other_db_data_3d)[10], 1.17);	
	EXPECT_EQ(db_data_3d->getTotalSum(), other_db_data_3d->getTotalSum());	
	
	delete other_int_data_0d;
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F(LLDataTest, DataAssignment) {
	
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	fl_data_1d->setAll(1.1f);
	(*other_fl_data_1d) =  (*fl_data_1d);
	EXPECT_EQ( (*other_fl_data_1d)[0], 1.1f);	
	EXPECT_EQ(fl_data_1d->getTotalSum(), other_fl_data_1d->getTotalSum());	
	
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	db_data_3d->setAll(1.27);
	(*other_db_data_3d) =  (*db_data_3d);
	EXPECT_EQ( (*other_db_data_3d)[11], 1.27);	
	EXPECT_EQ(db_data_3d->getTotalSum(), other_db_data_3d->getTotalSum());	
	
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F(LLDataTest, Addition) {
	
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	fl_data_1d->setAll(1.1f);
	other_fl_data_1d->setAll(2.9f);
	(*other_fl_data_1d) +=  (*fl_data_1d);
	EXPECT_EQ( (*other_fl_data_1d)[0], 4.0f);	
	EXPECT_EQ(other_fl_data_1d->getTotalSum(), 40.0f);	
	
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	db_data_3d->setAll(1.27);
	other_db_data_3d->setAll(0.73);
	(*other_db_data_3d) +=  (*db_data_3d);
	EXPECT_EQ( (*other_db_data_3d)[11], 2.0);	
	EXPECT_EQ(other_db_data_3d->getTotalSum(), 6000.0);	

	int *odim1 = new int[(size_t)1];
	odim1[0] = 12;
	LLData<float>  *fl_data_1d2  = new LLData<float>((size_t)1, odim1);
	fl_data_1d2->setAll(10.0);

	EXPECT_THROW((*fl_data_1d) += (*fl_data_1d2), RuntimeErrorException);

	delete fl_data_1d2;
	delete odim1;
	
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F(LLDataTest, Substraction) {
	
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	fl_data_1d->setAll(1.15f);
	other_fl_data_1d->setAll(5.15f);
	(*other_fl_data_1d) -=  (*fl_data_1d);
	EXPECT_EQ( (*other_fl_data_1d)[0], 4.0f);	
	EXPECT_EQ(other_fl_data_1d->getTotalSum(), 40.0f);	
	
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	db_data_3d->setAll(1.27);
	other_db_data_3d->setAll(1.77);
	(*other_db_data_3d) -=  (*db_data_3d);
	EXPECT_EQ( (*other_db_data_3d)[11], 0.5);	
	EXPECT_EQ(other_db_data_3d->getTotalSum(), 1500.0);	

	int *odim1 = new int[(size_t)1];
	odim1[0] = 12;
	LLData<float>  *fl_data_1d2  = new LLData<float>((size_t)1, odim1);
	fl_data_1d2->setAll(10.0);

	EXPECT_THROW((*fl_data_1d) -= (*fl_data_1d2), RuntimeErrorException);

	delete fl_data_1d2;
	delete odim1;
	
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F(LLDataTest, Multiplication) {
	
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	fl_data_1d->setAll(1.15f);
	other_fl_data_1d->setAll(2.0f);
	(*other_fl_data_1d) *=  (*fl_data_1d);
	EXPECT_EQ( (*other_fl_data_1d)[0], 2.30f);	
	EXPECT_EQ(other_fl_data_1d->getTotalSum(), 23.0f);	
	
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	db_data_3d->setAll(1.25);
	other_db_data_3d->setAll(2.0);
	(*other_db_data_3d) *=  (*db_data_3d);
	EXPECT_EQ( (*other_db_data_3d)[11], 2.5);	
	EXPECT_EQ(other_db_data_3d->getTotalSum(), 7500.0);	

	int *odim1 = new int[(size_t)1];
	odim1[0] = 12;
	LLData<float>  *fl_data_1d2  = new LLData<float>((size_t)1, odim1);
	fl_data_1d2->setAll(10.0);

	EXPECT_THROW((*fl_data_1d) *= (*fl_data_1d2), RuntimeErrorException);

	delete fl_data_1d2;
	delete odim1;
	
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F(LLDataTest, Division) {
	
	LLData<float> *other_fl_data_1d  = new LLData<float>(*fl_data_1d);
	fl_data_1d->setAll(1.15f);
	other_fl_data_1d->setAll(2.3f);
	(*other_fl_data_1d) /=  (*fl_data_1d);
	EXPECT_EQ( (*other_fl_data_1d)[0], 2.0f);	
	EXPECT_EQ(other_fl_data_1d->getTotalSum(), 20.0f);	
	
	LLData<double> *other_db_data_3d  = new LLData<double>(*db_data_3d);
	db_data_3d->setAll(1.25);
	other_db_data_3d->setAll(2.5);
	(*other_db_data_3d) /=  (*db_data_3d);
	EXPECT_EQ( (*other_db_data_3d)[11], 2.0);	
	EXPECT_EQ(other_db_data_3d->getTotalSum(), 6000.0);	

	int *odim1 = new int[(size_t)1];
	odim1[0] = 12;
	LLData<float>  *fl_data_1d2  = new LLData<float>((size_t)1, odim1);
	fl_data_1d2->setAll(10.0);

	EXPECT_THROW((*fl_data_1d) /= (*fl_data_1d2), RuntimeErrorException);

	delete fl_data_1d2;
	delete odim1;
	delete other_fl_data_1d;
	delete other_db_data_3d;
}

TEST_F (LLDataTest, HaveSameDimensions) {
	int *odim0 = new int[(size_t)0];
	
	int *odim1 = new int[(size_t)1];
	odim1[0] = 10;

	int *odim3 = new int[(size_t)3];
	odim3[0] = 10;
	odim3[1] = 15;
	odim3[2] = 20;
	
	LLData<int>    *other_int_data_0d = new LLData<int>((size_t)0, odim0);
	LLData<float>  *other_fl_data_1d  = new LLData<float>((size_t)1, odim1);
	LLData<double> *other_db_data_3d  = new LLData<double>((size_t)3, odim3);

	EXPECT_TRUE(HaveSameDimensions(*int_data_0d, *other_int_data_0d));	
	EXPECT_TRUE(HaveSameDimensions(*fl_data_1d, *other_fl_data_1d));	
	EXPECT_TRUE(HaveSameDimensions(*db_data_3d, *other_db_data_3d));	
	
	odim3[1] = 25;
	LLData<double> *some_other_db_data_3d  = new LLData<double>((size_t)3, odim3);
	EXPECT_FALSE(HaveSameDimensions(*db_data_3d, *some_other_db_data_3d));	

	delete other_int_data_0d;
	delete other_fl_data_1d;
	delete other_db_data_3d;
	delete some_other_db_data_3d;
	delete odim0;
	delete odim1;
	delete odim3;
}

TEST_F(LLDataTest, Accessors) {
	for (size_t i=0; i < fl_data_1d->getTotalSize(); ++i) {
		(*fl_data_1d)[i] = 0.5f*i;
	}
	EXPECT_EQ((*fl_data_1d)[2], 1.0f);
	
	int *coordinate = new int[(size_t)1];
	coordinate[0] = 2;
	EXPECT_EQ(fl_data_1d->atCoordinate(coordinate), 1.0f);
	EXPECT_EQ(fl_data_1d->getTotalSum(), 22.5f);

	for (size_t i=0; i < db_data_3d->getTotalSize(); ++i) {
		(*db_data_3d)[i] = 0.2*i;
	}
	
	EXPECT_EQ((*db_data_3d)[2], 0.4);
	int *coordinate3d = new int[(size_t)3];
	coordinate3d[0] = 0;
	coordinate3d[1] = 0;
	coordinate3d[2] = 2;

	EXPECT_EQ(db_data_3d->atCoordinate(coordinate3d), 0.4);
	EXPECT_EQ(db_data_3d->getTotalSum(), 899700.0);

	delete coordinate;
	delete coordinate3d;

}


#endif // LLDATATEST_H
