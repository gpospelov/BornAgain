#ifndef OUTPUTDATATEST_H
#define OUTPUTDATATEST_H

#include "OutputData.h"

#include "gtest/gtest.h"

class OutputDataTest : public ::testing::Test
{
protected:
    OutputDataTest();
    virtual ~OutputDataTest();

    OutputData<int> int_data_0d;
    OutputData<float> fl_data_1d;
    OutputData<double> db_data_3d;
    std::vector<size_t> zero_3d_coordinate;
};

OutputDataTest::OutputDataTest()
{
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    fl_data_1d.addAxis(new NamedVector<double>("angle", 0.0, 0.1, 20));

    db_data_3d.addAxis(new NamedVector<double>("angle", 0.0, 0.1, 20));
    db_data_3d.addAxis(new NamedVector<double>("length", 0.0, 0.5, 10));
    db_data_3d.addAxis(new NamedVector<int>("index", 10, 1, 10));
    OutputData<double>::iterator it = db_data_3d.begin();
    for (size_t i=0; i<2000; ++i)
    {
        *it = (double)i;
        ++it;
    }
}

OutputDataTest::~OutputDataTest()
{
}

TEST_F(OutputDataTest, SingleElementAfterConstruction)
{
    EXPECT_EQ((size_t)1, int_data_0d.getAllocatedSize());
}

TEST_F(OutputDataTest, SizeAfterAddingAxes)
{
    EXPECT_EQ((size_t)1, int_data_0d.getAllocatedSize());
    EXPECT_EQ((size_t)20, fl_data_1d.getAllocatedSize());
    EXPECT_EQ((size_t)2000, db_data_3d.getAllocatedSize());
}

TEST_F(OutputDataTest, DataInitialization)
{
    std::vector<int> coordinates;
    coordinates.push_back(11);
    coordinates.push_back(4);
    coordinates.push_back(3);
    EXPECT_DOUBLE_EQ((double)1143, db_data_3d[db_data_3d.toIndex(coordinates)]);
}

#endif // OUTPUTDATATEST_H
