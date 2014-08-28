#ifndef INTENSITYDATAFUNCTIONSTEST_H
#define INTENSITYDATAFUNCTIONSTEST_H



#include "gtest/gtest.h"
#include "IntensityDataFunctions.h"
#include "VariableBinAxis.h"

class IntensityDataFunctionsTest : public ::testing::Test
{
 protected:
    IntensityDataFunctionsTest(){}
    virtual ~IntensityDataFunctionsTest(){}

};



TEST_F(IntensityDataFunctionsTest, ClipDataSetFixed)
{
    OutputData<double> data;
    FixedBinAxis axis0("axis0",10, -5.0, 5.0);
    data.addAxis(axis0);
    FixedBinAxis axis1("axis1",3, 0.0, 3.0);
    data.addAxis(axis1);

    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = i;
    }

    OutputData<double> *clip = IntensityDataFunctions::createClippedDataSet(data, -5.0, 0.0, -1.5, 1.5);
    std::vector<double> vref = boost::assign::list_of(0.0)(1.0)(3.0)(4.0)(6.0)(7.0)(9.0)(10.0);
    EXPECT_EQ(clip->getAllocatedSize(), 8);
    int index(0);
    for(size_t i=0; i<clip->getAllocatedSize(); ++i) {
        EXPECT_EQ(vref[index++], (*clip)[i]);
    }
    delete clip;
}


TEST_F(IntensityDataFunctionsTest, ClipDataSetVariable)
{
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    OutputData<double> data;
    VariableBinAxis axis0("axis0",4, values);
    data.addAxis(axis0);
    VariableBinAxis axis1("axis1",4, values);
    data.addAxis(axis1);

    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = i;
    }

    OutputData<double> *clip = IntensityDataFunctions::createClippedDataSet(data, -0.5, 0.5, 0.99, 2.0);
    std::vector<double> vref = boost::assign::list_of(6.0)(7.0)(10.0)(11.0);
    EXPECT_EQ(clip->getAllocatedSize(), 4);
    int index(0);
    for(size_t i=0; i<clip->getAllocatedSize(); ++i) {
        EXPECT_EQ(vref[index++], (*clip)[i]);
    }
    delete clip;


}

#endif
